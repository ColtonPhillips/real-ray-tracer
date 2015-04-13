#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "world.h"
#include "raytracer.h"
#include <QKeyEvent>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    World world;
    RayTracer raytracer;
    QImage createImageWithOverlay(const QImage& baseImage, const QImage& overlayImage);
    qreal image_width;
    qreal image_height;
    int fun_count;

protected:
    void keyPressEvent(QKeyEvent *e);


private:
    Ui::MainWindow *ui;

    int _n;// DANGEROUS use of optimization.
    std::vector<Sphere>::size_type ___i;
public slots:
    void loopforever();
private slots:
    void on_myButton_clicked();
    void on_mySlider_valueChanged(int value);
    void on_horizontalSlider_valueChanged(int value);
    void on_horizontalSlider_2_valueChanged(int value);
};

#endif // MAINWINDOW_H
