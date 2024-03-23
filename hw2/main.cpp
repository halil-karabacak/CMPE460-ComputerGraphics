
#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <cmath>
#include <fstream>
#include "RayTracer.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


std::vector<Sphere> spheres;
Light light(Vector3d(500, 500, 500), Vector3d(1, 1, 1));
const Vector3d ambientLight(0.3, 0.3, 0.3);
const Vector3d backgroundColor(0.0, 0.0, 0.1);
const int maxDepth = 5;


bool sceneIntersect(const Ray& ray, Vector3d& hit, Vector3d& normal, Material& material);

Vector3d calculateLighting(const Vector3d& point, const Vector3d& normal, const Material& material, const Vector3d& viewDir) {
    Vector3d lightDir = (light.position - point).normalize();
    float distanceToLight = (light.position - point).length();
    float diff = std::max(lightDir.dot(normal), 0.0f);

    // Shadow check
    bool inShadow = false;
    Ray shadowRay(point + normal * 0.001f, lightDir);
    Vector3d shadowHit, shadowNormal;
    Material tempMaterial  = Material(Vector3d(0, 0, 0.9), Vector3d(0.6, 0.6, 0.6)); // Greyish;
    if (sceneIntersect(shadowRay, shadowHit, shadowNormal, tempMaterial)) {
        float shadowDist = (shadowHit - point).length();
        if (shadowDist < distanceToLight) {
            inShadow = true;
        }
    }

    Vector3d diffuse(0, 0, 0);
    if (!inShadow) {
        Vector3d scaledDiffuse = material.diffuse * diff;
        diffuse = Vector3d(scaledDiffuse.x() * light.color.x(), scaledDiffuse.y() * light.color.y(), scaledDiffuse.z() * light.color.z());
    }

    return material.ambient * ambientLight + diffuse;
}


bool sceneIntersect(const Ray& ray, Vector3d& hit, Vector3d& normal, Material& material) {
    float sphereDist = std::numeric_limits<float>::max();
    for (const auto& sphere : spheres) {
        float distI;
        if (sphere.intersect(ray, distI) && distI < sphereDist) {
            sphereDist = distI;
            hit = ray.orig + ray.dir * distI;
            normal = (hit - sphere.center).normalize();
            material = sphere.material;
        }
    }

    float planeDist = -(ray.orig.y() + 35) / ray.dir.y();
    Vector3d planePoint = ray.orig + ray.dir * planeDist;
    if (planeDist > 0 && planeDist < sphereDist) {// && planePoint.x() >= -150 && planePoint.x() <= 150 && planePoint.z() >= 50 && planePoint.z() <= 150) {
        hit = planePoint;
        normal = Vector3d(0, 1, 0); // Upwards  
        material = Material(Vector3d(0.5, 0.5, 0.5), Vector3d(0.6, 0.6, 0.6)); // Greyish
        return true;
    }

    return sphereDist < std::numeric_limits<float>::max();
}

Vector3d castRay(const Ray& ray, int depth) {
    if (depth > maxDepth) {
        return backgroundColor;
    }

    Vector3d point, normal;
    Material material(Vector3d(0, 0, 0), Vector3d(0, 0, 0));

    if (!sceneIntersect(ray, point, normal, material)) {
        return backgroundColor;
    }

    Vector3d reflectDir = ray.dir - normal * 2.f * ray.dir.dot(normal);
    Ray reflectRay(point + normal * 0.001f, reflectDir);

    Vector3d reflectColor = castRay(reflectRay, depth + 1);
    Vector3d color = calculateLighting(point, normal, material, -ray.dir);
    return color + reflectColor * 0.5;
}

void render(const int width, const int height) {
    std::vector<Vector3d> framebuffer(width * height);

    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            float x = (2*(i + 0.5)/(float)width - 1) * width / (float)height;
            float y = -(2*(j + 0.5)/(float)height - 1);
            Ray ray(Vector3d(0, 0, 0), Vector3d(x, y, 1));
            framebuffer[i+j*width] = castRay(ray, 0);
        }
    }

    int bufferSize = width * height * 3;
    unsigned char* buffer = new unsigned char[bufferSize];
    
    int index = 0;
    for (const auto& color : framebuffer) {
        buffer[index++] = static_cast<unsigned char>(255.599 * color.x());
        buffer[index++] = static_cast<unsigned char>(255.599 * color.y());
        buffer[index++] = static_cast<unsigned char>(255.599 * color.z());
    }   

    if (stbi_write_png("../output.png", width, height, 3, buffer, width * 3) != 0) {
    } 
}

void PlaceObjects() {
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

        spheres.push_back(Sphere(Vector3d(x, y, z), radius, Material(Vector3d((float) r/ 255, (float) g/ 255, (float) b/ 255), Vector3d(1, 1, 1))));
    }

    infile.close();
}

int main() {
    PlaceObjects();
    render(1000, 1000);

    return 0;
}