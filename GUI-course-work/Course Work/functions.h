/**
* Used to describe all prototypes of functions in the file functions.cpp.
*/

#pragma once
#include "stdafx.h"

/**
* Replacing all powers by multiplying and
* remove all spaces in the input string.
*
* @param s Given string.
*/
void PowerReplace(std::string &);

/**
* Saves given string to the file "extremums.txt".
*
* @param s Given string.
*/
void SaveToFile(std::string);

/**
* Replaces in string one substring by another.
*
* @param str Given string.
* @param from Given substring that you want to replace.
* @param to Given substring to which you want to replace.
* @returns Changed string.
*/
std::string ReplaceAll(std::string, const std::string&, const std::string&);

/**
* Converts double number to string
*
* @param a Given number.
* @param n Number of digits after comma.
* @returns Created of the number string.
*/
std::string ToString(double, int);

/**
* Finds max value in an array.
*
* @param arr Giver array.
* @param n Length of the array.
* @returns Max array value.
*/
double FindMaxValue(std::vector<double>, unsigned long);

/**
* Finds min value in an array.
*
* @param arr Giver array.
* @param n Length of the array.
* @returns Max array value.
*/
double FindMinValue(std::vector<double>, unsigned long);

/**
* Reverse polish algorithm, which calculates list with numbers
* and operations and gives calculated value.
*
* @param queue List with numbers and operations, which received from function.
* @returns Value of the calculated list.
*/
double ReversePolish(std::list<std::string>);

/**
* Calculates input as string function in point x.
*
* @param s Given function to calculate.
* @param x The point in which you want to calculate function.
* @returns Value of the calculated function in point.
*/
double f(std::string, double);

/**
* Rounds given number up to a given number of digits.
*
* @param a Given number.
* @param n Number of digits to round.
* @returns Rounded number.
*/
double RoundTo(double, int);

/**
* Checks is given function has correct format.
*
* @param s Given function.
* @returns Has correct format or not.
*/
bool CheckFunction(std::string);

/**
* Checks is string a number.
*
* @param s Given string.
* @returns Is number or not.
*/
bool IsNumber(std::string);

/**
* Shunting algorithm function helps to calculate input as string function
* in point x.
*
* @param s Given function to calculate.
* @param x The point in which you want to calculate function.
* @returns List with numbers and operations, which received from function.
*/
std::list<std::string> ShuntingAlgorithm(std::string, double);