#include "class_prototypes.hpp"

int main() {
    // Display some usefull info.
    Author *auth = new Author(2);
    auth->GetInfo();
    
    Function *log_;
    Function *exp_;
    
    double x;
    cout << "Enter x\n> ";
    cin >> x;
    
    exp_ = new Exponent(x);
    log_ = new Logarithm(x);

    exp_->calc_value();
    log_->calc_value();
    
    char cont = '\0';
    
    // Try again cycle.
    while(true) {
        cout << "\nContinue? (y/n)\n> ";
        cin >> cont;
        if (cont == 'n')
            break;
        
        // Try again.
        cout << "Enter x\n> ";
        cin >> x;
        
        exp_ = new Exponent(x);
        log_ = new Logarithm(x);

        exp_->calc_value();
        log_->calc_value();
    }
    
    delete exp_;
    delete log_;
    
    return 0;
}
