#include <iostream>

using namespace std;

class Solution
{
public:
    bool isPalindrome(string s)
    {
        string retstr;

        for (int i = 0; i < s.size(); i++)
        {
            if (isupper(s[i]) || islower(s[i]) || (s[i] >= '0' && s[i] <= '9'))
            {
                retstr += tolower(s[i]);
            }
        }

        int left = 0;
        int right = retstr.size() - 1;

        while (left < right)
        {
            if (retstr[left] != retstr[right])
            {
                return false;
            }

            left++;
            right--;
        }

        return true;
    }
};