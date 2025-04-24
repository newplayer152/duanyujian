
#include <iostream>
#include "productfactory.h"

int main()
{
    ProductFactory* pf = new ProductFactory();
    //Product* p= pf->CreateProduct(ProduceID::MouseProduce);
    Product* p = pf->CreateProduct(ProduceID::KeyBoardProduce);
    p->showProduct();
    delete(p);
    std::cout << "\n";
}

