#include "ray.h"
Ray::Ray(QVector3D pos, QVector3D dir)
    :start(pos),
     direction(dir)
{
    //direction.normalize(); optimization "hack"
    // we assumpe all the vectors are normal,
    // normalizing is dividing and that is slow
}
Ray::Ray()
{// never called
    //Ray(QVector3D(0,0,0), QVector3D(0,1,0));

}

QString Ray::toString()
{
    return QString::number(start.x()) + QString::number(start.z());
    // debugging purposes
}
