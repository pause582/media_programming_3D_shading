#ifndef _VECTOR3D_H_
#define _VECTOR3D_H_

using namespace std;

class Vector3D{
    private:
    Vector3D rotateX(double degree) const;
    Vector3D rotateY(double degree) const;
    Vector3D rotateZ(double degree) const;
    public:
    double x,y,z;
    Vector3D(double x=0,double y=0,double z=0);
    Vector3D(Vector3D const& v); //cpy constr
    Vector3D operator=(Vector3D const& v);

    Vector3D operator*(double a) const;
    Vector3D operator/(double a) const;
    Vector3D operator*=(double a);
    Vector3D operator/=(double a);

    Vector3D operator-() const;
    Vector3D operator+(Vector3D const& v)  const;
    Vector3D operator-(Vector3D const& v) const;
    Vector3D operator+=(Vector3D const& v);
    Vector3D operator-=(Vector3D const& v);

    Vector3D rotate_by(Vector3D const& p,double x,double y,double z) const;

    double dot(Vector3D const& v) const;
    Vector3D cross(Vector3D const& v) const;

    double length() const;
    Vector3D normalize() const;

    void print() const;

    bool operator==(Vector3D const& v) const;
    bool operator!=(Vector3D const& v) const;
};

// ----------------------------------------------

Vector3D operator*(double a,Vector3D const& v);
Vector3D operator/(double a,Vector3D const& v);

#endif