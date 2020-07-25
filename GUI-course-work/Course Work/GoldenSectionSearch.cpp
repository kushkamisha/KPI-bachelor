#include "GoldenSectionSearch.h" // Describes the prototype of the GoldenSectionSearch() function.

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

std::string GoldenSection::GoldenSectionSearch(std::string s, double a, double b, double acc)
{
	const double fi = (1 + pow(5, 0.5)) / 2;		// golden section proportion	
	unsigned int iterations = 0,					// number of iterations
				 operations = 12,					// number of operations
				 start_time = clock();				// start time of working method
	double x1,										// first x-value for golden section search
		   x2,										// second x-value for golden section search
		   y1,										// first f(x)-value for golden section search
		   y2,										// second f(x)-value for golden section search
		   x_min,									// min x value
		   x_max,									// max x value
		   a_original,								// initial start of the range
		   b_original,								// initial end of the range
		   work_time = 0;							// method's work time

	a_original = a;
	b_original = b;
	// find mininum of the function
	do
	{
		x1 = b - (b - a) / fi;
		x2 = a + (b - a) / fi;
		y1 = f(s, x1);
		y2 = f(s, x2);

		if (y1 >= y2)
		{
			a = x1;
			x1 = x2;
			x2 = a + (b - a) / fi;
		}
		else
		{
			b = x2;
			x2 = x1;
			x1 = b - (b - a) / fi;
		}
		iterations++;
	} while (abs(b - a) > acc);
	x_min = (a + b) / 2;

	// find maximum of the function
	a = a_original;
	b = b_original;
	do
	{
		x1 = b - (b - a) / fi;
		x2 = a + (b - a) / fi;
		y1 = f(s, x1);
		y2 = f(s, x2);

		if (y1 <= y2)
		{
			a = x1;
			x1 = x2;
			x2 = a + (b - a) / fi;
		}
		else
		{
			b = x2;
			x2 = x1;
			x1 = b - (b - a) / fi;
		}
		iterations++;
	} while (abs(b - a) > acc);
	x_max = (a + b) / 2;

	work_time = double(clock() - start_time) / CLK_TCK;

	// output result
	int n = 0;						// number of digits after comma
	std::string result = "";		// result of method's work

	while (acc < 1)
	{
		acc *= 10;
		n++;
	}
	if (x_min == x_max)
		result = "Function is independent of x. So f(min) = f(max) = " + ToString(RoundTo(f(s, x_max), n), n);
	else
	{
		result = "y(min) = " + ToString(RoundTo(f(s, x_min), n), n) + " at x(min) = " + ToString(RoundTo(x_min, n), n);
		result += "\ny(max) = " + ToString(RoundTo(f(s, x_max), n), n) + " at x(min) = " + ToString(RoundTo(x_max, n), n);
	}

	result += "\nNumber of iterations: " + std::to_string(iterations);
	result += "\nNumber of operations: " + std::to_string(operations * iterations * 2);
	result += "\nRunning time of the method: " + std::to_string(work_time) + " s";

	return result;
}