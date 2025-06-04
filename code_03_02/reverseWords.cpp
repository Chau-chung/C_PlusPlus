#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

using namespace std;

class Solution 
{
public:
    string reverseWords(string s)
    {
        size_t begin = 0;
        string::iterator it = s.begin();

        size_t pos = s.find(' ');
        while (pos != string::npos)
        {
            reverse(it + begin, it + pos);
            begin = pos + 1;

            pos = s.find(' ', begin);
        }

        reverse(it + begin, s.end());

        return s;
    }
};