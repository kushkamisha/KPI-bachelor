// Console Course Work.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "functions.h"
#include <stdio.h>
#include <iostream>

using namespace std;

int main() {
	cout << "Enter function: ";
	string func;
	cin >> func;

	// replace x^3 by x*x*x and so on
	PowerReplace(func);
	cout << func << endl;

	// Input data
	double a, b, acc;
	cout << "Enter boundaries of segment a and b (a < b)" << endl;
	cin >> a >> b;
	cout << "Enter accuracy" << endl;
	cin >> acc;

	// DichotomyMethod(func, a, b, acc);
	// BracketingMinimum(func, a, b, acc);
	GoldenSectionSearch(func, a, b, acc);
	
	system("pause");
	return 0;
}