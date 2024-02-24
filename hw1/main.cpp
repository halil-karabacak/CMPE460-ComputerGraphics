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
        Eigen::Vector3d position;
        double radius;
        int r, g, b;

        Utils::Color color_UC;

        std::cout << "Enter position (x y z) of sphere " << i + 1 << ": ";
        std::cin >> position[0] >> position[1] >> position[2];

        std::cout << "Enter radius of sphere " << i + 1 << ": ";
        std::cin >> radius;

        std::cout << "Enter color (R G B) of sphere " << i + 1 << ": ";
        std::cin >> r >> g >> b;

        color_UC << static_cast<unsigned char>(r), static_cast<unsigned char>(g),  static_cast<unsigned char>(b);

        objects.emplace_back(std::make_shared<Sphere>(position, radius, color_UC));
    }
}
