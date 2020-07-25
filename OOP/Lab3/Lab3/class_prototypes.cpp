//
//  class_prototypes.cpp
//  Lab3
//
//  Created by Kushka Misha on 9/30/17.
//  Copyright © 2017 Kushka Misha. All rights reserved.
//

#include "class_prototypes.hpp"

void Exponent::calc_value(int n) {
    long double result = 1;
    for (int i = 1; i < n; ++i) {
        result += pow(x, i) / factorial(i);
    }
    
    cout << "e^(" << x << ") = " << result << endl;
}

void Logarithm::calc_value(int n) {
    if (x <= 0 || x > 2) {
        cout << "Sorry, but x must be in range (0, 2]." << endl;
    } else {
        long double result = 0;
        for (int i = 1; i < n; ++i) {
            if (i % 2 == 0) {
                result -= pow(x-1, i) / i;
            } else {
                result +=  pow(x-1, i) / i;
            }
        }
        
        cout << "log(" << x << ") = " << result << endl;
    }
}

Function::~Function() {
    cout << "Function class destructor." << endl;
}

Exponent::~Exponent() {
    cout << "Exponent destructor." << endl;
}

Logarithm::~Logarithm() {
    cout << "Logarithm destructor." << endl;
}

unsigned long int factorial(int x) {
    return x == 0 ? 1 : x * factorial(x-1);
}

void Author::GetInfo() {
    // Displays author info.
    cout << "\
    -----------------------\n\
    | Kushka Misha, IP-61 |\n\
    | Level: " << level << "            |\n\
    | Variant: " << variant << "         |\n\
    -----------------------\n\n";
}
