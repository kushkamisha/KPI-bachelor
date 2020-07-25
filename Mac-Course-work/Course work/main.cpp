//
//  main.cpp
//  Course work
//
//  Created by Kushka Misha on 07.04.17.
//  Copyright © 2017 Kushka Misha. All rights reserved.
//

#include "stdafx.hpp"
#include "functions.hpp"
using namespace std;

int main() {
    ProgramInfo();
    
    cout << "Select one of the following methods to find extremum:\
            \n1 - Golden-section search method\
            \n2 - ?Bracketing a Minimum?\
            \n3 - Dichotomy method" << endl << endl;
    cout << "Enter function: ";
    string func;
    cin >> func;
    
    // replace x^3 by x*x*x and so on
    while (func.find("x^") != -1)
    {
        int pos = func.find("x^");
        int n = func[pos + 2] - '0';
        func.erase(pos, 3);
        string power = "";
        
        for (int i = 0; i < n; ++i)
            power += "x*";
        power.erase(power.end() - 1);
        func.insert(pos, power);
    }
    
//    DichotomyMethod(func);
    BracketingMinimum(func);
//    GoldenSectionSearch(func);
    /*short choice = NULL;
    cin >> choice;
    switch (choice)
    {
        case 1:
            GoldenSectionSearch();
            break;
        case 2:
            BracketingMinimum();
            break;
        case 3:
            DichotomyMethod();
            break;
        default:
            cout << "Sorry, but " << choice << " isn't a valid choice." << endl;
    }
    */
    return 0;
}
