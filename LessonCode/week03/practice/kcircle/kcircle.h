#ifndef _KCIRLCE_KCIRLCE_H_
#define _KCIRLCE_KCIRLCE_H_
#define  PI 3.1415926;
#include <cmath>
#include<iostream>
class KCircle
{
public:

    //构造  
    KCircle(float r = 0.0f);

    //拷贝构造
    KCircle(const KCircle& other) ;

    //移动构造   
    KCircle(KCircle&& other) noexcept;

    //拷贝重载
    KCircle& operator=(const KCircle& other);

    //移动重载
    KCircle& operator=(KCircle&& other) noexcept;

    // 析构
    ~KCircle();

    double getPerimeter()const;

	double getArea()const;
private:
	double radius;
};



#endif // _KCIRLCE_KCIRLCE_H_




