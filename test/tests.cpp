// Copyright 2025 UNN-CS Team
#include <gtest/gtest.h>
#include <cmath>
#include <cstdint>
#include "circle.h"
#include "tasks.h"

static const double EPS = 1e-10;
static const double CONCRETE_PRICE = 1000.0;
static const double FENCE_PRICE = 2000.0;

TEST(circle_test, negative_radius_throws) {
  EXPECT_THROW(Circle(-2.0), std::invalid_argument);
}

TEST(circle_test, constructor_basic) {
  Circle c(4.0);
  EXPECT_DOUBLE_EQ(4.0, c.getRadius());
  EXPECT_DOUBLE_EQ(2.0 * M_PI * 4.0, c.getFerence());
  EXPECT_DOUBLE_EQ(M_PI * 16.0, c.getArea());
}

TEST(circle_test, set_radius_updates_others) {
  Circle c(2.0);
  c.setRadius(6.5);
  EXPECT_DOUBLE_EQ(6.5, c.getRadius());
  EXPECT_DOUBLE_EQ(2.0 * M_PI * 6.5, c.getFerence());
  EXPECT_DOUBLE_EQ(M_PI * 6.5 * 6.5, c.getArea());
}

TEST(circle_test, set_ference_updates_others) {
  Circle c(1.0);
  double new_ference = 12.0;
  c.setFerence(new_ference);
  EXPECT_DOUBLE_EQ(new_ference, c.getFerence());
  EXPECT_NEAR(new_ference / (2.0 * M_PI), c.getRadius(), EPS);
  EXPECT_NEAR(M_PI * c.getRadius() * c.getRadius(), c.getArea(), EPS);
}

TEST(circle_test, set_area_updates_others) {
  Circle c(1.0);
  double new_area = 50.0;
  c.setArea(new_area);
  EXPECT_DOUBLE_EQ(new_area, c.getArea());
  EXPECT_NEAR(std::sqrt(new_area / M_PI), c.getRadius(), EPS);
  EXPECT_NEAR(2.0 * M_PI * c.getRadius(), c.getFerence(), EPS);
}

TEST(circle_test, zero_radius) {
  Circle c(0.0);
  EXPECT_DOUBLE_EQ(0.0, c.getRadius());
  EXPECT_DOUBLE_EQ(0.0, c.getFerence());
  EXPECT_DOUBLE_EQ(0.0, c.getArea());
}

TEST(circle_test, large_radius_values) {
  double huge_rad = 1e7;
  Circle c(huge_rad);
  EXPECT_DOUBLE_EQ(huge_rad, c.getRadius());
  EXPECT_DOUBLE_EQ(2.0 * M_PI * huge_rad, c.getFerence());
  EXPECT_NEAR(M_PI * huge_rad * huge_rad, c.getArea(), 1e1);
}

TEST(circle_test, small_radius_values) {
  double tiny_rad = 1e-8;
  Circle c(tiny_rad);
  EXPECT_DOUBLE_EQ(tiny_rad, c.getRadius());
  EXPECT_DOUBLE_EQ(2.0 * M_PI * tiny_rad, c.getFerence());
  EXPECT_DOUBLE_EQ(M_PI * tiny_rad * tiny_rad, c.getArea());
}

TEST(circle_test, set_negative_area_throws) {
  Circle c(1.0);
  EXPECT_THROW(c.setArea(-25.0), std::invalid_argument);
}

TEST(circle_test, set_negative_ference_throws) {
  Circle c(1.0);
  EXPECT_THROW(c.setFerence(-5.0), std::invalid_argument);
}

TEST(circle_test, ratio_area_ference) {
  Circle c(7.0);
  double ratio = c.getArea() / (c.getFerence() * c.getFerence());
  EXPECT_NEAR(ratio, 1.0 / (4.0 * M_PI), 1e-7);
}

TEST(rope_test, small_planet_gap) {
  const double planetRadiusKm = 100.0;
  const double planetRadiusM = planetRadiusKm * 1000.0;
  Circle planet(planetRadiusM);
  double oldFerence = planet.getFerence();
  planet.setFerence(oldFerence + 1.0);
  double newRadius = planet.getRadius();
  double gap = newRadius - planetRadiusM;
  EXPECT_GT(gap, 0.0);
}

TEST(rope_test, earth_gap_basic) {
  const double earthRadiusKm = 6378.1;
  const double earthRadiusM = earthRadiusKm * 1000.0;
  Circle earth(earthRadiusM);
  double oldFerence = earth.getFerence();
  earth.setFerence(oldFerence + 1.0);
  double gap = earth.getRadius() - earthRadiusM;
  EXPECT_NEAR(gap, 0.159, 0.002);
}

