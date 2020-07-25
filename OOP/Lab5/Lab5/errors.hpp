//
//  errors.hpp
//  Lab5
//
//  Created by Kushka Misha on 12/4/17.
//  Copyright © 2017 Kushka Misha. All rights reserved.
//

#ifndef errors_hpp
#define errors_hpp

class IsInfinity {
public:
    void showError() {
        cout << "Used type is too small to display so big value as following, so it'll be displayed as 'inf'." << endl;
    }
};

class IsNaN {
public:
    void showError() {
        cout << "Too big value" << endl;
    }
};

#endif /* errors_hpp */
