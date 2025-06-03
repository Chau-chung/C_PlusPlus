#include <iostream>

using namespace std;

// class Solution 
// {
// public:
//     int firstUniqChar(string s) 
//     {
//         for(int i = 0; i < s.size(); ++i)
//         {
//             if(s.find(s[i]) == s.rfind(s[i]))
//                 return i;
//         }

//         return -1;
//     }
// };

class Solution
{
public:
    int firstUniqChar(string s) 
    {
        int len = s.size();
        int count[26] = { 0 };

        for(auto ch : s)
        {
            ++count[ch - 'a'];
        }

        for(int i = 0; i < len; ++i)
        {
            if(count[s[i] - 'a'] == 1)
                return i;
        }

        return -1;
    }
};