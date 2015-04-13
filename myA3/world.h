#ifndef WORLD_H
#define WORLD_H
#include "camera.h"
#include "sphere.h"
#include "light.h"
#include "material.h"
#include <vector>
class World
{
public:
    World();
    ~World() {}
    Camera camera;
    // HACK: We are just going to store a list of materials
    // instead of directly associating them to geometric
    // objects and rely on the having no errors :)
    std::vector<Material> materials;
    std::vector<Sphere> spheres;
    std::vector<Light> lights;
};

#endif // WORLD_H
