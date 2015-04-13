    #include "material.h"

Material::Material()
{
    // defaults changed later, publicly.
    surface_color = QVector3D(100,100,100);
    diffuse_amount = 0.5;
    ambient_color = QVector3D(0,255,0);
    ambient_amount = 0.5;

    specular_color = QVector3D(0,0,255);
    shininess = 1;
    specular_amount = 0.5;

    reflection = 1;
}

Material::~Material()
{

}
