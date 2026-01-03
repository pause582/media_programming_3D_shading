#include <cstdio>
#include "Color.h"

using namespace std;

RGB_container::RGB_container(double R,double G, double B, bool t){
    isTransparent = t;
    r = R;
    g = G;
    b = B;
}
RGB_container::RGB_container(const RGB_container& x){
    isTransparent = x.isTransparent;
    r = x.getR();
    g = x.getG();
    b = x.getB();
}
double RGB_container::getR() const{
    return r;
}
double RGB_container::getG() const{
    return g;
}
double RGB_container::getB() const{
    return b;
}
RGB_container RGB_container::operator=(const RGB_container& x){
    isTransparent = x.isTransparent;
    r = x.getR();
    g = x.getG();
    b = x.getB();
    return (*this);
}
RGB_container RGB_container::operator*(double x) const{
    return RGB_container(this->r * x,this->g * x,this->b * x);
}
RGB_container RGB_container::operator*(RGB_container const& c) const{
    return RGB_container(this->r * c.getR(),this->g * c.getG(),this->b * c.getB());
}
RGB_container RGB_container::operator+(const RGB_container& x) const{
    return RGB_container(this->r + x.getR(),this->g + x.getG(),this->b + x.getB());
}
RGB_container RGB_container::operator+(double x) const{
    return RGB_container(this->r + x,this->g + x,this->b + x);
}
void RGB_container::print(){
    printf("RGB_container: (%.2f,%.2f,%.2f, isTrans: %d)\n",r,g,b,isTransparent);
}

Color::Color(double R,double G, double B, bool t) : RGB_container(R,G,B,t){
    r = double_to_unsigned_char(r);
    g = double_to_unsigned_char(g);
    b = double_to_unsigned_char(b);
}
Color::Color(const RGB_container& x) : RGB_container(x){
    r = double_to_unsigned_char(r);
    g = double_to_unsigned_char(g);
    b = double_to_unsigned_char(b);
}
RGB_container Color::operator=(const RGB_container& x){
    RGB_container::operator=(x);
    r = double_to_unsigned_char(r);
    g = double_to_unsigned_char(g);
    b = double_to_unsigned_char(b);
    return (*this);
}
RGB_container Color::operator*(double x) const{
    return Color(this->r * x,this->g * x,this->b * x);
}
RGB_container Color::operator+(const RGB_container& x) const{
    return Color(this->r + x.getR(),this->g + x.getG(),this->b + x.getB());
}
RGB_container Color::operator+(double x) const{
    return Color(this->r + x,this->g + x,this->b + x);
}
void Color::print(){
    printf("Color: (%d,%d,%d, t:%d)\n",(unsigned char)r,(unsigned char)g,(unsigned char)b,isTransparent);
}

double luminance(const RGB_container& c){
    return (double)c.getR() * 0.299 + (double)c.getG() * 0.587 + (double)c.getB() * 0.144;
}
unsigned char double_to_unsigned_char(double x){
    if(x<0) return (unsigned char)0;
    else if(x>255) return (unsigned char)255;
    else return (unsigned char)x;
}