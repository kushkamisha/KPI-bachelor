//
//  class_prototype.cpp
//  Lab1
//
//  Created by Kushka Misha on 9/13/17.
//  Copyright © 2017 Kushka Misha. All rights reserved.
//

class AlgebraicExpression {
    string fx = "";
    double x = 0;
public:
    AlgebraicExpression();
    void GetFunction();
    void GetX();
    void ClearString();
    void SolveFunction();
    ~AlgebraicExpression();
};
