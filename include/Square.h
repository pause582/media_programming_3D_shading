#include "Object3D.h"
#include "Vector3D.h"
#include "Color.h"

using namespace std;

class Square : public Primitive{
    public:
    Vector3D center;
    double side;
    Color color;
    Square(Vector3D center, double side, Color color){
        this->center = center;
        this->side = side;
        this->color = color;
    }
};

IntersectInfo calcRaySquareIntersect(Ray& ray,Vector3D center,double size,Color color){

    IntersectInfo info;
    info.distance = INF_DISTANCE;

    Vector3D delta = center - ray.origin;
    Vector3D normal = Vector3D(0,0,1);
    double t = normal.dot(delta) / normal.dot(ray.direction);
    Vector3D point_on_plane =  ray.origin + t * ray.direction;

    if(t > 0 && t < info.distance) { 

        Vector3D center_to_p_o_p = point_on_plane - center;

        if(abs(center_to_p_o_p.x) <= size/2.0 && abs(center_to_p_o_p.y) <= size/2.0 ){
            info.distance = t;
            info.point = point_on_plane;
            info.normal = normal;
            info.color = color;
        }
    }
    return info;
}