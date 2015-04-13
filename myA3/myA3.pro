#-------------------------------------------------
#
# Project created by QtCreator 2015-03-20T05:46:46
#
#-------------------------------------------------

QT       += core gui opengl qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myA3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sphere.cpp \
    camera.cpp \
    ray.cpp \
    light.cpp \
    material.cpp \
    raytracer.cpp \
    world.cpp

HEADERS  += mainwindow.h \
    sphere.h \
    camera.h \
    ray.h \
    light.h \
    material.h \
    raytracer.h \
    utils.h \
    world.h \
    geometry.h

FORMS    += mainwindow.ui
