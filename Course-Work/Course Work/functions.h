#pragma once
#include "stdafx.h"

void PowerReplace(std::string &);
void SaveToFile(std::string);

std::string GoldenSectionSearch(std::string, double, double, double);
std::string BracketingMinimum(std::string, double, double, double);
std::string DichotomyMethod(std::string, double, double, double);
std::string ReplaceAll(std::string, const std::string&, const std::string&);
std::string ToString(double, int);

double FindMaxValue(std::vector<double>, unsigned long);
double FindMinValue(std::vector<double>, unsigned long);
double ReversePolish(std::list<std::string>);
double f(std::string, double);
double RoundTo(double, int);

bool CheckFunction(std::string);
bool IsNumber(std::string);
std::list<std::string> ShuntingAlgorithm(std::string, double);