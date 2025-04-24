#include <cstdlib> // 包含system函数的头文件
#include <iostream>
#include "kcircle.h"
int main()
{

    KCircle kcircle(5);

    std::cout <<"Perimeter:  "<< kcircle.getPerimeter()<< "\n";
    std::cout <<"Area:  "<< kcircle.getArea()<< "\n";
    system("pause");
}


