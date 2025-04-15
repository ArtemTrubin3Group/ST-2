// Copyright 2025 UNN-CS Team
#include <gtest/gtest.h>
#include <cmath>
#include "circle.h"
#include "tasks.h"

const double EPSILON = 1e-6;
const double EARTH_RADIUS = 6378137.0;

TEST(CircleTest, RadiusOperations) {
    Circle c(5.5);
    EXPECT_NEAR(c.getRadius(), 5.5, EPSILON);
    EXPECT_NEAR(c.getFerence(), 34.557519, EPSILON);
    EXPECT_NEAR(c.getArea(), 95.033178, EPSILON);
}

TEST(CircleTest, FerenceUpdate) {
    Circle c(0);
    c.setFerence(62.831853);
    EXPECT_NEAR(c.getRadius(), 10.0, EPSILON);
    EXPECT_NEAR(c.getArea(), 314.159265, EPSILON);
}

TEST(CircleTest, AreaUpdate) {
    Circle c(0);
    c.setArea(452.389342);
    EXPECT_NEAR(c.getRadius(), 12.0, EPSILON);
    EXPECT_NEAR(c.getFerence(), 75.398224, EPSILON);
}

TEST(CircleTest, InvalidValues) {
    Circle c(-5.0);
    EXPECT_NEAR(c.getRadius(), 0.0, EPSILON);
    c.setFerence(-10.0);
    EXPECT_NEAR(c.getFerence(), 0.0, EPSILON);
    c.setArea(-25.0);
    EXPECT_NEAR(c.getArea(), 0.0, EPSILON);
}

TEST(TaskTest, EarthRopeProblem) {
    double gap = ropeGap(EARTH_RADIUS);
    EXPECT_NEAR(gap, 1.0/(2*M_PI), EPSILON);
    gap = ropeGap(1000.0);
    EXPECT_NEAR(gap, 1.0/(2*M_PI), EPSILON);
}

TEST(TaskTest, PoolCostCalculation) {
    double cost = poolCost(3.0, 1.0, 100.0, 50.0);
    double expected = (M_PI*(16.0-9.0)*100.0) + (8.0*M_PI*50.0);
    EXPECT_NEAR(cost, expected, EPSILON);
    cost = poolCost(0.0, 0.0, 0.0, 0.0);
    EXPECT_NEAR(cost, 0.0, EPSILON);
    cost = poolCost(0.1, 0.05, 1.0, 1.0);
    expected = (M_PI*(0.0225-0.01)*1.0) + (2*M_PI*0.15*1.0);
    EXPECT_NEAR(cost, expected, EPSILON);
}

TEST(TaskTest, ExtremeCases) {
    double cost = poolCost(1000.0, 100.0, 1e6, 1e6);
    double expected = (M_PI*(1210000.0-1000000.0)*1e6) + (2*M_PI*1100.0*1e6);
    EXPECT_NEAR(cost, expected, 1.0);
    cost = poolCost(0.001, 0.0005, 0.01, 0.01);
    expected = (M_PI*(2.25e-6-1e-6)*0.01) + (2*M_PI*0.0015*0.01);
    EXPECT_NEAR(cost, expected, EPSILON);
}

TEST(TaskTest, SpecialCases) {
    double cost = poolCost(2.0, 1.0, 10.0, 0.0);
    double expected = (M_PI*(9.0-4.0)*10.0);
    EXPECT_NEAR(cost, expected, EPSILON);
    cost = poolCost(2.0, 1.0, 0.0, 10.0);
    expected = (2*M_PI*3.0*10.0);
    EXPECT_NEAR(cost, expected, EPSILON);
}

TEST(TaskTest, NegativeInputs) {
    double gap = ropeGap(-1000.0);
    EXPECT_NEAR(gap, 1.0/(2*M_PI), EPSILON);
    double cost = poolCost(-3.0, -1.0, -100.0, -50.0);
    EXPECT_NEAR(cost, 0.0, EPSILON);
}

TEST(CircleTest, ZeroRadiusOperations) {
    Circle c(0.0);
    EXPECT_NEAR(c.getRadius(), 0.0, EPSILON);
    EXPECT_NEAR(c.getFerence(), 0.0, EPSILON);
    EXPECT_NEAR(c.getArea(), 0.0, EPSILON);
}

TEST(CircleTest, LargeRadiusOperations) {
    Circle c(1e6);
    EXPECT_NEAR(c.getRadius(), 1e6, EPSILON);
    EXPECT_NEAR(c.getFerence(), 2*M_PI*1e6, EPSILON);
    EXPECT_NEAR(c.getArea(), M_PI*1e12, EPSILON);
}

TEST(CircleTest, PrecisionOperations) {
    Circle c(0.000001);
    EXPECT_NEAR(c.getRadius(), 0.000001, EPSILON);
    EXPECT_NEAR(c.getFerence(), 2*M_PI*0.000001, EPSILON);
    EXPECT_NEAR(c.getArea(), M_PI*1e-12, EPSILON);
}

TEST(CircleTest, MultipleUpdates) {
    Circle c(1.0);
    c.setFerence(6.283185);
    c.setArea(12.566371);
    EXPECT_NEAR(c.getRadius(), 2.0, EPSILON);
    EXPECT_NEAR(c.getFerence(), 12.566371, EPSILON);
    EXPECT_NEAR(c.getArea(), 12.566371, EPSILON);
}

TEST(CircleTest, ChainedUpdates) {
    Circle c(0.0);
    c.setArea(78.539816);
    c.setFerence(31.415927);
    EXPECT_NEAR(c.getRadius(), 5.0, EPSILON);
    EXPECT_NEAR(c.getFerence(), 31.415927, EPSILON);
    EXPECT_NEAR(c.getArea(), 78.539816, EPSILON*10);
}

TEST(CircleTest, NegativeRadiusInitialization) {
    Circle c(-5.0);
    EXPECT_NEAR(c.getRadius(), 0.0, EPSILON);
    EXPECT_NEAR(c.getFerence(), 0.0, EPSILON);
    EXPECT_NEAR(c.getArea(), 0.0, EPSILON);
}

TEST(CircleTest, PartialNegativeUpdates) {
    Circle c(10.0);
    c.setFerence(-10.0);
    EXPECT_NEAR(c.getFerence(), 0.0, EPSILON);
    EXPECT_NEAR(c.getRadius(), 0.0, EPSILON);
    c.setRadius(10.0);
    c.setArea(-25.0);
    EXPECT_NEAR(c.getArea(), 0.0, EPSILON);
    EXPECT_NEAR(c.getRadius(), 0.0, EPSILON);
}

TEST(TaskTest, ZeroRopeGap) {
    double gap = ropeGap(0.0);
    EXPECT_NEAR(gap, 1.0/(2*M_PI), EPSILON);
}

TEST(TaskTest, TinyRopeGap) {
    double gap = ropeGap(1e-6);
    EXPECT_NEAR(gap, 1.0/(2*M_PI), EPSILON);
}

TEST(TaskTest, HugeRopeGap) {
    double gap = ropeGap(1e12);
    EXPECT_NEAR(gap, 1.0/(2*M_PI), EPSILON*1000);
}

TEST(TaskTest, PoolZeroWidth) {
    double cost = poolCost(5.0, 0.0, 100.0, 50.0);
    double expected = (2*M_PI*5.0*50.0);
    EXPECT_NEAR(cost, expected, EPSILON);
}

TEST(TaskTest, PoolNegativeWidth) {
    double cost = poolCost(5.0, -1.0, 100.0, 50.0);
    EXPECT_NEAR(cost, 0.0, EPSILON);
}
