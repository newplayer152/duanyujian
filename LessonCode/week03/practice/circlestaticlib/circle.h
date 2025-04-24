#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include <iostream>

class Circle
{
public:
    Circle(const double y = 0.0);
    ~Circle() = default;
    double getRadius() const;
    void setRadius(double r);
    void print();
    constexpr double getArea() ;
    constexpr double getPerimeter();
private:
    double m_radius;
};



#endif // __CIRCLE_H__