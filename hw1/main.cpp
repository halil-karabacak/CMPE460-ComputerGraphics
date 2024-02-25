#include <iostream>
#include "World.h"

void PlaceObjects(std::vector<std::shared_ptr<Sphere>>& objects);

int main() {
    std::shared_ptr<Camera> camera = std::make_shared<Camera>();
    std::shared_ptr<Screen> screen = std::make_shared<Screen>();
    std::vector<std::shared_ptr<Sphere>> objects;

    PlaceObjects(objects);
    std::shared_ptr<World> world = std::make_shared<World>(camera, screen, objects);
    world->generateFrame();
    

    const char * path = "../exports/first_res.png \0";
    world->exportFrame(path);

    return 0;
}


void PlaceObjects(std::vector<std::shared_ptr<Sphere>>& objects) {
    int numSpheres;
    std::cout << "Enter the number of spheres: "; std::cin >> numSpheres;

    for (int i = 0; i < numSpheres; ++i) {
        double radius;
        int r, g, b;
        double x, y, z;
        
        std::cout << "Enter position (x y z) of sphere " << i + 1 << ": ";
        std::cin >> x >> y >> z;
        Vector3d position{x, y, z};


        std::cout << "Enter radius of sphere " << i + 1 << ": ";
        std::cin >> radius;

        std::cout << "Enter color (R G B) of sphere " << i + 1 << ": ";
        std::cin >> r >> g >> b;

        Color color_UC{static_cast<unsigned char>(r), static_cast<unsigned char>(g),  static_cast<unsigned char>(b)};

        objects.emplace_back(std::make_shared<Sphere>(position, radius, color_UC));
    }
}
