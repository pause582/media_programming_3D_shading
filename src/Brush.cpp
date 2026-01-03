
#include "Brush.h"
#include "Image.h"
#include "Color.h"
#include <vector>
#include <cstdio>

using namespace std;

Brush::Brush(int size, vector<Color> h) : Image(size,size){
    this->size = size;
    for(int i=0;i<h.size();i++) (*this)[i] = h[i];
}
Brush::Brush(int size, vector<int> h) : Image(size,size){
    this->size = size;
    for(int i=0;i<h.size();i++){
        Color c;
        if(h[i] > 0){
            c = Color(0,0,0,false);
        }else{
            c = Color(255,255,255,true);
        }
        //c.print();
        (*this)[i] = c;
    }
    //print();
}
int Brush::getSize() const{
    return size;
}