#include <cstdlib>

#include "Image.h"
#include "bmpInterface.h"
#include "bmpIO.h"

using namespace std;

bool exportBmpImage(const char* filename, Image img){
    
    int nchannel = 3;
    int npixel = img.getHeight() * img.getWidth();
    int nchar = nchannel * npixel;
    unsigned char* pixelString = (unsigned char*)malloc(sizeof(char)*nchar);
    
    int string_i = 0;
    for(int pixel_i = 0;pixel_i<img.size(); pixel_i++){
        int height_reverse_pixel = pixel_i + img.getWidth() * (img.getHeight() - 1 - 2 * (pixel_i / img.getWidth()));
        pixelString[string_i] = img[height_reverse_pixel].getB();
        pixelString[string_i+1] = img[height_reverse_pixel].getG();
        pixelString[string_i+2] = img[height_reverse_pixel].getR();
        string_i += 3;
    }
    bool success = writeBmpImage(filename,img.getWidth(),img.getHeight(),nchannel,pixelString);
    free(pixelString);
    return success;
}

/*
    pixel = y * width + x
    conv_p = (height - y - 1) * width + x

    conv_p - pixel = width * (height - 2(pixel / width) - 1)
*/


bool importBmpImage(const char* filename, Image& img){
    int width,height,nchannel;
    width = height = nchannel = 0;
    unsigned char* pixelString = NULL;

    bool success = readBmpImage(filename,&width,&height,&nchannel,&pixelString);
    //debug_string = pixelString;
    
    if(success){
        img = Image(width,height);
        int string_i = 0;
        for(int pixel_i = 0;pixel_i<img.size(); pixel_i++){
            int height_reverse_pixel = pixel_i + img.getWidth() * (img.getHeight() - 1 - 2 * (pixel_i / img.getWidth()));
            img[height_reverse_pixel] = Color(pixelString[string_i+2],pixelString[string_i+1],pixelString[string_i]);
            string_i += 3;
        }
        free(pixelString); //why doesnt work while uncomment
    }
    return success;
}