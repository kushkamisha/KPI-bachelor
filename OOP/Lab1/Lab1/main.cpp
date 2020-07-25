#include "shunting_yard.hpp"
#include "class_prototype.hpp"

void AuthorInfo();

int main() {
    AuthorInfo();
    
    AlgebraicExpression *ptr;
    
    char quit = 'y';
    while (quit != 'n') {
        ptr = new AlgebraicExpression;
        ptr->SolveFunction();
        delete ptr;
        
        // Break the cycle.
        cout << "\nTry again? (y/n)\n> ";
        cin >> quit;
    }
    
    return 0;
}

AlgebraicExpression::AlgebraicExpression() {
    // Get function and x-value for it.
    cout << "Enter algebraic expression with one variable\n> ";
    getline(cin, fx);
    cout << fx << endl;
//    cin >> fx;
    this->ClearString();
}
AlgebraicExpression::~AlgebraicExpression() {
    // Class destructor.
    cout << "\nMust delete something..." << endl;
    fx = "";
    x = 0;
}

void AlgebraicExpression::GetFunction() {
    cout << "F(x) = " << fx << endl;
}
void AlgebraicExpression::GetX() {
    cout << "x = " << x << endl;
}
void AlgebraicExpression::SolveFunction() {
    cout << "Enter value of x\n> ";
    cin >> x;
    
    double answer = f(fx, x);
    cout << "Answer = " << answer << endl;
}
void AlgebraicExpression::ClearString() {
    // Delete all spaces in the string.
    fx.erase(remove(fx.begin(), fx.end(), ' '), fx.end());
}

void AuthorInfo() {
    cout << "\
    -----------------------\n\
    | Kushka Misha, IP-61 |\n\
    | Level: 3            |\n\
    | Variant: 15         |\n\
    -----------------------\n\n";
}
