#include <vector>
#include <cstdio>

#include "Filter.h"

using namespace std;

Filter::Filter(int size, vector<double> h){
    this->size = size;
    matrix = h;
}
RGB_matrix Filter::operator*(RGB_matrix& input){
   return applyOn(input,
        RGB_matrix(input.getWidth(),input.getHeight(),Color(255,255,255))); //White mask
}

RGB_matrix Filter::applyOn(RGB_matrix& input,const RGB_matrix& mask){
    RGB_matrix output = RGB_matrix(input.getWidth(),input.getHeight());
    int delta = size/2;
    
    for(int i=0;i<output.getHeight();i++){
        for(int j=0;j<output.getWidth();j++){
                
            if(mask.getPixel(i,j).getR() != 0){
                double output_r,output_g,output_b;
                output_r = output_g = output_b = 0;

                for(int m=0;m<size;m++){
                    int y = i + m - delta ;
                    for(int n=0;n<size;n++){
                        int x = j + n - delta;
                        RGB_container c = RGB_container(0,0,0);
                        if(y<0||y>=output.getHeight()||x<0||x>=output.getWidth())
                            c = input.getPixel(i,j); //out of range pixel
                        else
                            c = input.getPixel(y,x);
                        output_r += (double)c.getR() * matrix[m*size + n];
                        output_g += (double)c.getG() * matrix[m*size + n];
                        output_b += (double)c.getB() * matrix[m*size + n];
                    }
                }
                output.setPixel(i,j,RGB_container(output_r,output_g,output_b));
            }else
                output.setPixel(i,j,input.getPixel(i,j));
        }
    }
    return output;
}