# pragma once
#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include "Vector3d.h"

struct Ray {
    Vector3d orig, dir;
    Ray(const Vector3d& orig, const Vector3d& dir) : orig(orig), dir(dir.normalize()) {}
};
