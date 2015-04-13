#ifndef RAY_H
#define RAY_H

#include <QVector3D>
#include <QString>

class Ray
{
public:
    Ray(QVector3D pos, QVector3D dir);
    Ray();
    ~Ray() {}

    QVector3D start;
    QVector3D direction; // a normalized vector is expected!
    void setDirection(QVector3D newdir){newdir.normalize(); direction = newdir;}
    QString toString();
};

#endif // RAY_H
