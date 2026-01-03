#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include "Vector3D.h"
#include "Color.h"
#include "Canvas.h"

#include <cmath>

#define INF_DISTANCE 1000000.0;


//TODO: Object -> primitive -> Polygon / Sphere
// Object -> combine(?) -> Cube

typedef struct {
    Vector3D origin;
    Vector3D direction;
    int remain_reflect;
} Ray;

typedef struct {
    Vector3D point;
    Vector3D normal;
    Color color;
    double distance;
    bool isDirectLight = false;
} IntersectInfo;


class Primitive{
    protected:
    Color color;
    public:
    bool isSelfEmit = false;
    Primitive();
    virtual void move(Vector3D const& v) = 0;
    virtual void rotate_by(Vector3D const& p,double x,double y,double z) = 0;
    virtual void rotate_by_center(double x,double y,double z) = 0;
    virtual IntersectInfo calcIntersect(Ray const& r) const = 0;
};

class Polygon : public Primitive{
    private:
    vector<Vector3D> v_list;
    Vector3D normal;
    public:
    Polygon(vector<Vector3D> const& vertex_list, Color const& color = Color(0,0,0));
    //bool isValid() const;
    Vector3D getNormalVector() const;
    vector<Vector3D> getVertics() const;
    IntersectInfo calcIntersect(Ray const& r) const override;
    void rotate_by(Vector3D const& p,double x,double y,double z) override;
    void rotate_by_center(double x,double y,double z) override;
    void move(Vector3D const& delta) override; //TODO
};

class Sphere : public Primitive{
    private:
    Vector3D center;
    double radius;
    
    public:
    Sphere(Vector3D const& center, double radius, Color const& color = Color(0,0,0));
    Vector3D getCenter() const;
    double getRadius() const;
    Color getColor() const;
    void setCenter(Vector3D const& new_center);
    void setRadius(double new_raidus);
    void setColor(Color const& new_color);
    void move(Vector3D const& delta) override;
    void rotate_by(Vector3D const& p,double x,double y,double z) override;
    void rotate_by_center(double x,double y,double z) override;
    virtual IntersectInfo calcIntersect(Ray const& r) const override;
};

class Cube : public Primitive{
    private:
    vector<Polygon> surfaces;
    //vector<Vector3D> local_axis;
    Vector3D center;
    double side_len;
    public:
    Cube(Vector3D const& center, double side_length, Vector3D const& up,Vector3D const& front, vector<Color> const& colors = {Color(0,0,0)});
    Vector3D getSide() const;
    void move(Vector3D const& new_center) override;
    void rotate_by(Vector3D const& p,double x,double y,double z) override;
    void rotate_by_center(double x,double y,double z) override;
    IntersectInfo calcIntersect(Ray const& r) const override;
};

#define SIZE_POINT_LIGHT 5

class PointLight : public Sphere{
    public:
    PointLight(Vector3D const& v = Vector3D(0,0,0), Color const& c = COLOR_BLACK, double radius = SIZE_POINT_LIGHT);
    PointLight(PointLight const& p);
};


vector<Vector3D> Gram_Schmidt(vector<Vector3D> const& v_list);

#endif