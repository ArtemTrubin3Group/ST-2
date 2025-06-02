// Copyright 2022 UNN-CS
#include "circle.h"
#include <cmath>
#include <cstdint>
#include <iostream>
#include <stdexcept>

namespace {
double calcFerenceFromRadius(double r) { return 2.0 * M_PI * r; }

double calcAreaFromRadius(double r) { return M_PI * r * r; }

double calcRadiusFromFerence(double f) { return f / (2.0 * M_PI); }

double calcRadiusFromArea(double a) { return std::sqrt(a / M_PI); }
} // namespace

Circle::Circle(double radius) : radius(0.0), ference(0.0), area(0.0) {
  try {
    setRadius(radius);
  } catch (const std::invalid_argument &e) {
    std::cerr << "Constructor err: " << e.what() << std::endl;
    throw;
  }
}

void Circle::setRadius(double radius) {
  try {
    if (radius < 0.0) {
      throw std::invalid_argument("Radius can't be negative");
    }
    this->radius = radius;
    ference = calcFerenceFromRadius(this->radius);
    area = calcAreaFromRadius(this->radius);
  } catch (const std::invalid_argument &e) {
    std::cerr << "setRadius err: " << e.what() << std::endl;
    throw;
  }
}

void Circle::setFerence(double ference) {
  try {
    if (ference < 0.0) {
      throw std::invalid_argument("Ference can't be negative");
    }
    this->ference = ference;
    radius = calcRadiusFromFerence(this->ference);
    area = calcAreaFromRadius(radius);
  } catch (const std::invalid_argument &e) {
    std::cerr << "setFerence err: " << e.what() << std::endl;
    throw;
  }
}

void Circle::setArea(double area) {
  try {
    if (area < 0.0) {
      throw std::invalid_argument("Area can't be negative");
    }
    this->area = area;
    radius = calcRadiusFromArea(this->area);
    ference = calcFerenceFromRadius(radius);
  } catch (const std::invalid_argument &e) {
    std::cerr << "setArea err: " << e.what() << std::endl;
    throw;
  }
}

double Circle::getRadius() const { return radius; }

double Circle::getFerence() const { return ference; }

double Circle::getArea() const { return area; }
