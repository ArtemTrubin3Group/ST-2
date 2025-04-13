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
