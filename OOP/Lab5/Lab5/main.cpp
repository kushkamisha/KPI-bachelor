#include "prototypes.hpp"
#include "functions.hpp"

int main() {
    // Author information
    Author *auth = new Author();
    auth->GetInfo();

    // Input
    string xs, ys, zs;
    values valA, valB;
    string cont = "y";
    
    while(cont == "y") {
        cout << "=== First vector ===" << endl << endl;
        valA = input();
    
        cout << "=== Second vector ===" << endl << endl;
        valB =input();
    
        Vector a(valA.x, valA.y, valA.z),
               b(valB.x, valB.y, valB.z),
               c;
    
        // Demo
        cout << endl;
        a.show("A");
        b.show("B");
        cout << endl;
        show_demo(a, b, c);
        
        cout << endl << endl << "Continue? (y / n)\n> ";
        cin >> cont;
    }
    
    return 0;
}
