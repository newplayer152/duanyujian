#include <iostream>
#include "mysharedptr.h"
#include "base.h"

int main()
{
    MySharedPtr<Base> ptr1(new Base);
    std::cout << ptr1.useCount() << std::endl;
    MySharedPtr<Base> ptr2(ptr1);
    std::cout << "======================" << std::endl;
    std::cout << ptr1.useCount() << std::endl;
    std::cout << ptr2.useCount() << std::endl;

    std::cout << "======================" << std::endl;

    MySharedPtr<Base> ptr5(new Base);
    MySharedPtr<Base> ptr6;

    ptr6 = ptr5;

    std::cout << ptr5.useCount() << std::endl;
    std::cout << ptr6.useCount() << std::endl;

    return 0;
}

