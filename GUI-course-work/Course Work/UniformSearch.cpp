#include "UniformSearch.h" // Describes the prototype of the UniformSearch() function.

/**
* Uniform search method, which finds min and max
* value of the function on a range.
*
* @param s Given function to calculate.
* @param a Lower bound of the function.
* @param b Higher bound of the function.
* @param acc Accuracy of the calculations.
* @returns String, which contents result and information
* about calculations.
*/
std::string Uniform::UniformSearch(std::string s, double a, double b, double acc)
{
	unsigned int start_time = clock();		// start time of working method
	unsigned long n = (b - a) / acc,		// number of iterations
				  operations = 6,			// number of operations
				  x_min_index,				// index of min x value
				  x_max_index;				// index of max x value
	double work_time = 0,					// method's work time
		   x_min,							// min x value
		   x_max;							// max x value
	std::vector <double> x_arr,				// array of x-es on the range
						 y_arr;				// array of f(x)-es on the range

	for (unsigned long i = 0; i < n; ++i)
	{
		x_arr.push_back(a + (i + 1) * (b - a) / (n + 1));
		y_arr.push_back(f(s, x_arr[i]));
	}
	x_min_index = FindMinValue(y_arr, n);
	x_max_index = FindMaxValue(y_arr, n);
	x_min = x_arr[x_min_index];
	x_max = x_arr[x_max_index];

	work_time = double(clock() - start_time) / CLK_TCK;

	// output result
	int k = 0;						// number of digits after comma
	std::string result = "";		// result of method's work

	while (acc < 1)
	{
		acc *= 10;
		k++;
	}
	if (x_min == x_max)
		result = "Function is independent of x. So f(min) = f(max) = " + ToString(RoundTo(f(s, x_max), k), k);
	else
	{
		result = "y(min) = " + ToString(RoundTo(f(s, x_min), k), k) + " at x(min) = " + ToString(RoundTo(x_min, k), k);
		result += "\ny(max) = " + ToString(RoundTo(f(s, x_max), k), k) + " at x(min) = " + ToString(RoundTo(x_max, k), k);
	}

	result += "\nNumber of iterations: " + std::to_string(n);
	result += "\nNumber of operations: " + std::to_string(operations * n);
	result += "\nRunning time of the method: " + std::to_string(work_time) + " s";

	return result;
}