TEST(rope_test, large_added_length) {
  const double earthRadiusKm = 6378.1;
  const double earthRadiusM = earthRadiusKm * 1000.0;
  Circle earth(earthRadiusM);
  double oldFerence = earth.getFerence();
  earth.setFerence(oldFerence + 500.0);
  double gap = earth.getRadius() - earthRadiusM;
  EXPECT_GT(gap, 50.0);
}

TEST(rope_test, zero_added_length) {
  const double earthRadiusKm = 6378.1;
  const double earthRadiusM = earthRadiusKm * 1000.0;
  Circle earth(earthRadiusM);
  double oldFerence = earth.getFerence();
  earth.setFerence(oldFerence + 0.0);
  double gap = earth.getRadius() - earthRadiusM;
  EXPECT_NEAR(gap, 0.0, EPS);
}

TEST(rope_test, negative_planet_throws) {
  EXPECT_THROW({ Circle badPlanet(-6378.1 * 1000.0); }, std::invalid_argument);
}

TEST(pool_test, basic_scenario) {
  double poolRadius = 3.0;
  double walkway = 1.0;
  Circle cPool(poolRadius);
  Circle cOuter(poolRadius + walkway);
  double poolArea = cPool.getArea();
  double outerArea = cOuter.getArea();
  double walkwayArea = outerArea - poolArea;
  double concreteCost = walkwayArea * CONCRETE_PRICE;
  double fenceLength = cOuter.getFerence();
  double fenceCost = fenceLength * FENCE_PRICE;
  EXPECT_GT(poolArea, 0.0);
  EXPECT_GT(outerArea, 0.0);
  EXPECT_GT(walkwayArea, 0.0);
  EXPECT_GT(concreteCost, 0.0);
  EXPECT_GT(fenceCost, 0.0);
}

TEST(pool_test, zero_walkway) {
  double poolRadius = 3.0;
  double walkway = 0.0;
  Circle cPool(poolRadius);
  Circle cOuter(poolRadius + walkway);
  double poolArea = cPool.getArea();
  double outerArea = cOuter.getArea();
  double walkwayArea = outerArea - poolArea;
  EXPECT_NEAR(walkwayArea, 0.0, EPS);
  double fenceLength = cOuter.getFerence();
  double fenceCost = fenceLength * FENCE_PRICE;
  double poolFence = cPool.getFerence() * FENCE_PRICE;
  EXPECT_NEAR(fenceCost, poolFence, EPS);
  double concreteCost = walkwayArea * CONCRETE_PRICE;
  EXPECT_NEAR(concreteCost, 0.0, EPS);
}

TEST(pool_test, negative_walkway_throws) {
  double poolRadius = 3.0;
  double walkway = -1.0;
  EXPECT_NO_THROW({ Circle cOuter(poolRadius + walkway); });
  EXPECT_THROW({ Circle cOuter2(poolRadius + (-4.0)); }, std::invalid_argument);
}

TEST(pool_test, negative_pool_radius) {
  EXPECT_THROW({ Circle cPool(-2.0); }, std::invalid_argument);
}

TEST(pool_test, very_large_pool) {
  double poolRadius = 1000.0;
  double walkway = 10.0;
  Circle cPool(poolRadius);
  Circle cOuter(poolRadius + walkway);
  double walkwayArea = cOuter.getArea() - cPool.getArea();
  EXPECT_GT(walkwayArea, 0.0);
  double fenceLen = cOuter.getFerence();
  EXPECT_GT(fenceLen, 0.0);
  double concreteCost = walkwayArea * CONCRETE_PRICE;
  double fenceCost = fenceLen * FENCE_PRICE;
  double totalCost = concreteCost + fenceCost;
  EXPECT_GT(totalCost, 0.0);
}

TEST(pool_test, zero_prices) {
  double poolRadius = 3.0;
  double walkway = 1.0;
  Circle cPool(poolRadius);
  Circle cOuter(poolRadius + walkway);
  double walkwayArea = cOuter.getArea() - cPool.getArea();
  double fenceLen = cOuter.getFerence();
  double concretePrice = 0.0;
  double fencePrice = 0.0;
  double concreteCost = walkwayArea * concretePrice;
  double fenceCost = fenceLen * fencePrice;
  double totalCost = concreteCost + fenceCost;
  EXPECT_DOUBLE_EQ(0.0, concreteCost);
  EXPECT_DOUBLE_EQ(0.0, fenceCost);
  EXPECT_DOUBLE_EQ(0.0, totalCost);
}
