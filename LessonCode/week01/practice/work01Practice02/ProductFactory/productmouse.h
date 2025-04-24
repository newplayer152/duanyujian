#ifndef __PRODUCT_MOUSE_H__  
#define __PRODUCT_MOUSE_H__

#include "product.h"
class ProductMouse : public Product{
public:

    ProductMouse();
    
    ProductMouse(const ProductMouse& other);
    
    ProductMouse& operator =(const ProductMouse& other);

    ~ProductMouse();

    void showProduct() override;
};
#endif //__PRODUCT_MOUSE_H__


