#include <vector>
#include <cstdio>
#include <cmath>
#include "Color.h"
#include "Image.h"

using namespace std;

RGB_matrix::RGB_matrix(int w, int h, RGB_container init_val) : vector<RGB_container>(w*h,init_val){ //??
    width = w;
    height = h;
}
RGB_matrix::RGB_matrix(const RGB_matrix& img){
    vector<RGB_container>::operator=(img);
    width = img.getWidth();
    height = img.getHeight();
}

int RGB_matrix::getWidth() const{return width;}
int RGB_matrix::getHeight() const{return height;}

RGB_container RGB_matrix::getPixel(int i, int j) const{return (*this)[i*width + j];}
void RGB_matrix::setPixel(int i, int j,const RGB_container& px){
    if(!isInRange(i,j)) return;
    if(px.isTransparent) return;
    (*this)[i*width + j] = px;
}

RGB_matrix RGB_matrix::operator=(const RGB_matrix& img){
    vector<RGB_container>::operator=(img);
    width = img.getWidth();
    height = img.getHeight();
    return (*this);
}

bool RGB_matrix::isInRange(int i,int j) const{
    //printf("Test (%d,%d)\n",i,j);
    //printf("flag: %d\n",!(i < 0 || i >= height || j < 0 || j >= width));
    return !(i < 0 || i >= height || j < 0 || j >= width);
}

void RGB_matrix::clear(const RGB_container& c){ 
    for(int i=0;i<0;i++)
        (*this)[i] = c;
}
void RGB_matrix::print(){
    printf("RGB_matrix\n");
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            printf("Pixel (%d,%d) ",i,j);
            getPixel(i,j).print();
        }
    }
}

Image::Image(int w, int h,Color init_color) : RGB_matrix(w,h,init_color){}
Image::Image(const RGB_matrix& img){
    (*this).resize(img.size());
    width = img.getWidth();
    height = img.getHeight();
    for(int i=0;i<img.size();i++)
       (*this)[i] = (Color)img[i];
}

RGB_matrix Image::operator=(const RGB_matrix& img){
    (*this).resize(img.size());
    width = img.getWidth();
    height = img.getHeight();
    for(int i=0;i<img.size();i++)
       (*this)[i] = (Color)img[i];
    return (*this);
}

RGB_container Image::getPixel(int i, int j) const{return (Color)(*this)[i*width + j];}
void Image::setPixel(int i, int j,const RGB_container& px){
    RGB_matrix::setPixel(i,j,(Color)px);
}

void Image::clear(const RGB_container& c){
   for(int i=0;i<size();i++)
      (*this)[i] = (Color)c;
}
void Image::print(){
    printf("Image\n");
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            printf("Pixel (%d,%d) ",i,j);
            getPixel(i,j).print();
        }
    }
}

void drawChecker(RGB_matrix& img, int size, RGB_container& c1, RGB_container& c2){
    for(int i=0;i<img.getHeight();i++){
        for(int j=0;j<img.getWidth();j++){
            RGB_container c = ((i/size + j/size)%2 == 0) ? c1:c2;
            img.setPixel(i,j,c);
        }
    }
}
void drawGradation(RGB_matrix& image,const RGB_container&  color1, const RGB_container& color2) {
    for(int j=0; j<image.getHeight(); j++) {
        for(int i=0; i<image.getWidth(); i++) {
            double a = double(i)/double(image.getWidth()-1);
            RGB_container c = color1 * (1-a) + color2 * a;
            image.setPixel(i, j, c);
        }
    }
}
void linearTransform(RGB_matrix& img, double a, double b){
    for(int i=0;i<img.size();i++)
        img[i] = img[i] * a + b;
}

void binarize(Image& img, double thresh){
    for(int i=0;i<img.size();i++){
        img[i] = luminance(img[i]) < thresh ? Color(0,0,0) : Color(255,255,255);
    }
}

void posterize(Image& img, int level){
    double unit = round(256/level);

    for(int i=0;i<img.getHeight();i++){
        for(int j=0;j<img.getWidth();j++){
            Color c = Color(
                int(img.getPixel(i,j).getR()/unit)*unit,
                int(img.getPixel(i,j).getG()/unit)*unit,
                int(img.getPixel(i,j).getB()/unit)*unit);
            img.setPixel(i,j,c);
        }
    }
}
/*
void applyMedianFilter(Image& input, Image& output, int size){
    output = Image(input.getWidth(),input.getHeight());
    int delta = size/2;

    for(int i=0;i<output.getHeight();i++){
        for(int j=0;j<output.getWidth();j++){

            vector<Color> ColorArr;

            //printf("Start of (%d,%d)\n",i,j);

            for(int m=0;m<size;m++){
                int y = i + m - delta ;
                for(int n=0;n<size;n++){
                    int x = j + n - delta;

                    Color c = Color(0,0,0);
                    if(y<0||y>=output.getHeight()||x<0||x>=output.getWidth());
                    else
                        ColorArr.push_back(input.getPixel(y,x));
                }
            }
            
            for(int s = 1;s<ColorArr.size();s++){ //Insertion sort
                int index = s;
                for(int k = s;k<=0;k--){
                    if(luminance(ColorArr[index]) < luminance(ColorArr[k])){
                        Color temp = ColorArr[index];
                        ColorArr[index] = ColorArr[k];
                        ColorArr[k] = temp;
                        index--;
                    }else
                        break;
                }
            }

            output.setPixel(i,j,ColorArr[ColorArr.size()/2]);
        }
    }
}*/