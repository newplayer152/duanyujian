#ifndef __PRODUCT_KEYBOARD_H__  
#define __PRODUCT_KEYBOARD_H__
#include "product.h"
class ProductKeyBoard :
    public Product
{
public:
    ProductKeyBoard();

    ProductKeyBoard(const ProductKeyBoard& other);

    ProductKeyBoard& operator=(const ProductKeyBoard& other);

    ~ProductKeyBoard();

    
    void showProduct() override;
};
#endif //__PRODUCT_KEYBOARD_H__



