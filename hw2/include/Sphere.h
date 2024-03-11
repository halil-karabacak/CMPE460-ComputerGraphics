#pragma once

#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include "Material.h"
#include "Vector3d.h"

struct Sphere {
    Vector3d center;
    float radius;
    Material material;
    Sphere(const Vector3d& center, float radius, const Material& material) : center(center), radius(radius), material(material) {}

    bool intersect(const Ray& ray, float& t) const {
        Vector3d oc = ray.orig - center;
        float b = oc.dot(ray.dir);
        float c = oc.dot(oc) - radius*radius;
        float h = b*b - c;
        if (h < 0.0) return false;
        h = sqrt(h);
        t = -b - h;
        if (t < 0.0) t = -b + h;
        if (t < 0.0) return false;
        return true;
    }
};