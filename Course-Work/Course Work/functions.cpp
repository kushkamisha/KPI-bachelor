#include "functions.h"
#include "stdafx.h"

const double fi = (1 + pow(5, 0.5)) / 2;

bool CheckFunction(std::string s)
{
	std::vector<char> can_content = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'x', ' ', '+', '-', '*', '/', '^', '(', ')' };
	int n = s.length(), counter = 0;
	for (int i = 0; i < n; ++i)
		if (std::find(can_content.begin(), can_content.end(), s[i]) != can_content.end())
			counter++;
	
	return !!(counter == n);
}

bool IsNumber(std::string s)
{
	int n = s.length(), counter = 0;
	if (n == 0)
		return false;
	for (int i = 0; i < n; ++i)
		if (isdigit(s[i]) || s[i] == ',' || s[i] == '-')
			counter++;

	return !!(counter == n);
}

void SaveToFile(std::string s)
{
	std::ofstream f("extremums.txt");
	f << s;
	f.close();
}

double RoundTo(double a, int  n)
{
	int mult = std::pow(10, n);
	a *= mult;
	a = std::round(a);
	return a / mult;
}

std::string ToString(double a, int n)
{
	std::string s = std::to_string(a);
	int p = s.find(".");
	s = s.substr(0, p + n + 1);

	return s;
}

std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
	return str;
}

double FindMaxValue(std::vector<double> mas, unsigned long n)
{
	double max = mas[0];
	unsigned long max_index = 0;
	for (unsigned long i = 0; i < n; ++i)
		if (mas[i] > max)
		{
			max = mas[i];
			max_index = i;
		}
	return max_index;
}

double FindMinValue(std::vector<double> mas, unsigned long n)
{
	double min = mas[0];
	unsigned long min_index = 0;
	for (unsigned long i = 0; i < n; ++i)
		if (mas[i] < min)
		{
			min = mas[i];
			min_index = i;
		}
	return min_index;
}

void PowerReplace(std::string &s)
{
	s = ReplaceAll(s, " ", "");
	while (s.find("x^") != -1)
	{
		int pos = s.find("x^");
		int n = s[pos + 2] - '0';
		s.erase(pos, 3);
		std::string power = "";

		for (int i = 0; i < n; ++i)
			power += "x*";
		power.erase(power.end() - 1);
		s.insert(pos, power);
	}
}

std::list<std::string> ShuntingAlgorithm(std::string s, double x)
{
	/**
	* The shunting algorithm
	*/
	std::list<char> stack;
	std::list<std::string> queue;
	std::string prev = "o";
	std::string number;

	std::map<char, int> precedence = {
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
	bool numbers_before = false;
	int i = 0;
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

double ReversePolish(std::list<std::string> queue)
{
	/**
	* Reverse polish
	*/
	double a, b, result = 0;
	std::list<double>fstack;
	std::string str;

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

double f(std::string s, double x)
{
	std::list<std::string>queue = ShuntingAlgorithm(s, x);
	return ReversePolish(queue);
}

/////////////////////////////////
////// Find extremum functions //
/////////////////////////////////

std::string GoldenSectionSearch(std::string s, double a, double b, double acc)
{
	double x1, x2, y1, y2, a_original, b_original;
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
	} while (abs(b - a) > acc);
	double x_min;
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
	} while (abs(b - a) > acc);
	double x_max;
	x_max = (a + b) / 2;

	// output result
	int n = 0;
	while (acc < 1)
	{
		acc *= 10;
		n++;
	}
	std::string result = "";
	if (x_min == x_max)
		result = "Function is independent of x. So f(min) = f(max) = " + ToString(RoundTo(f(s, x_max), n), n);
	else
	{
		result = "y(min) = " + ToString(RoundTo(f(s, x_min), n), n) + " at x(min) = " + ToString(RoundTo(x_min, n), n);
		result += "\ny(max) = " + ToString(RoundTo(f(s, x_max), n), n) + " at x(min) = " + ToString(RoundTo(x_max, n), n);
	}

	return result;
}

std::string BracketingMinimum(std::string s, double a, double b, double acc)
{
	int n = (b - a) / acc;

	std::vector <double> x_mas, x_values;
	for (unsigned long i = 0; i < n; ++i)
	{
		x_mas.push_back(a + (i + 1) * (b - a) / (n + 1));
		x_values.push_back(f(s, x_mas[i]));
	}
	unsigned long x_min_index = FindMinValue(x_values, n);
	unsigned long x_max_index = FindMaxValue(x_values, n);
	double x_min = x_mas[x_min_index];
	double x_max = x_mas[x_max_index];

	// output result
	int k = 0;
	while (acc < 1)
	{
		acc *= 10;
		k++;
	}
	std::string result = "";
	if (x_min == x_max)
		result = "Function is independent of x. So f(min) = f(max) = " + ToString(RoundTo(f(s, x_max), k), k);
	else
	{
		result = "y(min) = " + ToString(RoundTo(f(s, x_min), k), k) + " at x(min) = " + ToString(RoundTo(x_min, k), k);
		result += "\ny(max) = " + ToString(RoundTo(f(s, x_max), k), k) + " at x(min) = " + ToString(RoundTo(x_max, k), k);
	}

	return result;
}

std::string DichotomyMethod(std::string s, double a, double b, double acc)
{
	double y, z, f_y, f_z, a_original, b_original, epsilon = pow(10, -4);
	a_original = a;
	b_original = b;
	// find minimum of the function
	do
	{
		y = (a + b - epsilon) / 2;
		f_y = f(s, y);
		z = (a + b + epsilon) / 2;
		f_z = f(s, z);
		if (f_y <= f_z)
			b = z;
		else
			a = y;
	} while (abs(b - a) > acc);
	double x_min = (a + b) / 2;

	a = a_original;
	b = b_original;
	// find maximum of the function
	do
	{
		y = (a + b - epsilon) / 2;
		f_y = f(s, y);
		z = (a + b + epsilon) / 2;
		f_z = f(s, z);
		if (f_y >= f_z)
			b = z;
		else
			a = y;
	} while (abs(b - a) > acc);
	double x_max = (a + b) / 2;

	// output result
	int n = 0;
	while (acc < 1)
	{
		acc *= 10;
		n++;
	}
	std::string result = "";
	if (x_min == x_max)
		result = "Function is independent of x. So f(min) = f(max) = " + ToString(RoundTo(f(s, x_max), n), n);
	else
	{
		result = "y(min) = " + ToString(RoundTo(f(s, x_min), n), n) + " at x(min) = " + ToString(RoundTo(x_min, n), n);
		result += "\ny(max) = " + ToString(RoundTo(f(s, x_max), n), n) + " at x(min) = " + ToString(RoundTo(x_max, n), n);
	}

	return result;
}