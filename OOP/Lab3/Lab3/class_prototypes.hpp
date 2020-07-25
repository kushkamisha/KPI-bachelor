//
//  class_prototypes.hpp
//  Lab3
//
//  Created by Kushka Misha on 9/30/17.
//  Copyright © 2017 Kushka Misha. All rights reserved.
//

#ifndef class_prototypes_hpp
#define class_prototypes_hpp

#include "stdafx.hpp"

// Abstract parent class.
class Function {
public:
    double x;
    virtual void calc_value(int n=25)=0;
    virtual ~Function();
};

// Exponent class (parent: Function).
class Exponent : public Function {
public:
    Exponent(double x_) {
        x = x_;
    };
    void calc_value(int n=25);
    ~Exponent();
};

// Logarithm class (parent: Function).
class Logarithm : public Function{
public:
    Logarithm(double x_) {
        x = x_;
    }
    void calc_value(int n=25);
    ~Logarithm();
};

// Class to display some useful info about author of the program.
class Author {
    int level, variant;
public:
    Author(int level=3, int variant=15) : level(level), variant(variant) {}
    void GetInfo();
};

// Calculate factorial.
unsigned long int factorial(int);

#endif /* class_prototypes_hpp */
