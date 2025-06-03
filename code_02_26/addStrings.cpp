#include <iostream>

using namespace std;

class Solution 
{
public:
    string addStrings(string num1, string num2) 
    {
        int end1 = num1.size() - 1, end2 = num2.size() - 1;
        int next = 0;

        string retStr;
        while (end1 >= 0 || end2 >= 0)
        {
            int val1 = end1 >= 0 ? num1[end1--] - '0' : 0;
            int val2 = end2 >= 0 ? num2[end2--] - '0' : 0;
            int ret = val1 + val2 + next;
            next = ret / 10;
            ret %= 10;

            retStr += (ret + '0');
        }

        if (next == 1)
            retStr += '1';

        reverse(retStr.begin(), retStr.end());
        return retStr;
    }
};
