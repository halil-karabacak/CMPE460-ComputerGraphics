#include <iostream>
#include "World.h"

void PlaceObjects(std::vector<std::shared_ptr<Sphere>>& objects);

int main() {
    std::shared_ptr<Camera> camera = std::make_shared<Camera>();
    std::shared_ptr<Screen> screen = std::make_shared<Screen>();
    std::vector<std::shared_ptr<Sphere>> objects;

    PlaceObjects(objects);

    std::shared_ptr<World> world = std::make_shared<World>(camera, screen, objects);
    

    return 0;
}


void PlaceObjects(std::vector<std::shared_ptr<Sphere>>& objects) {
    
}