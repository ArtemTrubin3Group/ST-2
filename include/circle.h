// Copyright 2022 UNN-CS
#ifndef INCLUDE_CIRCLE_H_
#define INCLUDE_CIRCLE_H_

#include <cstdint>

class Circle {
 public:
  explicit Circle(double radius);
  void setRadius(double radius);
  void setFerence(double ference);
  void setArea(double area);
  double getRadius() const;
  double getFerence() const;
  double getArea() const;

 private:
  double radius;
  double ference;
  double area;
};

#endif  // INCLUDE_CIRCLE_H_
