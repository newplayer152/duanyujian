#ifndef __PRODUCT_H__  
#define __PRODUCT_H__
#include <iostream>
#include <algorithm>
class Product
{
public:
	//ππ‘Ï
	Product();
	Product(const Product& other);
	Product& operator =(const Product& other);

	~Product();

	virtual void showProduct();


};

#endif //__PRODUCT_H__
