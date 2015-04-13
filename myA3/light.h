#ifndef LIGHT_H
#define LIGHT_H

#include <QVector3D>

class Light
{
public:
    Light();
    Light(QVector3D pos);
    ~Light() {}
    QVector3D position;
 };

#endif // LIGHT_H
