#include "raytracer.h"
#include "utils.h"
#include <cstdlib>
#include <qmath.h>
int init_depth = 2; // default depth

QVector3D global_ambient_color(10,1,0);
QVector3D light_diffuse_color(15,1,200);

RayTracer::RayTracer(World * _world, qreal image_width, qreal image_height)
{
    world = _world;
    renderImage = QImage(image_width, image_height, QImage::Format_RGB32);
    my_depth = init_depth;
    fastx = 0.0;
    fasty = 0.0;
    my_val = QVector3D(100,0,0);
    is_aa = false;
}

Ray RayTracer::getCameraToViewportRay(qreal image_space_x, qreal image_space_y)
{
    fastx = (image_space_x)/(renderImage.size().width()-1);
    fasty = (image_space_y)/(renderImage.size().height()-1);
    utils::convertToViewportRelative(fastx ,fasty);
    return world->camera.cameraToViewportRay(fastx ,fasty);
}

void RayTracer::run()
{
    img_size_h = renderImage.size().height();
    img_size_w = renderImage.size().width();

    for(__y = 0; __y<img_size_h;__y++)
    {
        for(int __x=0; __x<img_size_w;__x++)
        {
           renderImage.setPixel(__x,__y, getColorForPixel(__x,__y).rgba());
        }
    }
}

QColor RayTracer::getColorForPixel(qreal x, qreal y)
{
    fastray = Ray( getCameraToViewportRay(x ,y) );
    if (is_aa) {
        Ray ray1( getCameraToViewportRay(x+0.2 ,y+0.1)); //triangle multisample
        Ray ray2 (getCameraToViewportRay(x-0.2 ,y+0.15));
        //multisample
        QVector3D my_color = raytrace(fastray,my_depth) + raytrace(ray1,my_depth)+ raytrace(ray2,my_depth);
        return utils::convertAndClampToColor(my_color/3);
    }
    else {
        return utils::convertAndClampToColor(raytrace(fastray,my_depth));
    }
}

QVector3D RayTracer::raytrace(Ray ray, int depth)
{
    if ((depth) == 0) return QVector3D(200,200,200);
    winner = -1;
    winning_distance = 999999999999999.0;
    for(__i = 0; __i < world->spheres.size(); __i++) {

        result = world->spheres[__i].getIntersectionInfo(ray);
        if (result.hit)
        {
            if (result.distance < winning_distance) {
             winner = __i;
             winning_distance = result.distance;
            }
            else { continue; }


        } else {
            // did not hit a sphere...
        }
    }

    // lets return a greenish color in the background for a loser
    if (winner == -1) {fastr = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/8));
                            if (fastr < 0.001)
        {return QVector3D(200,200,255);} else {return global_ambient_color;}}
    else {
        result = world->spheres[winner].getIntersectionInfo(ray);
        inters_point = ray.start + ray.direction * result.distance;
        normal = world->spheres[winner].getNormal(inters_point);

        mat = world->materials[winner];
        diffuse_col= mat.surface_color + mat.ambient_color;
        overall_col_from_light = QVector3D(0,0,0);
        for(__j = 0; __j < world->lights.size(); __j++) {
              overall_col_from_light = overall_col_from_light +
                      getDiffuseFactor(&(world->lights[__j]),&inters_point, &normal, mat) + //diff_l
                      getSpecularFactor(&(world->lights[__j]),&inters_point, &normal, &(ray.direction), mat);// + spec_l;
         }
        my_val = diffuse_col + overall_col_from_light/world->lights.size() + (0.4) * raytrace(Ray(inters_point+normal,normal),depth-1);
        return my_val / depth;
    }
}

QVector3D RayTracer::getDiffuseFactor(Light*const light,const QVector3D *point, const QVector3D *_normal, Material _mat)
{
    light_dir = getLightDir(light, point);
    dot = utils::clamp(_normal->dotProduct( *_normal, light_dir));
    color = _mat.surface_color * _mat.diffuse_amount * light_diffuse_color * dot;
    return color;
}


QVector3D RayTracer::getLightDir(Light* const light,const QVector3D* point)
{
    light_dir1;
    light_dir1 = light->position - *point;
    light_dir1.normalize();
    return light_dir1;
}

QVector3D RayTracer::getSpecularFactor( Light*const light,const QVector3D *point, const QVector3D *___normal,const QVector3D *viewdir, Material ___mat)
{
    light_dir2 = getLightDir(light, point);
    halfVector = light_dir2 + (-(*viewdir));
    halfVector.normalize();
    dot2 = utils::clamp(___normal->dotProduct(*___normal, halfVector));
    col = ___mat.specular_amount*(pow(dot2,mat.shininess)*___mat.specular_color);
    return col;
}
