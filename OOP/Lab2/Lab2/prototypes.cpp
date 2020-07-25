//
//  prototypes.cpp
//  Lab2
//
//  Created by Kushka Misha on 9/16/17.
//  Copyright © 2017 Kushka Misha. All rights reserved.
//

#include "prototypes.hpp"


void Point::GetX() {
    cout << "x = " << x << endl;
}

void Point::GetY() {
    cout << "y = " << y << endl;
}

void Point::GetZ() {
    cout << "z = " << z << endl;
}

void Point::GetAll() {
    cout << "x = " << x << "; y = " << y << "; z = " << z << endl;
}

Point::~Point() {
    // Point class destructor.
    cout << "Delete something..." << endl;
}

void Pyramid::GetPeaks() {
    cout << endl << "--x--|" << "--y--|" << "--z--" << endl;
    cout << setw(4) << x1 << " |" << setw(4) << y1 << " |" << setw(4) << z1 << endl;
    cout << setw(4) << x2 << " |" << setw(4) << y2 << " |" << setw(4) << z2 << endl;
    cout << setw(4) << x3 << " |" << setw(4) << y3 << " |" << setw(4) << z3 << endl;
    cout << setw(4) << x4 << " |" << setw(4) << y4 << " |" << setw(4) << z4 << endl;
}

void Pyramid::GetEdges() {
    // Calculate edges length of the base of the pyramid.
    cout << "\nLength of the first edge = " << sqrt(pow(x3 - x2, 2) + pow(y3 - y2, 2) + pow(z3 - z2, 2)) << "." << endl;
    cout << "Length of the second edge = " << sqrt(pow(x4 - x3, 2) + pow(y4 - y3, 2) + pow(z4 - z3, 2)) << "." << endl;
    cout << "Length of the third edge = " << sqrt(pow(x4 - x2, 2) + pow(y4 - y2, 2) + pow(z4 - z2, 2)) << ".\n" << endl;
}

void Pyramid::PlaneEquation() {
    // Calculate plane equation for the base of the pyramid.
    
    double A = y2*(z3 - z4) + y3*(z4 - z2) + y4*(z2 - z3);
    double B = z2*(x3 - x4) + z3*(x4 - x2) + z4*(x2 - x3);
    double C = x2*(y3 - y4) + x3*(y4 - y2) + x4*(y2 - y3);
    double D = -A * x2 -B * y2 - C * z2;
    
    string a = " + ";
    string b = " + ";
    string c = " + ";
    
    if (B < 0) {
        a = " - ";
        B = -B;
    }
    if (C < 0) {
        b = " - ";
        C = -C;
    }
    if (D < 0) {
        c = " - ";
        D = -D;
    }
    cout << "The plane equation is: " << A << "x" << a << B << "y" << b << C << "z" << c << D << " = 0." << endl;
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

int* input_coordinates() {
    // Get coordinates of the vertexes via user input.
    int *arr = new int[12];
    cout << "Enter x, y, z of the first point, separated by spaces\n> ";
    cin >> arr[0] >> arr[1] >> arr[2];
    cout << "Enter x, y, z of the second point, separated by spaces\n> ";
    cin >> arr[3] >> arr[4] >> arr[5];
    cout << "Enter x, y, z of the third point, separated by spaces\n> ";
    cin >> arr[6] >> arr[7] >> arr[8];
    cout << "Enter x, y, z of the last point, separated by spaces\n> ";
    cin >> arr[9] >> arr[10] >> arr[11];
    
    return arr;
}

int get_choice() {
    // Simple menu for methods of the Pyramid class.
    int ch = 0;
    while (ch != 1 && ch != 2 && ch != 3 && ch != 4) {
        cout << "\nWhat do you want?\n";
        cout << "\t1 - Show all point coordinates\n";
        cout << "\t2 - Show length of edges in the base of the pyramid\n";
        cout << "\t3 - Show equation of the plane in the base of the pyramid\n";
        cout << "\t4 - Do all of the above\n";
        cin >> ch;
        if (ch != 1 && ch != 2 && ch != 3 && ch != 4)
            cout << "Invalid choice, try again." << endl;
    }
    
    return ch;
}
