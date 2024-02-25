#ifndef WORLD_H
#define WORLD_H

#include "Utils.h"
#include <vector>
#include <memory>

class World {
    public:
        World(std::shared_ptr<Camera> camera, std::shared_ptr<Screen> screen,  std::vector<std::shared_ptr<Sphere>> objects);    
        Color traceRay(double startX, double startY, double startZ, double dirX, double dirY, double dirZ, const std::vector<std::shared_ptr<Sphere>>& spheres);
        void generateFrame();
        void exportFrame(const char*);
    private:
        std::shared_ptr<Camera> camera;
        std::shared_ptr<Screen> screen;
        std::vector<std::shared_ptr<Sphere>> objects;
};

#endif