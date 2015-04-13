#ifndef SPHERE_H
#define SPHERE_H
#include "geometry.h"
class Sphere: public Geometry
{
public:
    Sphere(QVector3D center, qreal rad);
    Sphere ();
    ~Sphere() {}

    Geometry::RayQueryResults getIntersectionInfo(Ray &ray) ;
    QVector3D getNormal(QVector3D &point) ;

    QVector3D center;
    qreal rad;
private:
    Geometry::RayQueryResults results;
    qreal B;
    qreal C;
    qreal disc;
    qreal t1;
    qreal t2;
    QVector3D normal;
};


#endif // SPHERE_H
