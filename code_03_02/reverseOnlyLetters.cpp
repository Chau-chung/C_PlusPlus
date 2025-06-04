#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class Solution 
{
public:
    string reverseOnlyLetters(string s) 
    {
        if(s.empty()) return s;

        int left = 0, right = s.size() - 1;

        while(left < right)
        {
            while(left < right && isalpha(s[left]) == 0) ++left;
            while(left < right && isalpha(s[right]) == 0) --right;

            swap(s[left++], s[right--]);
        }

        return s;
    }
};