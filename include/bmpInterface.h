#ifndef _BMPINTERFACE_H_
#define _BMPINTERFACE_H_

#include "Image.h"

bool exportBmpImage(const char* filename, Image img);
bool importBmpImage(const char* filename, Image& img);

#endif