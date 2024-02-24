#include "World.h"

World::World(std::shared_ptr<Camera> camera, std::shared_ptr<Screen> screen,  std::vector<std::shared_ptr<Sphere>> objects) {
    this->camera = camera;
    this->screen = screen;
    this->objects = objects;

    const char * path = "selam.png \0";
    this->screen->ExportFrame(path);
}


