# pragma once
#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include "Vector3d.h"

struct Material {
    Vector3d ambient;
    Vector3d diffuse;
    Material(const Vector3d& ambient, const Vector3d& diffuse) : ambient(ambient), diffuse(diffuse) {}
};