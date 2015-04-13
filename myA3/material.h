#ifndef MATERIAL_H
#define MATERIAL_H

#include <QVector3D>

class Material
{
public:
    Material();
    ~Material();

    // properties
    QVector3D surface_color;
    qreal diffuse_amount;
    QVector3D ambient_color;
    qreal ambient_amount;

    QVector3D specular_color;
    qreal shininess;
    qreal specular_amount;

    qreal reflection;
};

#endif // MATERIAL_H
