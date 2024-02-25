#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "Vector3d.h"
#include <array>


enum Result {
    SUCCESS,
    FAIL,
    DEFAULT
};

struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    Color () {}
    Color (unsigned char r_, unsigned char g_, unsigned char b_) : r(r_), g(g_), b(b_) {}
};

struct Sphere {
    Vector3d position;
    double radius;
    Color color;
    Sphere(Vector3d position_, double _radius, Color _color)
        : position(position_), radius(_radius), color(_color) {}
};


struct Screen {
    const Vector3d ScreenLeftBottom_const;
    const Vector3d ScreenRightTop_const;
    const Vector3d ScreenCenter_const;
    static const int screenWidth_const = 1000;
    static const int screenHeight_const = 1000;
    std::array<Color, screenHeight_const * screenWidth_const> frame;
    
    Screen()
        : ScreenLeftBottom_const(-50, -50, 100),
          ScreenRightTop_const(50, 50, 100),
          ScreenCenter_const(0, 0, 100) {}
    

    Result ExportFrame(const char* file_path);
    unsigned char* convertFrameToUnsignedChar() {
        constexpr int bufferSize = screenHeight_const * screenWidth_const * 3;
        unsigned char* buffer = new unsigned char[bufferSize];
    
        int index = 0;
        for (const auto& color : frame) {
            buffer[index++] = color.r;
            buffer[index++] = color.g;
            buffer[index++] = color.b;
        }   
    
        return buffer;
    }

};

struct Camera {
    const Vector3d cameraPos;
    Camera () : cameraPos(0, 0, 0) {}
};


#endif // UTILS_H