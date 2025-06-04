#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

using namespace std;

class Solution 
{
public:
    string multiply(string num1, string num2)
    {
        if (num1 == "0" || num2 == "0")
        {
            return "0";
        }

        int len1 = num1.size();
        int len2 = num2.size();
        int* res = new int[len1 + len2] { 0 };

        for (int i = len1 - 1; i >= 0; --i)
        {
            for (int j = len2 - 1; j >= 0; --j)
            {
                int mul = (num1[i] - '0') * (num2[j] - '0');
                int sum = mul + res[i + j + 1];
                res[i + j] += sum / 10;
                res[i + j + 1] = sum % 10;
            }
        }

        string retStr;
        for (int i = 0; i < len1 + len2; i++)
        {
            if (!(retStr.empty() && res[i] == 0))
            {
                retStr.push_back(res[i] + '0');
            }
        }

        delete[] res;

        return retStr;
    }
};