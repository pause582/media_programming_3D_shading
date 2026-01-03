#include "Camera.h"
#include "Canvas.h"
#include "Object3D.h"
#include <cmath>
#include <cstdio>

using namespace std;

ShadingEnvironment::ShadingEnvironment(Color const& ambient, PointLight const& light_source, 
    double DISTANCE_CONSTANT, double LUMINANCE_CONSTANT){
        this->ambient = ambient;
        this->light_source = light_source;
        this->DISTANCE_CONSTANT = DISTANCE_CONSTANT;
        this->LUMINANCE_CONSTANT = LUMINANCE_CONSTANT;
}

Camera::Camera(Vector3D const& pos,Vector3D const& ref,Vector3D const& up,double fov_x,double n_x,double n_y){
    film = Image(n_x,n_y);
    p_position = pos;
    p_reference = ref;
    this->up = up;
    updateLocalAxis();
    
    this->fov_x = fov_x;
    delta_x = (2 * tan(fov_x/2)) / film.getWidth();
    
    delta_y = delta_x;
    this->fov_y = 2*atan((delta_y * n_y)/ 2.0);
}
Vector3D Camera::calcViewingVector(double y,double x) const{
    double xs = delta_x * (x + 0.5 - film.getWidth() / 2);
    double ys = delta_y * -(y + 0.5 - film.getHeight() / 2);
    return (xs * u + ys * v + w).normalize();
}

void Camera::updateLocalAxis(){
    w = (p_reference - p_position).normalize();
    u = w.cross(up).normalize();
    v = u.cross(w).normalize();
}

void Camera::setPosition(Vector3D const& pos){
    p_position = pos;
    updateLocalAxis();
}
void Camera::setReferencePoint(Vector3D const& ref){
    p_reference = ref;
    updateLocalAxis();
}

void Camera::calcRaytracing(vector<Primitive*> const & objlist,ShadingEnvironment const& shader){
    Ray r;
    r.origin = p_position;

    int progress_10 = 0;

    for(int i=0;i<film.getHeight();i++){
        for(int j=0;j<film.getWidth();j++){
            double progress = ((double)(i * film.getWidth() + j)/ (double)(film.size()))*100;
            if(progress > progress_10){
                //printf("Computing progress %.2f %%...\n",progress);
                progress_10 += 10;
            }

            r.direction = calcViewingVector(i,j);
            r.remain_reflect = MAX_REFLECT_NUM ;
            IntersectInfo info;
            info.distance = INF_DISTANCE;
            //getPixel(i,j).print();
            for(int k=0;k<objlist.size();k++){
                IntersectInfo temp_info = objlist[k]->calcIntersect(r);
                if(temp_info.distance < info.distance) info = temp_info;
            }

            double temp_inf = INF_DISTANCE;
            if(temp_inf == info.distance){continue;}

            Color shading_color;
            if(info.isDirectLight)
                shading_color = info.color;
            else
                shading_color = calcShading(info,objlist,shader);
            
            film.setPixel(i,j,shading_color);
            //info.color.print();

        }
    }
}

Vector3D Camera::getPosition() const{return p_position;}
Vector3D Camera::getReferencePoint()const{return p_reference;}
double Camera::getFovY()const{return fov_y;}
double Camera::getDeltaY()const{return delta_y;}
Vector3D Camera::getU()const{return u;}
Vector3D Camera::getV()const{return v;}
Vector3D Camera::getW()const{return w;}
Image Camera::getFilm()const{return film;}
void Camera::clearFilm(Color const& bg_color){film.clear(bg_color);
//film.print();
}

Color calcShading(IntersectInfo const& info,vector<Primitive*> const & objlist,ShadingEnvironment const& shader){

    RGB_container reflect_rate = RGB_container(info.color) * (1.0/255.0); //reflect rate = RGB / 255

    //Ambient light
    RGB_container ambient = reflect_rate * shader.ambient;

    //Diffuse light
    Color source_light = shader.light_source.getColor() * shader.LUMINANCE_CONSTANT;
    RGB_container diffuse = RGB_container(
        source_light.getR() * reflect_rate.getR(), source_light.getG() * reflect_rate.getG(),source_light.getB() * reflect_rate.getB());

    //Shadow check
    bool isBlocked = false;
    Vector3D light_direction = shader.light_source.getCenter() - info.point;
    Ray r;
    r.direction = light_direction.normalize();
    r.origin = info.point;
    IntersectInfo shadow_info;
    shadow_info.distance = light_direction.length();
    const double ZERO = 0.001;

    for(int k=0;k<objlist.size();k++){
        IntersectInfo temp_info = objlist[k]->calcIntersect(r);
        if(temp_info.isDirectLight) continue; //skip light source
        if((temp_info.point - r.origin).length() < ZERO) continue; //skip self check !!!!!
        if(temp_info.distance < shadow_info.distance){ //shadow occur
            isBlocked = true;
            //r.origin.print();
            break;
        }
    }

    double multiplier;
    if(!isBlocked){
        multiplier = info.normal.dot(light_direction) / pow(light_direction.length() * shader.DISTANCE_CONSTANT,2);
        if(multiplier < 0) multiplier = 0; //avoid negative light
    }else
        multiplier = 0;
    
    diffuse = diffuse * multiplier;
    return (ambient + diffuse);
}