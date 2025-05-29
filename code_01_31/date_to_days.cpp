#include <iostream>

using namespace std;

int Get_Days(int year, int month, int day)
{
    int days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    int total_day = 0;

    for (int i = 1; i < month; ++i)
    {
        total_day += days[i];

        if (i == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
        {
            ++total_day;
        }
    }

    total_day += day;
    return total_day;
}

int main() 
{
    int year = 0, month = 0, day = 0;
    while (cin >> year >> month >> day) 
    {
        cout << Get_Days(year, month, day) << endl;
    }

    return 0;
}