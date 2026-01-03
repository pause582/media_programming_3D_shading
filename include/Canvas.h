#ifndef _CANVAS_H_
#define _CANVAS_H_

#include "Image.h"
#include "Color.h"
#include "Brush.h"

class Canvas : public Image{
    private:
    int offset_x,offset_y;
    public:
    Canvas(int w, int h, const Color c,int offset_x=0, int offset_y=0);
    Canvas(const Canvas& cvs);
    Canvas(const RGB_matrix& img,int offset_x=0, int offset_y=0);
    RGB_container getPixel(int i, int j) const;
    RGB_matrix operator=(const Canvas& cvs);
    int getStartX()const;
    int getStartY()const;
    int convertY(int j)const;
    int convertX(int j)const;
    bool isInRange(int i,int j)const;
    void setPixel(int i, int j,const RGB_container& px);
    void drawBrush(int i,int j,const Brush& b);
    void print();
};

#endif