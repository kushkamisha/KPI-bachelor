//
//  prototypes.hpp
//  Lab2
//
//  Created by Kushka Misha on 9/16/17.
//  Copyright © 2017 Kushka Misha. All rights reserved.
//

#ifndef prototypes_hpp
#define prototypes_hpp

#include "stdafx.hpp"

// Emulation of the point.
class Point {
public:
    int x, y, z;
    Point(int x, int y, int z) : x(x), y(y), z(z) {}
    void GetX();
    void GetY();
    void GetZ();
    void GetAll();
    ~Point();
};

class Point2: public Point {
public:
    Point2(int x, int y, int z) : Point(x, y, z) {}
};

class Point3: public Point {
public:
    Point3(int x, int y, int z) : Point(x, y, z) {}
};

// Emulation of the pyramid.
class Pyramid: public Point2, public Point3  {
    int x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;
public:
    Pyramid(int x10, int y10, int z10, int x20, int y20, int z20, int x3, int y3, int z3, int x4, int y4, int z4) :
    Point2(x10, y10, z10), Point3(x20, y20, z20), x3(x3), y3(y3), z3(z3), x4(x4), y4(y4), z4(z4) {
        x1 = Point2::x;
        y1 = Point2::y;
        z1 = Point2::z;
        
        x2 = Point3::x;
        y2 = Point3::y;
        z2 = Point3::z;
    }
    void GetPeaks();
    void GetEdges();
    void PlaneEquation();
};

// Class to display some useful info about author of the program.
class Author {
    int level, variant;
public:
    Author(int level=3, int variant=15) : level(level), variant(variant) {}
    void GetInfo();
};

// Get coordinates of the vertexes via user input.
int* input_coordinates();

// Simple menu for methods of the Pyramid class.
int get_choice();

#endif /* prototypes_hpp */
