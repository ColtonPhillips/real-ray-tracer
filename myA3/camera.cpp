#include "camera.h"
Camera::Camera(QVector3D pos, QVector3D dir, qreal _aspect_ratio, qreal _near_clip)
    :aspect_ratio(_aspect_ratio),
     near_clip(_near_clip)
{
    dir.normalize();
    ray = Ray(pos,dir);
    _up = QVector3D(0,1,0);
}

Ray Camera::cameraToViewportRay(qreal relativex, qreal relativey)
{
    camera_transform = QMatrix4x4();
    x = aspect_ratio * relativex;
    y = relativey;
    viewportdir = QVector3D(x,y,-near_clip);
    viewportdir.normalize();
    camera_transform.lookAt(ray.start, ray.start+ ray.direction, _up);
        bool invertable;
    QVector3D newdir = camera_transform.inverted(&invertable).mapVector(viewportdir);
    return Ray(ray.start,newdir);
}
