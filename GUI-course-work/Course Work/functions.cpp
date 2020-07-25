#include "functions.h" // Describes all prototypes of functions in the file functions.cpp file.
#include "stdafx.h" // Connect libraries that are used in the project.

/**
* Checks is given function has correct format.
*
* @param s Given function.
* @returns Has correct format or not.
*/
bool CheckFunction(std::string s)
{
	int n = s.length(),					// length of the string
		counter = 0;					// number of symbols, which can be in the expression with double numbers
	std::vector<char> can_content;		// symbols, which can be in the expression with double numbers
	can_content = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'x', ' ', '+', '-', '*', '/', '^', '(', ')' };
	for (int i = 0; i < n; ++i)
		if (std::find(can_content.begin(), can_content.end(), s[i]) != can_content.end())
			counter++;
	
	return !!(counter == n);
}

/**
* Checks is string a number.
*
* @param s Given string.
* @returns Is number or not.
*/
bool IsNumber(std::string s)
{
	int n = s.length(),		// length of the string
		counter = 0;		// counter
	if (n == 0)
		return false;
	for (int i = 0; i < n; ++i)
		if (isdigit(s[i]) || s[i] == ',' || s[i] == '-')
			counter++;

	return !!(counter == n);
}

/**
* Saves given string to the file "extremums.txt".
*
* @param s Given string.
*/
void SaveToFile(std::string s)
{
	std::ofstream f("extremums.txt");	// output file
	f << s;
	f.close();
}

/**
* Rounds given number up to a given number of digits.
*
* @param a Given number.
* @param n Number of digits to round.
* @returns Rounded number.
*/
double RoundTo(double a, int  n)
{
	int mult = std::pow(10, n);		// stores 10 in some power
	a *= mult;
	a = std::round(a);
	return a / mult;
}

/**
* Converts double number to string
*
* @param a Given number.
* @param n Number of digits after comma.
* @returns Created of the number string.
*/
std::string ToString(double a, int n)
{
	std::string s = std::to_string(a);	// string from double number
	int p = s.find(".");				// position of dot symbol in the string
	s = s.substr(0, p + n + 1);

	return s;
}

/**
* Replaces in string one substring by another.
*
* @param str Given string.
* @param from Given substring that you want to replace.
* @param to Given substring to which you want to replace.
* @returns Changed string.
*/
std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
	size_t start_pos = 0;	// start position in the string
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
	return str;
}

/**
* Finds max value in an array.
*
* @param arr Giver array.
* @param n Length of the array.
* @returns Max array value.
*/
double FindMaxValue(std::vector<double> arr, unsigned long n)
{
	unsigned long max_index = 0;	// index of max element in the array
	double max = arr[0];			// initial "max" value
	for (unsigned long i = 0; i < n; ++i)
		if (arr[i] > max)
		{
			max = arr[i];
			max_index = i;
		}
	return max_index;
}

/**
* Finds min value in an array.
*
* @param arr Giver array.
* @param n Length of the array.
* @returns Max array value.
*/
double FindMinValue(std::vector<double> arr, unsigned long n)
{
	unsigned long min_index = 0;	// index of min element in the array
	double min = arr[0];			// initial "min" value
	for (unsigned long i = 0; i < n; ++i)
		if (arr[i] < min)
		{
			min = arr[i];
			min_index = i;
		}
	return min_index;
}

/**
* Replacing all powers by multiplying and 
* remove all spaces in the input string.
*
* @param s Given string.
*/
void PowerReplace(std::string &s)
{
	int pos,	// position of "x^" substring
		n,		// end of substring with "x^"
		i;		// counter
	s = ReplaceAll(s, " ", "");
	while (s.find("x^") != -1)
	{
		pos = s.find("x^");
		n = s[pos + 2] - '0';
		s.erase(pos, 3);
		std::string power = "";

		for (i = 0; i < n; ++i)
			power += "x*";
		power.erase(power.end() - 1);
		s.insert(pos, power);
	}
}

