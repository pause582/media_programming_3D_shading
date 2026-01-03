#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "Color.h"
#include <vector>

using namespace std;

class RGB_matrix : public vector<RGB_container>{
    protected:
    int width,height;
    public:
    RGB_matrix(int w=1, int h=1,const RGB_container init_value = RGB_container());
    RGB_matrix(const RGB_matrix& img);
    int getWidth() const;
    int getHeight() const;
    void test(vector<RGB_container>);
    virtual RGB_container getPixel(int i, int j) const;
    virtual void setPixel(int i, int j,const RGB_container& px);
    virtual RGB_matrix operator=(const RGB_matrix& img);
    bool isInRange(int i, int j)const;
    virtual void clear(const RGB_container& c);
    virtual void print();
};

class Image : public RGB_matrix{
    public:
    Image(int w=1, int h=1,const Color c = Color());
    Image(const RGB_matrix& img);
    virtual RGB_container getPixel(int i, int j) const override;
    virtual void setPixel(int i, int j,const RGB_container& px) override;
    RGB_matrix operator=(const RGB_matrix& img) override;
    void clear(const RGB_container& c) override;
    void print() override;
};

void drawChecker(RGB_matrix& img, int size,const RGB_container& c1,const RGB_container& c2);
void drawGradation(RGB_matrix& image,const RGB_container& color1,const RGB_container& color2);
void linearTransform(RGB_matrix& img, double a, double b);

// Image only
void binarize(Image& img, double thresh);
void posterize(Image& img, int level);

#endif