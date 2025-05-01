#ifndef TRIANGLE30_H
#define TRIANGLE30_H

#include <iostream>
#include <vector>
#include <cmath>
#include <windows.h>

using namespace std;

struct Point {
    double x, y;
};

struct Triangle {
    Point A, B, C;
};

double distance(const Point& p1, const Point& p2);
double crossProduct(const Point& A, const Point& B, const Point& P);
double heronArea(const Triangle& t);
bool isPointInTriangle_VectorMethod(const Triangle& t, const Point& P);
bool isDegenerate(const Triangle& t);
bool isPointOnEdge(const Triangle& t, const Point& P);
void coordinate();
#endif