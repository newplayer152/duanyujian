#ifndef __PRODUCT_FACTORY_H__  
#define __PRODUCT_FACTORY_H__

#include <iostream>
#include"product.h"

enum class ProduceID : int
{
	MouseProduce = 1,
	KeyBoardProduce = 2
};
class ProductFactory
{
public:
	Product* CreateProduct(ProduceID id);
};
#endif //__PRODUCT_FACTORY_H__

