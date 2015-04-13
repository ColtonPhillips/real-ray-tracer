#include "sphere.h"
#include "ray.h"
#include "cmath"
#include "utils.h"

Sphere::Sphere(QVector3D _center, qreal _rad)
{
    center = _center;
    rad = _rad;
}

Sphere::Sphere()
{// never called
   // center = QVector3D(0,0,0);
   // rad = 1;
}

Geometry::RayQueryResults Sphere::getIntersectionInfo(Ray &ray)
{
    results = Geometry::RayQueryResults();
    //A=1, so no need to calculate
    B = 2*(ray.direction.x() * (ray.start.x() - center.x()) + ray.direction.y() * (ray.start.y() - center.y())  + ray.direction.z() * (ray.start.z() - center.z()));
    C = pow(ray.start.x() - center.x(),2) + pow(ray.start.y() - center.y(),2) + pow(ray.start.z() - center.z(),2) - pow(rad,2);
    disc = pow(B,2) - 4*C;
    if(disc>0)
    {
        results.hit = true;
        t1 = (-B - sqrt(disc))/2;
        t2 = (-B + sqrt(disc))/2;
        results.distance = utils::min(t1,t2);
        if(results.distance<0)
        {
            results.distance = utils::max(t1,t2);
            if(results.distance<0)
            {
                results.hit = false;
            }
        }
    }

    return results;
}

QVector3D Sphere::getNormal(QVector3D &point)
{
    normal = point-center;
    normal.normalize();
    return normal;
}
