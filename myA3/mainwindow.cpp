#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "camera.h"
#include "sphere.h"
#include "light.h"
#include <QTimer>
#include <Qt>
#include <QTime>
#include <QTransform>
#include <qmath.h>
// HACK: this will crash if not enough lights or spheres are kicking around...

qreal near_plane_dist = 0.6;
QVector3D my_start = QVector3D(0,0,-2000);
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFocus();
    image_width = 192;
    image_height = 60;
    world = World();
    world.camera = Camera(my_start,QVector3D(0,0,1),static_cast<qreal>(image_width)/image_height,near_plane_dist);

    // You can EDIT these to change how our ray tracer looks!
    world.lights.push_back(Light(QVector3D(0,0,-100000)));
    world.lights.push_back(Light(QVector3D(0,1000000,0)));
    world.lights.push_back(Light(QVector3D(10000000,0,0)));

    // Materials and Spheres is kinda complicated/funny...
    Material m = Material();
    m.surface_color = QVector3D(255,255,255);
    m.diffuse_amount = 1;
    m.ambient_amount= 0.8;
    m.specular_amount = 5;
    m.specular_color = QVector3D(255,100,100);
    m.shininess = 1;
    world.materials.push_back(m);
    world.spheres.push_back(Sphere(QVector3D(0,0,0),200));
    m.shininess = 1000;
    m.ambient_amount = 0.1;
    m.specular_amount = 0.1;
    world.materials.push_back(m);
    world.spheres.push_back(Sphere(QVector3D(0,100,0),200));
    m.surface_color = QVector3D(255,20,20);
    m.shininess = 100.1;
    m.diffuse_amount = 0.01;
    m.ambient_color = QVector3D(255,0,0);
    world.materials.push_back(m);
    world.spheres.push_back(Sphere(QVector3D(0,0,10000),2000));
    m.shininess = 0.00001;
    m.ambient_amount = 0.0001;
    m.specular_amount = 0.0001;
    m.diffuse_amount = 0.0001;
    m.surface_color = QVector3D(0,220,0);
    m.ambient_color = QVector3D(0,244,0);
    world.materials.push_back(m);
    world.spheres.push_back(Sphere(QVector3D(11100,11110,80000),12000));
    Material m1 = Material();
    m1.ambient_amount=1;
    m1.ambient_color=QVector3D(255,60,60);
    m1.diffuse_amount=1;
    m1.shininess = 1;
    m1.specular_color=QVector3D(110,120,130);
    m1.surface_color = QVector3D(2,255,255);
    world.materials.push_back(m1);
    world.spheres.push_back(Sphere(QVector3D(0,0,-800),120));
    Material m2 = Material();
    m2.ambient_color = QVector3D(10,20,10);
    m2.shininess = 3000;
    m2.surface_color = QVector3D(10,20,20);
    world.materials.push_back(m2);
    world.spheres.push_back(Sphere(QVector3D(0,0,-1600),10));
    Material m3;
    m3.specular_amount = 0.1;
    m3.ambient_amount = 0.1;
    m3.ambient_color = QVector3D(255,10,10);
    m3.shininess = 3000;
    world.materials.push_back(m3);
    world.spheres.push_back(Sphere(my_start+QVector3D(0,0,40),2));
    Material m4 = Material();
    m4.shininess = 0;
    world.materials.push_back(m4);
    world.spheres.push_back(Sphere(my_start+QVector3D(0,1,41),3));
    Material m5 = Material();
    m5.ambient_amount = 0.3;
    m5.ambient_color = QVector3D(0,0,5);
    m5.diffuse_amount = 0.01;
    m5.shininess = 20000000000;
    m5.specular_amount = 0.01;
    m5.specular_color = QVector3D(0,200,230);
    m5.surface_color = QVector3D(0,0,255);
    world.materials.push_back(m5);
    world.spheres.push_back(Sphere(QVector3D(0,0,0),62));
    Material m6 = Material();
    m6.ambient_amount = 1;
    m6.ambient_color = QVector3D(0,0,55);
    m6.diffuse_amount = 0.1;
    m6.shininess = 200000;
    m6.specular_amount = 0.1;
    m6.specular_color = QVector3D(0,20,230);
    m6.surface_color = QVector3D(0,0,25);
    world.materials.push_back(m6);
    world.spheres.push_back(Sphere(QVector3D(10,710,10),462));


    raytracer = RayTracer(&world, image_width,image_height);
    raytracer.run();
    ui->myLabel->setPixmap(QPixmap::fromImage(raytracer.renderImage.scaledToHeight(240)));

    QTimer::singleShot(10,this,SLOT(loopforever())); // call our update function once
}

MainWindow::~MainWindow()
{
    delete ui;
}

qreal random_float(qreal LO, qreal HI) {
    float r = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
    return r;
}

