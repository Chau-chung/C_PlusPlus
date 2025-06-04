#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

using namespace std;

class Solution 
{
public:
	string reverseStr(string s, int k) 
	{
		int len = s.size();
		string::iterator it = s.begin();

		for (int i = 0; i < len; i += 2 * k)
		{
			if (i + k < len)
			{
				reverse(it + i, it + i + k);
			}
			else
			{
				reverse(it + i, it + len);
			}
		}
		return s;
	}
};