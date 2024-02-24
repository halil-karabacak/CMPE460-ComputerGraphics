#include "World.h"

World::World(std::shared_ptr<Camera> camera, std::shared_ptr<Screen> screen,  std::vector<std::shared_ptr<Sphere>> objects) {
    this->camera = camera;
    this->screen = screen;
    this->objects = objects;
}


Utils::Color World::traceRay(double startX, double startY, double startZ, double dirX, double dirY, double dirZ, const std::vector<std::shared_ptr<Sphere>>& spheres) {
    double minDistance = INFINITY;
    Utils::Color pixelColor = {0, 0, 0};

    for (const auto& sphere : spheres) {
        double ocX = startX - sphere->position.x();
        double ocY = startY - sphere->position.y();
        double ocZ = startZ - sphere->position.z();

        double a = dirX * dirX + dirY * dirY + dirZ * dirZ;
        double b = 2 * (ocX * dirX + ocY * dirY + ocZ * dirZ);
        double c = ocX * ocX + ocY * ocY + ocZ * ocZ - sphere->radius * sphere->radius;

        double discriminant = b * b - 4 * a * c;
        if (discriminant > 0) {
            double temp = (-b - sqrt(discriminant)) / (2 * a);
            if (temp > 0 && temp < minDistance) {
                minDistance = temp;
                pixelColor = sphere->color;
            }
        }
    }

    return pixelColor;
}


void World::generateFrame() {
    for (int y = 0; y < this->screen->screenHeight_const; ++y) {
        for (int x = 0; x < this->screen->screenWidth_const; ++x) {
            double screenTopLeftX = this->screen->ScreenLeftBottom_const.x();
            double screenBottomRightX = this->screen->ScreenRightTop_const.x();
            double screenTopLeftY = this->screen->ScreenRightTop_const.y();
            double screenBottomRightY = this->screen->ScreenLeftBottom_const.y();
            double screenTopLeftZ = 100;

            double dirX = screenTopLeftX + (screenBottomRightX - screenTopLeftX) * (x + 0.5) / this->screen->screenWidth_const;
            double dirY = screenTopLeftY + (screenBottomRightY - screenTopLeftY) * (y + 0.5) / this->screen->screenHeight_const;
            double dirZ = screenTopLeftZ;

            Utils::Color pixelColor = traceRay(this->camera->cameraPos.x(), this->camera->cameraPos.y(), this->camera->cameraPos.z(), dirX, dirY, dirZ, objects);
            this->screen->frame[y * this->screen->screenHeight_const + x] = pixelColor;
        }
    }
}

void World::exportFrame(const char* name) {
    this->screen->ExportFrame(name);
}