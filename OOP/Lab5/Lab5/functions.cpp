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
    cout << "c = a * 5" << endl;
    c = a * 5;
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

// Check input values for vector
values input() {
    string xs, ys, zs;
    values val;
    
    while (true) {
        // Enter x
        while(true) {
            try {
                cout << "Enter x\n> ";
                cin >> xs;
                val.x = stof(xs);
                
                break;
            } catch(const out_of_range& oor) {
                cout << "Entered value out of range. Please entervalue in range from " << __FLT_MIN__ << " to " << __FLT_MAX__ << endl;
            } catch(...) {
                cout << "Error! Please enter number, not string." << endl;;
            }
        }
        // Enter y
        while(true) {
            try {
                cout << "Enter y\n> ";
                cin >> ys;
                val.y = stof(ys);
                
                break;
            } catch(const out_of_range& oor) {
                cout << "Entered value out of range. Please entervalue in range from " << __FLT_MIN__ << " to " << __FLT_MAX__ << endl;
            } catch(...) {
                cout << "Error! Please enter number, not string." << endl;;
            }
        }
        // Enter z
        while(true) {
            try {
                cout << "Enter z\n> ";
                cin >> zs;
                val.z = stof(zs);
                
                break;
            } catch(const out_of_range& oor) {
                cout << "Entered value out of range. Please entervalue in range from " << __FLT_MIN__ << " to " << __FLT_MAX__ << endl;
            } catch(...) {
                cout << "Error! Please enter number, not string." << endl;;
            }
        }
        // Is zero vector
        if (val.x == 0  && val.y == 0 && val.z == 0) {
            cout << "Length of vector can't be zero (0, 0, 0). Please try another values." << endl << endl;
        } else {
            break;
        }
    }
    
    return val;
}

