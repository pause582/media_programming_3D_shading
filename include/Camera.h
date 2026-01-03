#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Vector3D.h"
#include "Canvas.h"
#include "Object3D.h"
#include "Color.h"

#define MAX_REFLECT_NUM 3

class ShadingEnvironment{
    public:
    Color ambient;
    PointLight light_source;
    double DISTANCE_CONSTANT;
    double LUMINANCE_CONSTANT;
    //ShadingEnvironment(Color const& ambient, PointLight const& light_source);
    ShadingEnvironment(Color const& ambient, PointLight const& light_source, double DISTANCE_CONSTANT = 0.05, double LUMINANCE_CONSTANT = 0.3);
};

class Camera{
    private:
    Vector3D p_position, p_reference;
    double fov_y, fov_x, delta_y,delta_x;
    Vector3D u,v,w,up;
    Image film;
    void updateLocalAxis();

    public:
    Camera(Vector3D const& pos,Vector3D const& ref,Vector3D const& up,double fov,double n_x,double n_y);
    Vector3D calcViewingVector(double x,double y) const;
    Vector3D getPosition() const;
    Vector3D getReferencePoint()const;
    double getFovY()const;
    double getDeltaY()const;
    Vector3D getU()const;
    Vector3D getV()const;
    Vector3D getW()const;
    Image getFilm()const;
    void clearFilm(Color const& bg_color);
    void calcRaytracing(vector<Primitive*> const & objlist,
        ShadingEnvironment const& shader = ShadingEnvironment(COLOR_WHITE,PointLight(Vector3D(0,0,0),COLOR_BLACK)));
    void setPosition(Vector3D const& pos);
    void setReferencePoint(Vector3D const& ref);
};

Color calcShading(IntersectInfo const& info,vector<Primitive*> const & objlist, ShadingEnvironment const& shader);
// Extension: vector<PointLight&> const&

#endif