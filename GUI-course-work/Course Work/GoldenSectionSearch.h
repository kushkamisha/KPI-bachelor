/**
* Used to describe the prototype of the GoldenSectionSearch() function.
*/

#pragma once
#include "stdafx.h"
#include "functions.h"

namespace GoldenSection
{
	/**
	* Golden selection search method, which finds min and max
	* value of the function on a range.
	*
	* @param s Given function to calculate.
	* @param a Lower bound of the function.
	* @param b Higher bound of the function.
	* @param acc Accuracy of the calculations.
	* @returns String, which contents result and information
	* about calculations.
	*/
	std::string GoldenSectionSearch(std::string, double, double, double);
}