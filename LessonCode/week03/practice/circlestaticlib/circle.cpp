#include "circle.h"

static constexpr double PI = 3.14;

Circle::Circle(const double r) : m_radius(r)
{
    ;
}

double Circle::getRadius() const
{
    return m_radius;
}

void Circle::setRadius(double r)
{
    this->m_radius = r;
}

void Circle::print() 
{
    std::cout << "circle areaa: " << this->getArea() << std::endl;
    std::cout << "circle perimeter: " << this->getPerimeter() << std::endl;
}

constexpr double Circle::getArea()
{
    return PI * m_radius * m_radius;
}

constexpr double Circle::getPerimeter()
{
    return 2 * PI * m_radius;
}

