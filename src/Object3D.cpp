#include "Object3D.h"
#include <cstdio>
#include <cmath>

using namespace std;

Primitive::Primitive(){}

Polygon::Polygon(vector<Vector3D> const& vertex_list, Color const& color){
    this->v_list = vertex_list;
    this->color = color;
    if(vertex_list.size() < 2) printf("Polygon cannot have less than 2 vertics!!\n");
    this->normal = (v_list[1]-v_list[0]).cross(v_list[2]-v_list[0]).normalize();
}
Vector3D Polygon::getNormalVector() const{return normal;}
vector<Vector3D> Polygon::getVertics() const{return v_list;}
void Polygon::move(Vector3D const& delta){
    for(int i=0;i<v_list.size();i++) v_list[i] += delta;
}
void Polygon::rotate_by(Vector3D const& p,double x,double y,double z){
    for(int i=0;i<v_list.size();i++){
        v_list[i] = v_list[i].rotate_by(p,x,y,z);
    }
    this->normal = (v_list[1]-v_list[0]).cross(v_list[2]-v_list[0]).normalize();
}
void Polygon::rotate_by_center(double x,double y,double z){
    Vector3D center = Vector3D(0,0,0);
    for(int i=0;i<v_list.size();i++) center += v_list[i];
    center /= v_list.size();
    rotate_by(center,x,y,z);
}
IntersectInfo Polygon::calcIntersect(Ray const& r) const{
    IntersectInfo info;
    info.distance = INF_DISTANCE;

    Vector3D delta = v_list[0] - r.origin;
    double t = normal.dot(delta) / normal.dot(r.direction);
    Vector3D point_on_plane =  r.origin + t * r.direction;

    if(t > 0 && t < info.distance) { 
        for(int i=0;i<v_list.size();i++){
            Vector3D v_edge, v_test;
            v_test = point_on_plane - v_list[i];
            if(i+1 == v_list.size()) v_edge = v_list[0] - v_list[i];
            else v_edge = v_list[i+1] - v_list[i];

            double valid = v_edge.cross(v_test).dot(normal);
            if(valid < 0){
                return info; // p_o_p outside this polygon
            }
        }
        //printf("Ray hit\n");
        info.distance = t;
        info.point = r.origin + t * r.direction;
        if(this->normal.dot(r.direction) > 0) info.normal = -this->normal.normalize();
        else info.normal = this->normal.normalize();
        info.color = color;
        info.isDirectLight = isSelfEmit;
    }
    return info;
}


Sphere::Sphere(Vector3D const& center, double radius, Color const& color){
    this->center = center;
    this->radius = radius;
    this->color = color;
}
Vector3D Sphere::getCenter() const{return center;}
double Sphere::Sphere::getRadius() const{return radius;}
Color Sphere::getColor() const{return color;}
void Sphere::setCenter(Vector3D const& new_center){center = new_center;}
void Sphere::setRadius(double new_raidus){radius = new_raidus;}
void Sphere::setColor(Color const& new_color){color = new_color;}
void Sphere::move(Vector3D const& v){this->center += v;}
void Sphere::rotate_by(Vector3D const& p,double x,double y,double z){center = center.rotate_by(p,x,y,z);}
void Sphere::rotate_by_center(double x,double y,double z){}

IntersectInfo Sphere::calcIntersect(Ray const& r) const{
    IntersectInfo info;
    info.distance = INF_DISTANCE;
    
    Vector3D delta = this->center - r.origin; //v
    double s = delta.dot(r.direction);
    double h = sqrt(delta.length() * delta.length() - s*s);

    if(h < radius){
        double t = s - sqrt(radius*radius - h*h);   
        if(t > 0 && t < info.distance) { 
            info.distance = t;
            info.point = r.origin + t * r.direction;
            info.normal = (info.point - center).normalize();
            info.color = color;
            info.isDirectLight = isSelfEmit;
        }
    }
    
    return info;
}

Cube::Cube(Vector3D const& center, double side_length, Vector3D const& up,Vector3D const& front, vector<Color> const& colors){
    this->side_len = side_length;
    this->center = center;
    vector<Vector3D>local_axis = Gram_Schmidt({up,front,up.cross(front)});
    if(local_axis.size()<3) printf("Not enough axis\n"); //Debug msg
    bool isFullColor = colors.size() > 5;
    Color temp_c = colors[0];

    int sgn = 1;
    for(int i=0;i<6;i++){
        vector<Vector3D> s = {
            center + (sgn * local_axis[(i/2)%3] + local_axis[(i/2+1)%3] + local_axis[(i/2+2)%3]) * (side_len / 2.0) ,
            center + (sgn * local_axis[(i/2)%3] + local_axis[(i/2+1)%3] - local_axis[(i/2+2)%3]) * (side_len / 2.0),
            center + (sgn * local_axis[(i/2)%3] - local_axis[(i/2+1)%3] - local_axis[(i/2+2)%3]) * (side_len / 2.0),
            center + (sgn * local_axis[(i/2)%3] - local_axis[(i/2+1)%3] + local_axis[(i/2+2)%3]) * (side_len / 2.0)
        };
        sgn *= -1;
        if(isFullColor) temp_c = colors[i]; //if colors.size < 6, all same color.
        surfaces.push_back(Polygon(s,temp_c));
    }
}
Vector3D Cube::getSide() const{return side_len;}

void Cube::move(Vector3D const& delta){
    this->center += delta;
    for(int i=0;i<surfaces.size();i++)
        surfaces[i].move(delta);
}

void Cube::rotate_by(Vector3D const& p,double x,double y,double z){
    for(int i=0;i<surfaces.size();i++)
        surfaces[i].rotate_by(p,x,y,z);
    center = center.rotate_by(p,x,y,z);
}
void Cube::rotate_by_center(double x,double y,double z){
    rotate_by(center,x,y,z);
}
IntersectInfo Cube::calcIntersect(Ray const& r) const{
    IntersectInfo info;
    info.distance = INF_DISTANCE;
    //getPixel(i,j).print();
    for(int k=0;k<surfaces.size();k++){
        IntersectInfo temp_info = surfaces[k].calcIntersect(r);
        //printf("Distance: %f\n",temp_info.distance);
        if(temp_info.distance < info.distance)
        info = temp_info;
    }
    return info;
}

PointLight::PointLight(Vector3D const& v, Color const& c, double radius) : Sphere(v,radius,c){isSelfEmit = true;}
PointLight::PointLight(PointLight const& p) : Sphere(p){
    isSelfEmit = p.isSelfEmit;
}

vector<Vector3D> Gram_Schmidt(vector<Vector3D> const& input){
    vector<Vector3D> orthonormal_basis = {input[0].normalize()};
    const int dimension = 3;
    const double zero = 0.001;

    for(int n=1;n<input.size();n++){
        Vector3D v = input[n];
        for(int i=0;i<n;i++)
            v -= input[n].dot(orthonormal_basis[i]) * orthonormal_basis[i];

        bool duplicate_flag = false;
        for(int i=0;i<orthonormal_basis.size();i++){
            if(v.dot(orthonormal_basis[i]) > zero){ //duplicate basis
                duplicate_flag = true;
            }
        }
        if(!duplicate_flag)
            orthonormal_basis.push_back(v.normalize());
        if(orthonormal_basis.size()==dimension) break;
    }
    return orthonormal_basis;
}