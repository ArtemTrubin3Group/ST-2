// Copyright 2022 UNN-CS
#include "circle.h"
#include <cstdint>
#include <cmath>

const double PI = 3.141592653589793;

void Circle::updateByRadius() {
    ference = 2 * PI * radius;
    area = PI * radius * radius;
}

void Circle::updateByFerence() {
    radius = ference / (2 * PI);
    area = PI * radius * radius;
}

void Circle::updateByArea() {
    radius = sqrt(area / PI);
    ference = 2 * PI * radius;
}

Circle::Circle(double r) {
    setRadius(r);
}

void Circle::setRadius(double r) {
    if (r > 0) {
        radius = r;
        updateByRadius();
    } else {
        radius = 0;
        ference = 0;
        area = 0;
    }
}

void Circle::setFerence(double f) {
    if (f > 0) {
        ference = f;
        updateByFerence();
    } else {
        radius = 0;
        ference = 0;
        area = 0;
    }
}

void Circle::setArea(double a) {
    if (a > 0) {
        area = a;
        updateByArea();
    } else {
        radius = 0;
        ference = 0;
        area = 0;
    }
}

double Circle::getRadius() const {
    return radius;
}

double Circle::getFerence() const {
    return ference;
}

double Circle::getArea() const {
    return area;
}
