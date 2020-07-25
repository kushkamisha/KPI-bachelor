/**
* Used to describe the prototype of the DichotomyMethod() function.
*/

#pragma once
#include "stdafx.h"
#include "functions.h"

namespace Dichotomy
{
	/**
	* Dichotomy method, which finds min and max
	* value of the function on a range.
	*
	* @param s Given function to calculate.
	* @param a Lower bound of the function.
	* @param b Higher bound of the function.
	* @param acc Accuracy of the calculations.
	* @returns String, which contents result and information
	* about calculations.
	*/
	std::string DichotomyMethod(std::string, double, double, double);
}