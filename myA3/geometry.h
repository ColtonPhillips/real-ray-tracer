#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <QVector3D>

class Ray;

// An interface that Sphere and future objects inherit
class Geometry
{
public:

    struct RayQueryResults
    {
        RayQueryResults():hit(false), distance(-1){}
        bool hit;
        qreal distance;
    };
    virtual RayQueryResults getIntersectionInfo(Ray &ray)  =0;
    virtual QVector3D getNormal(QVector3D& point)  =0;
};

#endif // GEOMETRY_H
