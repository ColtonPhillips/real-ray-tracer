#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "ray.h"
#include <QImage>
#include "raytracer.h"
#include "world.h"
#include "geometry.h"

// Disclosure: Some of the logic was reverse engineered from this git repo:
// https://github.com/Manaluusua/Simple-Raytracer-with-Qt/
// Variable naming may even be similar in order to save time during development
// This code is vastly simpler than Manaluusua's and in my opinion
// some of the architecture is improved especially with avoiding
// nasty subclassing. Furthermore I went for a publicly exposed
// api so as the algorithms are more readable (though less safe)

class RayTracer
{
public:
    RayTracer(World * _world, qreal image_width, qreal image_height);
    RayTracer() {}
    ~RayTracer() {}
    void run();
    QImage renderImage;
    int my_depth;
    bool is_aa;

private:
    World * world;
    Ray getCameraToViewportRay(qreal image_space_x, qreal image_space_y);
    QColor getColorForPixel(qreal x, qreal y);
    QVector3D raytrace(Ray ray, int depth);
    QVector3D getDiffuseFactor(Light*const light,const QVector3D *point, const QVector3D *normal, Material mat);
    QVector3D getLightDir(Light* const light,const QVector3D* point);
    QVector3D getSpecularFactor( Light*const light,const QVector3D *point, const QVector3D *normal,const QVector3D *viewdir, Material mat);
                                // DANGEROUS otimization below
    qreal fastx, fasty;         // REASON: prevent re-creating objects and when we don't have to (thunking)
    int img_size_h;
    int img_size_w;
    Ray fastray;
    qreal winning_distance;
    int winner;
    float fastr;
    Geometry::RayQueryResults result;
    QVector3D inters_point;
    QVector3D normal;
    Material mat;
    QVector3D diffuse_col;
    QVector3D overall_col_from_light;
    QVector3D my_val;
    QVector3D light_dir;
    qreal dot;
    QVector3D color;
    QVector3D light_dir1;
    QVector3D light_dir2;
    QVector3D halfVector;
    qreal dot2;
    QVector3D col;
    std::vector<Sphere>::size_type __i;
    std::vector<Light>::size_type __j;
    int __y, __x;
};

#endif // RAYTRACER_H
