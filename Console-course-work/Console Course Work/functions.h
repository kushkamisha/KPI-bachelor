#pragma once

void PowerReplace(string &);
void GoldenSectionSearch(string, double, double, double);
void BracketingMinimum(string, double, double, double);
void DichotomyMethod(string, double, double, double);

double FindMaxValue(vector<double>, unsigned long);
double FindMinValue(vector<double>, unsigned long);
double ReversePolish(list<string>);
double f(string, double);

list<string> ShuntingAlgorithm(string, double);
string ReplaceAll(string, const string&, const string&);