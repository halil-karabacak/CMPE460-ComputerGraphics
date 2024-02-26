#include <iostream>
#include "World.h"

void PlaceObjects(std::vector<std::shared_ptr<Sphere>>& objects);

int main() {
    // create Camera and Screen
    std::shared_ptr<Camera> camera = std::make_shared<Camera>();
    std::shared_ptr<Screen> screen = std::make_shared<Screen>();
    std::vector<std::shared_ptr<Sphere>> objects;

    // this part takes input from the user via command-line
    PlaceObjects(objects);
    // create the 3D world with camera, screen, and spheres
    std::shared_ptr<World> world = std::make_shared<World>(camera, screen, objects);

    // capture the frame seen by the eye
    world->generateFrame();
    

    const char * path = "frame.png";
    // save it file
    world->exportFrame(path);

    return 0;
}


void PlaceObjects(std::vector<std::shared_ptr<Sphere>>& objects) {
    std::ifstream infile("../input.txt");
    if (!infile.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }

    int numObjects;
    infile >> numObjects;
    int r, g, b;
    double x, y, z, radius;
    for (int i = 0; i < numObjects; ++i) {
        infile >> r >> g >> b;
        infile >> x >> y >> z;
        infile >> radius;
        
        Vector3d position{x, y, z};
        Color color_UC{static_cast<unsigned char>(r), static_cast<unsigned char>(g),  static_cast<unsigned char>(b)};

        objects.emplace_back(std::make_shared<Sphere>(position, radius, color_UC));
    }

    infile.close();
}
