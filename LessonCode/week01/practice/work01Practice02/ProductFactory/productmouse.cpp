#include "productmouse.h"

ProductMouse::ProductMouse() {};
ProductMouse::ProductMouse(const ProductMouse& other) {};

ProductMouse& ProductMouse::operator=(const ProductMouse& other)
{
	return *this;
}

ProductMouse::~ProductMouse()
{
}

void ProductMouse::showProduct()
{
	std::cout << "create Mouse Product" << std::endl;
}
