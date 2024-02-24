#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <Eigen/Dense>


enum Result {
    SUCCESS,
    FAIL,
    DEFAULT
};

namespace Utils {
    typedef Eigen::Matrix<unsigned char, 3, 1> Color; 
}

struct Sphere {
    Eigen::Vector3d position;
    double radius;
    Utils::Color color;
    Sphere(Eigen::Vector3d position_, double _radius, Utils::Color _color)
        : position(position_), radius(_radius), color(_color) {}
};


struct Screen {
    const Eigen::Vector3d ScreenLeftBottom_const;
    const Eigen::Vector3d ScreenRightTop_const;
    const Eigen::Vector3d ScreenCenter_const;
    static const int screenWidth_const = 1000;
    static const int screenHeight_const = 1000;
    std::array<Utils::Color, screenHeight_const * screenWidth_const> frame;
    
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
            buffer[index++] = color(0);
            buffer[index++] = color(1);
            buffer[index++] = color(2);
        }   
    
        return buffer;
    }

};

struct Camera {
    const Eigen::Vector3d cameraPos;
    Camera () : cameraPos(0, 0, 0) {}
};


#endif // UTILS_H