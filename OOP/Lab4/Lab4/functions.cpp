//
//  functions.cpp
//  Lab4
//
//  Created by Kushka Misha on 10/28/17.
//  Copyright © 2017 Kushka Misha. All rights reserved.
//

#include "functions.hpp"

// Show all class operator functions
void show_demo(Vector a, Vector b, Vector c) {
    // c = a + b
    cout << "c = a + b" << endl;
    c = a + b;
    c.show("C");
    cout << endl;
    
    // c = a - b
    cout << "c = a - b" << endl;
    c = a - b;
    c.show("C");
    cout << endl;
    
    // c = a * b
    cout << "c = a * b" << endl;
    c = a * b;
    c.show("C");
    cout << endl;
    
    // c = a * const
    cout << "c = a * 3" << endl;
    c = a * 3;
    c.show("C");
    cout << endl;
    
    // c = -a
    cout << "c = -a" << endl;
    c = -a;
    c.show("C");
    cout << endl;
    
    // isCollinear = a == b
    bool isCollinear = false;
    cout << "isCollinear = a == b" << endl;
    isCollinear = a == b;
    cout << "isCollinear == " << isCollinear << endl << endl;
    
    // isCollinear = a == a*2
    cout << "isCollinear = a == a*2" << endl;
    isCollinear = a == a*2;
    cout << "isCollinear == " << isCollinear << endl << endl;
}

