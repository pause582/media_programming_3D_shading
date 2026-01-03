#include "Image.h"
#include "Color.h"
#include "Canvas.h"
#include "Brush.h"
#include <cstdio>

using namespace std;

Canvas::Canvas(int w, int h, const Color c,int offset_x, int offset_y):Image(w,h,c){
    this->offset_x = offset_x;
    this->offset_y = offset_y;
    /* end_x = start_x + img.width();
       end_y = start_y + img.height();*/ 
}
/*
    len = 6
    0   1  2  3  4  5
   -2  -1  0  1  2  3
*/
Canvas::Canvas(const Canvas& cvs) : Image(cvs){
    this->offset_x = cvs.offset_x;
    this->offset_y = cvs.offset_y;
}
Canvas::Canvas(const RGB_matrix& img,int offset_x, int offset_y) : Image(img){
    this->offset_x = offset_x;
    this->offset_y = offset_y;
}
RGB_container Canvas::getPixel(int i, int j) const{return Image::getPixel(convertY(i), convertX(j));
}
RGB_matrix Canvas::operator=(const Canvas& cvs){
    this->offset_x = cvs.offset_x;
    this->offset_y = cvs.offset_y;
    return Image::operator=(cvs);
}

void Canvas::setPixel(int i, int j,const RGB_container& px){
    Image::setPixel(convertY(i), convertX(j),px);
}
int Canvas::getStartX()const{return -offset_x;}
int Canvas::getStartY()const{return -offset_y;}
int Canvas::convertY(int i)const{return offset_y + i;}
int Canvas::convertX(int j)const{return  offset_x + j;}
bool Canvas::isInRange(int i,int j)const{return RGB_matrix::isInRange(convertY(i), convertX(j));}

void Canvas::drawBrush(int i,int j,const Brush& b){
    int delta = b.getSize()/2;
    for(int m=0;m<b.getSize();m++){
        int y = i + m - delta ;
        for(int n=0;n<b.getSize();n++){
            int x = j + n - delta;  
            setPixel(y,x,b.getPixel(m,n));
        }
    }
}

void Canvas::print(){
    printf("Canvas\n");
    for(int i=getStartY(); i < getStartY() + height ;i++){
        for(int j=getStartX();j<getStartX() + width;j++){
            printf("Pixel (%d,%d) ",i,j);
            getPixel(i,j).print();
        }
    }
}