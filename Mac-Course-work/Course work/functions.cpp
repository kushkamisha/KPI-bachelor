//
//  functions.cpp
//  Course work
//
//  Created by Kushka Misha on 08.04.17.
//  Copyright © 2017 Kushka Misha. All rights reserved.
//
//        [+][+]         [+][+]
//     [+][+][+][+]   [+][+][+][+]
//  [+][+][+][+][+][+][+][+][+][+][+]
//  [+][+][+][+][+][+][+][+][+][+][+]
//  [+][+]     I love code     [+][+]
//     [+][+][+][+][+][+][+][+][+]
//        [+][+][+][+][+][+][+]
//           [+][+][+][+][+]
//              [+][+][+]
//                 [+]

#include "functions.hpp"
#include "stdafx.hpp"

const double fi = (1 + pow(5, 0.5)) / 2;

void ProgramInfo ()
{
    cout << "\t-----------------------------------------------------\
    \n\t| This program helps to find extremum of a function |\
    \n\t| uses the following methods:                       |\
    \n\t| \t- Golden-section search method                  |\
    \n\t| \t- ?Bracketing a Minimum?                        |\
    \n\t| \t- Dichotomy method                              |\
    \n\t-----------------------------------------------------"<< endl << endl;
}

void GoldenSectionSearch (string s)
{
//    cout << "Golden-section search method" << endl;
//    cout << "Function: (x - 1) ^ 2" << endl;
    cout << "Enter boundaries of segment a and b (a < b)" << endl;
    double a, b;
    cin >> a >> b;
    cout << "Enter accuracy" << endl;
    double acc;
    cin >> acc;
    
    double x1, x2, y1, y2, a_original, b_original;
    a_original = a;
    b_original = b;
    // find mininum of the function
    do
    {
        x1 = b - (b - a) / fi;
        x2 = a + (b - a) / fi;
        y1 = f (s, x1);
        y2 = f (s, x2);
    
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
        y1 = f (s, x1);
        y2 = f (s, x2);
        
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
    
    if (x_min == x_max)
        cout << "Function is independent of x. So f(min) = f(max) = " << f(s, x_max) << endl;
    else
    {
        cout << "y(min) = " << f(s, x_min) << " at " << "x(min) = " << x_min << endl;
        cout << "y(max) = " << f(s, x_max) << " at " << "x(max) = " << x_max << endl;
    }
}

void BracketingMinimum (string s)
{
    cout << "Bracketiong a Minimum method" << endl;
    cout << "Function: (x - 1) ^ 2" << endl;
    cout << "Enter boundaries of segment a and b (a < b)" << endl;
    double a, b;
    cin >> a >> b;
    cout << "Enter accuracy" << endl;
    double acc;
    cin >> acc;
    
    int n = (b - a) / acc;
    cout << "n = " << n << endl;
    
    double x_mas [n], x_values [n];
    for (unsigned long i = 0; i < n; ++i)
    {
        x_mas[i] = a + (i + 1) * (b - a) / (n + 1);
        x_values[i] = f(s, x_mas[i]);
    }
    unsigned long x_min_index = FindMinValue (x_values, n);
    unsigned long x_max_index = FindMaxValue (x_values, n);
    double x_min = x_mas [x_min_index];
    double x_max = x_mas [x_max_index];
    
    if (x_min == x_max)
        cout << "Function is independent of x. So f(min) = f(max) = " << f(s, x_max) << endl;
    else
    {
        cout << "y(min) = " << f(s, x_min) << " at " << "x(min) = " << x_min << endl;
        cout << "y(max) = " << f(s, x_max) << " at " << "x(max) = " << x_max << endl;
    }
    
}

void DichotomyMethod (string s)
{
//    cout << "Dichotomy method" << endl;
//    cout << "Function: (x - 1) ^ 2" << endl;
    cout << "Enter boundaries of segment a and b (a < b)" << endl;
    double a, b;
    cin >> a >> b;
    cout << "Enter accuracy" << endl;
    double acc;
    cin >> acc;
    
    double y, z, f_y, f_z, a_original, b_original,
           epsilon = pow (10, -8);
    a_original = a;
    b_original = b;
    // find minimum of the function
    do
    {
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
        y = (a + b - epsilon) / 2;
        f_y = f(s, y);
        z = (a + b + epsilon) / 2;
        f_z = f(s, z);
        cout << "f(y) = " << f(s, y) << endl;
        cout << "f(z) = " << f(s, z) << endl << endl;
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
        f_y = f (s, y);
        z = (a + b + epsilon) / 2;
        f_z = f (s, z);
        if (f_y >= f_z)
            b = z;
        else
            a = y;
    } while (abs(b - a) > acc);
    double x_max = (a + b) / 2;
    
    if (x_min == x_max)
        cout << "Function is independent of x. So f(min) = f(max) = " << f(s, x_max) << endl;
    else
    {
        cout << "y(min) = " << f(s, x_min) << " at " << "x(min) = " << x_min << endl;
        cout << "y(max) = " << f(s, x_max) << " at " << "x(max) = " << x_max << endl;
    }
}

//double f (double x)
//{
//    return pow(x - 1, 2);
////    return 1;
////    return 1 / x;
////    return pow(x, 3) + pow(x, 2);
//}

double FindMaxValue (double mas [], unsigned long n)
{
    double max = mas [0];
    unsigned long max_index = 0;
    for (unsigned long i = 0; i < n; ++i)
        if (mas [i] > max)
        {
            max = mas [i];
            max_index = i;
        }
    return max_index;
}

double FindMinValue (double mas [], unsigned long n)
{
    double min = mas [0];
    unsigned long min_index = 0;
    for (unsigned long i = 0; i < n; ++i)
        if (mas [i] < min)
        {
            min = mas [i];
            min_index = i;
        }
    return min_index;
}

double f(string s, double x)
{
    list<string>queue = ShuntingAlgorithm(s, x);
    return ReversePolish(queue);
}

list<string> ShuntingAlgorithm(string s, double x)
{
    /**
     * The shunting algorithm
     */
    list<char> stack;
    list<string> queue;
    string prev = "o";
    string number;
    
    map<char, int> precedence = {
        {'-', 1}, {'+', 1},
        {'*', 2}, {'/', 2},
        {'^', 3}
    };
    
    // replace 'x' by x-value
    s = ReplaceAll(s, "x", to_string(x));
    
    // replace all '--' by '+'
    s = ReplaceAll(s, "--", "+");
    if (s[0] == '+')
        s.erase(s.begin(), s.begin() + 1);
    
    // work with '-'
    bool numbers_before = false;
    int i = 0;
    while(i < s.length())
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
                    number = prev + string(1, s[i]);
                    queue.pop_back();
                    queue.push_back(number);
                    prev = number;
                }
                else
                {
                    queue.push_back(string(1, s[i]));
                    prev = s[i];
                }
            }
            else
            {
                number = prev + string(1, s[i]);
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
                        queue.push_back(string(1, stack.back()));
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
                            queue.push_back(string(1, stack.back()));
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
        queue.push_back(string(1, stack.back()));
        stack.pop_back();
    }
    
    return queue;
}

double ReversePolish(list<string> queue)
{
    /**
     * Reverse polish
     */
    double a, b, result = 0;
    list<double>fstack;
    string str;
    
    for (list<string>::iterator p = queue.begin(); p != queue.end(); ++p)
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
                    result = (double) b / a;
                    break;
                case '^':
                    result = (double) pow((double) b, a);
                    break;
            }
            fstack.push_back(result);
        }
    }
    
    return fstack.back();
}

string ReplaceAll(string str, const string& from, const string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

