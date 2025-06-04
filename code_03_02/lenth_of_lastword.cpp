#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

using namespace std;

int main()
{
    string str;

    getline(cin, str);

    size_t pos = str.rfind(' ');
    cout << str.size() - (pos + 1);
}