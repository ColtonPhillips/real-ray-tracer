#include "world.h"

World::World()
{
    spheres = std::vector<Sphere>();
    lights = std::vector<Light> ();
    // default camera reset later.
    camera = Camera(QVector3D(0,0,0),QVector3D(1,1,1),1,3);
}

