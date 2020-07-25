#include "prototypes.hpp"
#include "functions.hpp"

int main() {
    Author *auth = new Author();
    auth->GetInfo();
    
    Vector a(5, 3, -1), b(3, 3, 3), c;
    
    a.show("A");
    b.show("B");
    cout << endl;
    
    show_demo(a, b, c);
        
    // Vectors are given on the plane
    cout << endl << "=====Vectors are given on the plane=====" << endl;
    Vector a_plane(5, 3, 0), b_plane(3, 3, 0), c_plane;
    
    a_plane.show("A");
    b_plane.show("B");
    cout << endl;
    
    show_demo(a_plane, b_plane, c_plane);
    
    
    return 0;
}
