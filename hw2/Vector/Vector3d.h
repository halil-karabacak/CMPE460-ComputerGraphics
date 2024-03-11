#ifndef VECTOR3D_H
#define VECTOR3D_H

/**
 * Header-only, simple Vector3Double implemenation.
*/
#include <cmath>
#include <iostream>

class Vector3d
{
 protected:
    double x_, y_, z_;

 public:
    Vector3d(double _x, double _y, double _z)
     : x_(_x), y_(_y), z_(_z) 
    {
    
    }
    Vector3d()
     : x_(0), y_(0), z_(0) 
    {
    
    }  

    double x() const  { return x_; }
    double y() const { return y_; }
    double z() const { return z_; }
    
    Vector3d sub(const Vector3d &v) 
    {
        return Vector3d(x_-v.x(), y_-v.y(), z_-v.z());
    }

    Vector3d add(const Vector3d &v) {
        return Vector3d(x_+v.x(), y_+v.y(), z_+v.z());
    }

    Vector3d scale(double t) {
        return Vector3d(x_*t, y_*t, z_*t);
    }

    Vector3d unit_vector() {
        double len = length();
        return Vector3d(x_/len, y_/len, z_/len);

    }

    Vector3d operator-() const { return Vector3d(-x_, -y_, -z_); }

    Vector3d& operator+=(const Vector3d &v) {
        x_ += v.x();
        y_ += v.y();
        z_ += v.z();
        return *this;
     }

    Vector3d& operator*=(const double t) {
        x_ *= t;
        y_ *= t;
        z_ *= t;
        return *this;
    }

    Vector3d& operator/=(const double t) {
        return *this *= 1/t;
    }

    Vector3d operator / (float d) const { return Vector3d(x_ / d, y_ / d, z_ / d); }
    Vector3d operator + (const Vector3d& v) const { return Vector3d(x_ + v.x(), y_ + v.y(), z_ + v.z()); }
    Vector3d operator - (const Vector3d& v) const { return Vector3d(x_ - v.x(), y_ - v.y(), z_ - v.z()); }
    Vector3d operator * (const Vector3d& v) const { return Vector3d(x_ * v.x(), y_ * v.y(), z_ * v.z()); }
    Vector3d operator * (float d) const { return Vector3d(x_ * d, y_ * d, z_ * d); }
    Vector3d operator * (double d) const { return Vector3d(x_ * d, y_ * d, z_ * d); }

    double length(){
        return sqrt(x_*x_ + y_*y_ + z_*z_);
    }
    

    friend std::istream& operator>>(std::istream& is, Vector3d& v);
    
    float dot(const Vector3d& v) const { return x_ * v.x() + y_ * v.y() + z_ * v.z(); }
    Vector3d& operator<<(const unsigned char value) {
        if (x_ == 0) x_ = value;
        else if (y_ == 0) y_ = value;
        else if (z_ == 0) z_ = value;
        return *this;
    }

    Vector3d normalize() const { return *this / sqrt(dot(*this)); }
};

inline std::istream& operator>>(std::istream& is, Vector3d& v) {
    is >> v.x_ >> v.y_ >> v.z_;
    return is;
}


#endif