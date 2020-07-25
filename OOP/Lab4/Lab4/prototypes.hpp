//
//  prototypes.hpp
//  Lab4
//
//  Created by Kushka Misha on 10/28/17.
//  Copyright © 2017 Kushka Misha. All rights reserved.
//

#ifndef prototypes_hpp
#define prototypes_hpp

#include "stdafx.hpp"

class Vector {
    double x, y, z;
public:
    Vector(double a, double b, double c) : x(a), y(b), z(c) {}; // Constructor
    Vector() { x = y = z = 0; }                                 // Blank constructor
    //    ~Vector() { cout << "Destructor..." << endl; }              // Destructor
    
    double getX() { return x; }
    double getY() { return y; }
    double getZ() { return z; }
    void show(string s) {
        cout << s << " = (" << x <<", " << y << ", " << z << ")" << endl;
    }
    
    Vector operator+(Vector);   // Sum of 2 vectors
    Vector operator-(Vector);   // Substraction of a 2 vectors
    Vector operator*(Vector);   // Multiplication of a 2 vectors
    Vector operator*(double);   // Multiplication by a constant
    
    Vector& operator-();        // Unary minus operation
    bool operator==(Vector);    // Check vectors collinearity
};

// Class to display some useful info about author of the program.
class Author {
    int level, variant;
public:
    Author(int level=3, int variant=15) : level(level), variant(variant) {}
    void GetInfo();
};

#endif /* prototypes_hpp */
