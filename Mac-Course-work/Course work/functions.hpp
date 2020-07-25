//
//  functions.hpp
//  Course work
//
//  Created by Kushka Misha on 08.04.17.
//  Copyright © 2017 Kushka Misha. All rights reserved.
//

#ifndef functions_hpp
#define functions_hpp
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <cmath>
#include <stdio.h>
using namespace std;
void ProgramInfo ();
void GoldenSectionSearch (string);
void BracketingMinimum (string);
void DichotomyMethod (string);
//double f (double);
double FindMaxValue (double [], unsigned long);
double FindMinValue (double [], unsigned long);

list<string> ShuntingAlgorithm(string, double);
double ReversePolish(list<string>);
string ReplaceAll(string, const string&, const string&);
double f(string, double);

#endif /* functions_hpp */
