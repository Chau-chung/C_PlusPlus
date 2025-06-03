#include<iostream>

using namespace std;

class Solution 
{
public:
    int myAtoi(string str) 
    {
        int sign = 1;
        int index = 0;
        long ret = 0;

        while (str[index] == ' ')
            ++index;

        if (str[index] == '-')
        {
            sign = -1;
            ++index;
        }
        else if (str[index] == '+')
        {
            ++index;
        }

        while (index < str.size() && isdigit(str[index]))
        {
            ret = ret * 10 + (str[index] - '0');
            if (ret < INT_MIN || ret > INT_MAX)
            {
                if (sign == 1)
                {
                    return INT_MAX;
                }
                else
                {
                    return INT_MIN;
                }
            }
            ++index;
        }

        return sign * ret;
    }
};