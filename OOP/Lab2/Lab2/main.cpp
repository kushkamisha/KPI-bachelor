#include "prototypes.hpp"

int main() {
    srand(time(NULL));
    
    // Display some usefull info.
    Author *auth = new Author;
    auth->GetInfo();
    
    Point *p = new Point(5, 10, 3);
    p->GetAll();
    delete p;
    
    Point2 *p2 = new Point2(-2, 2, 0);
    p2->GetAll();
    delete p2;
    
    Point3 *p3 = new Point3(0, 11, 9);
    p3->GetAll();
    delete p3;
    
    Pyramid *pir;
    char cont_program;
    char cont_this;
    int *arr;
    
    while (true) {
//        arr = input_coordinates();
//        pir = new Pyramid(arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6], arr[7], arr[8], arr[9], arr[10], arr[11]);
        pir = new Pyramid(1, 2, 1, 5, 6, -7, 8, 0, 0, 3, 4, 2);
        
        while (true) {
            int choice = get_choice();
            if (choice == 1)
                pir->GetPeaks();
            else if (choice == 2)
                pir->GetEdges();
            else if (choice == 3)
                pir->PlaneEquation();
            else if (choice == 4) {
                pir->GetPeaks();
                pir->GetEdges();
                pir->PlaneEquation();
            }
            cout << "Continue with this points? (y/n)\n> ";
            cin >> cont_this;
            if (cont_this == 'n')
                break;
        }
        
        cout << "Try enter another points? (y/n)\n> ";
        cin >> cont_program;
        if (cont_program == 'n')
            break;
    }
    delete pir;
    
    return 0;
}
