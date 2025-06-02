// Copyright 2022 UNN-CS
#include "tasks.h"
#include <cmath>
#include "circle.h"

double ropeGap() {
  const double earthRadiusKm = 6378.1;
  const double earthRadiusM = earthRadiusKm * 1000.0;
  Circle earthCircle(earthRadiusM);
  double oldFerence = earthCircle.getFerence();
  earthCircle.setFerence(oldFerence + 1.0);
  double newRadius = earthCircle.getRadius();
  double gap = newRadius - earthRadiusM;
  return gap;
}

double poolConcreteCost() {
  const double poolRadius = 3.0;
  const double walkwayWidth = 1.0;
  double outerRadius = poolRadius + walkwayWidth;
  Circle poolCircle(poolRadius);
  Circle outerCircle(outerRadius);
  double poolArea = poolCircle.getArea();
  double outerArea = outerCircle.getArea();
  double walkwayArea = outerArea - poolArea;
  double costPerSquareMeter = 1000.0;
  double totalConcreteCost = walkwayArea * costPerSquareMeter;
  return totalConcreteCost;
}

double poolFenceCost() {
  const double poolRadius = 3.0;
  const double walkwayWidth = 1.0;
  double outerRadius = poolRadius + walkwayWidth;
  Circle fenceCircle(outerRadius);
  double fenceFerence = fenceCircle.getFerence();
  double costPerMeter = 2000.0;
  double totalFenceCost = fenceFerence * costPerMeter;
  return totalFenceCost;
}
