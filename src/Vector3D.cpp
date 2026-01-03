#include "Vector3D.h"
#include <cmath>
#include <cstdio>

using namespace std;

Vector3D::Vector3D(double x,double y,double z){
    this->x = x;
    this->y = y;
    this->z = z;
}
Vector3D::Vector3D(Vector3D const& v){
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;   
}
Vector3D Vector3D::operator=(Vector3D const& v){
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;  
    return (*this);
}

Vector3D Vector3D::operator*(double a) const{
    return Vector3D(x * a,y * a,z * a);
}
Vector3D Vector3D::operator/(double a) const{
    return operator*(1/a);
}
Vector3D Vector3D::operator*=(double a){
    return (*this) = (*this)*a; 
}
Vector3D Vector3D::operator/=(double a){
    return operator*=(1/a);
}
Vector3D Vector3D::operator-() const{
    return Vector3D(-x,-y,-z);
}
Vector3D Vector3D::operator+(Vector3D const& v)  const{
    return Vector3D(x + v.x,y + v.y,z + v.z);
}
Vector3D Vector3D::operator-(Vector3D const& v) const{
    return operator+(-v);
}
Vector3D Vector3D::operator+=(Vector3D const& v){
    return (*this) = (*this) + v;
}
Vector3D Vector3D::operator-=(Vector3D const& v){
    return (*this) = (*this) - v;
}

double Vector3D::dot(Vector3D const& v) const{
    return x * v.x + y * v.y + z * v.z;
}
Vector3D Vector3D::cross(Vector3D const& v) const{
    return Vector3D(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
}

double Vector3D::length() const{
    return sqrt(x*x+y*y+z*z);
}
Vector3D Vector3D::normalize() const{
    return (*this) / length();
}

bool Vector3D::operator==(Vector3D const& v) const{
    return (x==v.x)&&(y==v.y)&&(z==v.z);
}
bool Vector3D::operator!=(Vector3D const& v) const{
    return !operator==(v);
}

void Vector3D::print() const{
    printf("( %.2f, %.2f, %.2f)\n",x,y,z);
}

Vector3D operator*(double a,Vector3D const& v){
    return v * a;
}
Vector3D operator/(double a,Vector3D const& v){
    return v / a;
}

Vector3D Vector3D::rotateX(double degree) const{
    double rad = (degree * M_PI) / 180 ;
    return Vector3D(x, y*cos(rad)-z*sin(rad), y*sin(rad)+z*cos(rad));
}
Vector3D Vector3D::rotateY(double degree) const{
    double rad = (degree * M_PI) / 180 ;
    return Vector3D(x*cos(rad)+z*sin(rad), y, -x*sin(rad)+z*cos(rad));
}
Vector3D Vector3D::rotateZ(double degree) const{
    double rad = (degree * M_PI) / 180 ;
    return Vector3D(x*cos(rad)-y*sin(rad), x*sin(rad)+y*cos(rad), z);
}
Vector3D Vector3D::rotate_by(Vector3D const& p,double x,double y,double z) const{
    return (((*this) - p).rotateX(x).rotateY(y).rotateZ(z) + p);
}