#include <cstdio>
#include <iostream>

#include "Vector3D.h"
#include "Color.h"
#include "Object3D.h"
#include "Camera.h"
#include "bmpInterface.h"

using namespace std;

int main(void){

    double d = 150;

    Vector3D cam_pos = Vector3D(0,0,-2*d);
    Vector3D p_ref = Vector3D(d,0,0);
    Vector3D up = Vector3D(0,0,1);
    double fov = 60 * M_PI / 180; // to radius
    int img_size_h = 720;
    int img_size_w = 1280;
    Camera cam = Camera(cam_pos,p_ref,up,fov,img_size_w,img_size_h);

    Color bg_color = COLOR_BLACK;
    Color ambient_color = COLOR_WHITE * 0.1;
    const double DISTANCE_CONSTANT = 0.05;
    const double LUMINANCE_CONSTANT = 0.3;
    PointLight L1 = PointLight(Vector3D(d,0,0), COLOR_WHITE);
    ShadingEnvironment shader = ShadingEnvironment(ambient_color,L1,DISTANCE_CONSTANT,LUMINANCE_CONSTANT);

    Sphere s1 = Sphere(Vector3D(d,80,0),  7, COLOR_MIKU);
    Sphere s2 = Sphere(Vector3D(d,140,0), 30, COLOR_PINK);

    vector<Primitive*> objlist;
    objlist.push_back(&L1);
    objlist.push_back(&s1);
    objlist.push_back(&s2);

    for(int i=0;i<1800;i++){
        cam.clearFilm(bg_color);
        cam.calcRaytracing(objlist,shader);
        string file_name = "output/a" + to_string(i) + ".bmp";
        exportBmpImage(file_name.c_str(),cam.getFilm());
        s1.setCenter(s2.getCenter() - Vector3D(0,60,0));
        s1.rotate_by(s2.getCenter(),(i+1)*1.2,0,0);
        s2.rotate_by(Vector3D(d,0,0),0.2,0,0);
    }
}
