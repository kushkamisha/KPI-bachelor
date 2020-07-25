//
//  shunting_yard.cpp
//  Lab1
//
//  Created by Kushka Misha on 9/13/17.
//  Copyright © 2017 Kushka Misha. All rights reserved.
//

#include "shunting_yard.hpp"


double f(string s, double x)
{
    // Insert '*' if nesessary ("2x" -> "2*x")
    list<char> good = {'+', '-', '*' , '/', '('};
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == 'x' && i != 0) {
            if (!(find(good.begin(), good.end(), s[i-1]) != good.end())) {
                s.insert(i, "*");
            }
        }
    }
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
    
    // replace x^3 by x*x*x and so on
    while (s.find("x^") != -1)
    {
        //        cout << "here" << endl;
        int pos = s.find("x^");
        int n = s[pos + 2] - '0';
        s.erase(pos, 3);
        string power = "";
        
        for (int i = 0; i < n; ++i)
            power += "x*";
        power.erase(power.end() - 1);
        s.insert(pos, power);
    }
    
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
    // Replace all occurences in the string.
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}
