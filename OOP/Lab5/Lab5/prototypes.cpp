//
//  prototypes.cpp
//  Lab4
//
//  Created by Kushka Misha on 10/28/17.
//  Copyright © 2017 Kushka Misha. All rights reserved.
//

#include "prototypes.hpp"
#include "errors.hpp"

// Sum
Vector Vector::operator+(Vector vec) {
    Vector temp;
    
    temp.x = x + vec.x;
    temp.y = y + vec.y;
    temp.z = z + vec.z;
    
    return temp;
}

// Substraction
Vector Vector::operator-(Vector vec) {
    Vector temp;
    
    temp.x = x - vec.x;
    temp.y = y - vec.y;
    temp.z = z - vec.z;
    
    return temp;
}

// Multiplication of a 2 vectors
Vector Vector::operator*(Vector vec) {
    Vector temp;
    
    temp.x = y * vec.z - z * vec.y;
    temp.y = z * vec.x - x * vec.z;
    temp.z = x * vec.y - y * vec.x;
    
    return temp;
}

// Multiplication by a constant
Vector Vector::operator*(float value) {
    Vector temp;
    temp.x = x * value;
    temp.y = y * value;
    temp.z = z * value;
    
    return temp;
}

// Unary minus
Vector& Vector::operator-() {
    Vector temp;
    
    temp.x = -x;
    temp.y = -y;
    temp.z = -z;
    
    return temp;
}

// Collinearity
bool Vector::operator==(Vector vec) {
    if (x == 0 && vec.x == 0) {
        if (y / vec.y == z / vec.z)
            return true;
        return false;
    } else if (y == 0 && vec.y == 0) {
        if (x / vec.x == z / vec.z)
            return true;
        return false;
    } else if (z == 0 && vec.z == 0) {
        if (x / vec.x == y / vec.y)
            return true;
        return false;
    } else {
        float alpha = 0;
        alpha = x / vec.x;
        if (y / vec.y == alpha && z / vec.z == alpha)
            return true;
    }
    return false;
}

// Show vector
void Vector::show(string s) {
    try {
        if (isinf(x) || isinf(y) || isinf(z)) {
            throw IsInfinity();
        }
        if (isnan(x) || isnan(y) || isnan(z)) {
            throw IsNaN();
        }
    cout << s << " = (" << x <<", " << y << ", " << z << ")" << endl;
    } catch (IsInfinity &e) {
        e.showError();
        cout << s << " = (" << x <<", " << y << ", " << z << ")" << endl;
    } catch (IsNaN &e) {
        e.showError();
    }
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
