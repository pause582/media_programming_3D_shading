#include <cstdio>
#include <iostream>

#include "Vector3D.h"
#include "Color.h"
#include "Object3D.h"
#include "Camera.h"
#include "bmpInterface.h"

using namespace std;

int main(void){

    Vector3D cam_pos = Vector3D(0,0,5);
    Vector3D p_ref = Vector3D(10,0,2);
    Vector3D up = Vector3D(0,0,1);
    double fov = 60 * M_PI / 180; // to radius
    int img_size_h = 720;
    int img_size_w = 1280;
    Camera cam = Camera(cam_pos,p_ref,up,fov,img_size_w,img_size_h);
    
    PointLight L1 = PointLight(Vector3D(7,0,0), COLOR_WHITE,0.5);
    Color bg_color = COLOR_BLACK;
    Color ambient_color = COLOR_WHITE * 0.1;
    const double DISTANCE_CONSTANT = 0.05;
    const double LUMINANCE_CONSTANT = 0.04;
    ShadingEnvironment shader = ShadingEnvironment(ambient_color,L1,DISTANCE_CONSTANT,LUMINANCE_CONSTANT);

    Sphere s2 = Sphere(Vector3D(50,0,0), 10, COLOR_PINK);

    Cube c1 = Cube(Vector3D(20,-10,0),2,Vector3D(0,0,1),Vector3D(-1,0,0),
        {COLOR_MIKU,COLOR_ORANGE,COLOR_PINK,COLOR_YELLOW,COLOR_BLUE,COLOR_RED});

    vector<Primitive*> objlist;
    objlist.push_back(&c1);
    objlist.push_back(&s2);
    objlist.push_back(&L1);
    
    for(int i=0;i<300;i++){
        cam.clearFilm(bg_color);
        cam.calcRaytracing(objlist,shader);

        string file_name = "output/a" + to_string(i) + ".bmp";
        exportBmpImage(file_name.c_str(),cam.getFilm());

        c1.rotate_by_center(-0.67,2,1.33);
        c1.move(Vector3D(0,0.0667,0));
    }  
}