/**
* Shunting algorithm function helps to calculate input as string function
* in point x.
*
* @param s Given function to calculate.
* @param x The point in which you want to calculate function.
* @returns List with numbers and operations, which received from function.
*/
std::list<std::string> ShuntingAlgorithm(std::string s, double x)
{
	bool numbers_before;					// whether there are numbers before
	int i;									// counter
	std::list<char> stack;					// stack for string's elements
	std::list<std::string> queue;			// result queue
	std::string prev = "o";					// previous char in the string
	std::string number;						// number in the string
	std::map<char, int> precedence = {		// dictionary with prioriry of operations
		{ '-', 1 },{ '+', 1 },
		{ '*', 2 },{ '/', 2 },
		{ '^', 3 }
	};

	// replace 'x' by x-value
	s = ReplaceAll(s, "x", std::to_string(x));

	// replace all '--' by '+'
	s = ReplaceAll(s, "--", "+");
	if (s[0] == '+')
		s.erase(s.begin(), s.begin() + 1);

	// work with '-'
	numbers_before = false;
	i = 0;
	while (i < s.length())
	{
		if (isdigit(s[i]))
			numbers_before = true;
		i++;
		if (s[i] == '-' && numbers_before && isdigit(s[i - 1]))
		{
			s.insert(i, "+");
			i++;
		}
	}

	for (int i = 0; i < s.length(); ++i)
	{
		if (isdigit(s[i]) || s[i] == '.' || s[i] == '-')
		{
			// It's a number
			if (prev.length() == 1)
			{
				if (isdigit(prev[0]) || prev[0] == '.' || prev[0] == '-')
				{
					number = prev + std::string(1, s[i]);
					queue.pop_back();
					queue.push_back(number);
					prev = number;
				}
				else
				{
					queue.push_back(std::string(1, s[i]));
					prev = s[i];
				}
			}
			else
			{
				number = prev + std::string(1, s[i]);
				queue.pop_back();
				queue.push_back(number);
				prev = number;
			}
		}
		else
		{
			if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^')
			{
				// It's an operator
				while (!stack.empty())
				{
					if (precedence[stack.back()] > precedence[s[i]])
					{
						queue.push_back(std::string(1, stack.back()));
						stack.pop_back();
					}
					else
						break;
				}
				stack.push_back(s[i]);
			}
			else
			{
				if (s[i] == '(')
					stack.push_back('(');
				if (s[i] == ')')
				{
					while (!stack.empty())
					{
						if (stack.back() != '(')
						{
							queue.push_back(std::string(1, stack.back()));
							stack.pop_back();
						}
						else
						{
							stack.pop_back();
							break;
						}
					}
				}
			}
			prev = s[i];
		}
	}

	// While there's operators on the stack, pop them to the queue
	while (!stack.empty())
	{
		queue.push_back(std::string(1, stack.back()));
		stack.pop_back();
	}

	return queue;
}

/**
* Reverse polish algorithm, which calculates list with numbers
* and operations and gives calculated value.
*
* @param queue List with numbers and operations, which received from function.
* @returns Value of the calculated list.
*/
double ReversePolish(std::list<std::string> queue)
{
	double a,					// first number for math operation
		   b,					// second number for math operation
		   result = 0;			// result of math operation
	std::list<double>fstack;	// stack with numbers and math operators
	std::string str;			// string, which contains current symbol from queue

	for (std::list<std::string>::iterator p = queue.begin(); p != queue.end(); ++p)
	{
		str = *p;
		if (str[0] == '-')
		{
			fstack.push_back(stod(str));
			continue;
		}
		if (isdigit(str[0]))
			fstack.push_back(stod(str));
		else
		{
			a = fstack.back();
			fstack.pop_back();
			b = fstack.back();
			fstack.pop_back();
			switch (str[0])
			{
			case '+':
				result = b + a;
				break;
			case '-':
				result = b - a;
				break;
			case '*':
				result = b * a;
				break;
			case '/':
				result = (double)b / a;
				break;
			case '^':
				result = (double)pow((double)b, a);
				break;
			}
			fstack.push_back(result);
		}
	}

	return fstack.back();
}

/**
* Calculates input as string function in point x.
*
* @param s Given function to calculate.
* @param x The point in which you want to calculate function.
* @returns Value of the calculated function in point.
*/
double f(std::string s, double x)
{
	std::list<std::string>queue = ShuntingAlgorithm(s, x);	// queue with numbers and math operators
	return ReversePolish(queue);
}