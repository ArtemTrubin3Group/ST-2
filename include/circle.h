// Copyright 2022 UNN-CS
#ifndef INCLUDE_CIRCLE_H_
#define INCLUDE_CIRCLE_H_

#include <cstdint>

class Circle {
 public:
  explicit Circle(double r);

  void setRadius(double r);
  void setFerence(double f);
  void setArea(double a);

  double getRadius() const;
  double getFerence() const;
  double getArea() const;

 private:
  double radius;
  double ference;
  double area;

  void updateByRadius();
  void updateByFerence();
  void updateByArea();
};

#endif  // INCLUDE_CIRCLE_H_
