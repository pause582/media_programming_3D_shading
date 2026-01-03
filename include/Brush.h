#ifndef _BRUSH_H_
#define _BRUSH_H_

#include <vector>
#include "Color.h"
#include "Image.h"

using namespace std;

class Brush : public Image{
    private:
    int size;
    public:
    int getSize() const;
    Brush(int size, vector<Color> m);
    Brush(int size, vector<int> im);
};

#endif