void MainWindow::keyPressEvent(QKeyEvent *e) {
    QVector3D cross = QVector3D(1,1,1);
    cross = world.camera.ray.start.crossProduct(world.camera.ray.direction,QVector3D(0,1,0));
     if (e->key() == Qt::Key_Space) {
         Material m = Material();
         m.ambient_amount = random_float(0.0,1.0);
         m.diffuse_amount = random_float(0.0,1.0);
         m.specular_amount = random_float(0.0,1.0);
         m.shininess = random_float(1.0,10000);
         m.surface_color= QVector3D(random_float(0,255),random_float(0,255),random_float(0,255));
         m.ambient_color= QVector3D(random_float(0,255),random_float(0,255),random_float(0,255));
         m.specular_color= QVector3D(random_float(0,255),random_float(0,255),random_float(0,255));
         world.materials.push_back(m);
         world.spheres.push_back(Sphere(
           QVector3D(world.camera.ray.start + world.camera.ray.direction * 100),random_float(1,100)));
     }
     if (e->key() == Qt::Key_Control) {
         world.camera.ray.start = world.camera.ray.start + QVector3D(0,12,0);
         QVector3D newdir = QVector3D(0,0,0) - world.camera.ray.start;
         newdir.normalize();
         world.camera.ray.direction = newdir;
     }
     if (e->key() == Qt::Key_Alt) {
         world.camera.ray.start = world.camera.ray.start + QVector3D(0,-12,0);
         QVector3D newdir = QVector3D(0,0,0) - world.camera.ray.start;
         newdir.normalize();
         world.camera.ray.direction = newdir;
     }
     if (e->key() == Qt::Key_Left ) {
         world.camera.ray.start = world.camera.ray.start - 8*cross;
         QVector3D newdir = QVector3D(0,0,0) - world.camera.ray.start;
         newdir.normalize();
         world.camera.ray.direction = newdir;
    }
     if (e->key() == Qt::Key_Right ) {
        world.camera.ray.start = world.camera.ray.start + 8*cross;
        QVector3D newdir = QVector3D(0,0,0) - world.camera.ray.start;
        newdir.normalize();
        world.camera.ray.direction = newdir;
    }
     if (e->key() == Qt::Key_Up ) {
        world.camera.ray.start = world.camera.ray.start + 20*world.camera.ray.direction;
    }
     if (e->key() == Qt::Key_Z ) {
        world.camera.ray.start = world.camera.ray.start + 1.5*world.camera.ray.direction;
    }
     if (e->key() == Qt::Key_Down ) {
        world.camera.ray.start = world.camera.ray.start - 80*world.camera.ray.direction;
    }
     if (e->key() == Qt::Key_S ) {
        raytracer.my_depth = 6;
        raytracer.renderImage = QImage(1920*2, 600*2, QImage::Format_RGB888);
        raytracer.run();
        bool b = raytracer.renderImage.save(QString("outrays.png"), "PNG", 100);
        raytracer.my_depth = 1;
        raytracer.renderImage = QImage(19,6,QImage::Format_RGB32);
     }
     if (e->key() == Qt::Key_A) {
         if(raytracer.is_aa) {
             raytracer.is_aa = false;
         } else {
             raytracer.is_aa = true;
         }
     }
}

// this replicates a update loop
void MainWindow::loopforever()
{
    //"gravity"
    for(___i = 0; ___i < world.spheres.size(); ___i++) {
        world.spheres[___i].center.setZ(0.9999*world.spheres[___i].center.z());
    }

    raytracer.run();
    ui->myLabel->setPixmap(QPixmap::fromImage(raytracer.renderImage.scaledToHeight(240)));

    QTimer::singleShot(1,this,SLOT(loopforever()));
}

void MainWindow::on_myButton_clicked()
{
    for(std::vector<Sphere>::size_type i = 0; i < world.spheres.size(); i++) {
        float delta = 140;
        float r = -delta + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(delta-(-delta))));
        float r1 = -delta + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(delta-(-delta))));
        float r2 = -delta + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(delta-(-delta))));
        world.spheres[i].center = QVector3D(r1,r2/2,r);
        if (world.spheres[i].rad > 10.0) {
                world.spheres[i].rad = 10;}
    }

    world.camera.ray.start = QVector3D(0,0,-130);
    QVector3D newdir = QVector3D(0,0,0) - world.camera.ray.start;
    newdir.normalize();
    world.camera.ray.direction = newdir;
    setFocus();
}


void MainWindow::on_mySlider_valueChanged(int value)
{
  qreal val = static_cast<qreal>(value) / 120.0;
  raytracer.my_depth = 3 + val*2;
  raytracer.renderImage = QImage(image_width+val*512, image_height+val*160, QImage::Format_RGB32);
  setFocus();
}



void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    qreal val = static_cast<qreal>(value) / 150.0;
    world.camera.near_clip = near_plane_dist + sqrt(70*val);
    setFocus();
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    for(std::vector<Light>::size_type i = 0; i < world.lights.size(); i++) {
        world.lights[i].position.setX(world.lights[i].position.x()+100*value);
    }
    setFocus();
}
