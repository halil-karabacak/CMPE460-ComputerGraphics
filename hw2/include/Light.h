# pragma once
#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include "Vector3d.h"

struct Light {
    Vector3d position;
    Vector3d color;
    Light(const Vector3d& position, const Vector3d& color) : position(position), color(color) {}
};