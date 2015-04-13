#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix4x4>
#include <QVector3D>
#include "ray.h"

class Camera
{
public:
    Camera(QVector3D pos, QVector3D dir, qreal _aspect_ratio, qreal _near_clip);
    Camera() {}
    ~Camera() {}
    Ray ray;
    qreal aspect_ratio;
    qreal near_clip;
    Ray cameraToViewportRay(qreal relativex, qreal relativey);
private:
    QMatrix4x4 camera_transform;
    qreal x;
    qreal y;
    QVector3D viewportdir;
    QVector3D _up;
};

#endif // CAMERA_H
