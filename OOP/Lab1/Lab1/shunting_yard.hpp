//
//  shunting_yard.hpp
//  Lab1
//
//  Created by Kushka Misha on 9/13/17.
//  Copyright © 2017 Kushka Misha. All rights reserved.
//

#ifndef shunting_yard_hpp
#define shunting_yard_hpp

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <cmath>
#include <stdio.h>
using namespace std;

list<string> ShuntingAlgorithm(string, double);
double ReversePolish(list<string>);
string ReplaceAll(string, const string&, const string&);
double f(string, double);

#endif /* shunting_yard_hpp */
