#include "kcircle.h"

KCircle::KCircle(float r) : radius(r) {}
KCircle::KCircle(const KCircle& other) : radius(other.radius) {

}
KCircle::KCircle(KCircle&& other) noexcept : radius(other.radius) {
	other.radius = 0.0f; 
;
}
KCircle& KCircle::operator=(const KCircle& other) {
    if (this != &other) { 
        radius = other.radius;
    }

    return *this;
}
KCircle& KCircle::operator=(KCircle&& other) noexcept {
    if (this != &other) { 
        radius = other.radius;
        other.radius = 0.0f; 
    }

    return *this;
}
KCircle::~KCircle() {

};

double KCircle::getPerimeter()const
{
	return 2 * radius * PI;
}

double KCircle::getArea()const
{

	return  std::pow(radius,2)* PI;
}
