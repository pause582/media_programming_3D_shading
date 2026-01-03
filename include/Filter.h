#ifndef _FILTER_H_
#define _FILTER_H_

#include <vector>
#include "Image.h"
#include "Color.h"

using namespace std;

class Filter{
    public:
    int size;
    vector<double> matrix;
    Filter(int size, const vector<double> h);
    RGB_matrix operator*(RGB_matrix& input);
    RGB_matrix applyOn(RGB_matrix& input,const RGB_matrix& mask);
};

#endif