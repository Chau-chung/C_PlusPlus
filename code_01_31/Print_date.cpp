#include <iostream>
#include <assert.h>

using namespace std;

class Date
{
public:
    Date(int year, int day)
    {
        _year = year;
        _day = day;
    }

    int GetMonthDay(int year, int month) const
    {
        assert(month > 0 && month < 13);

        static int days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

        int day = days[month];
        if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
        {
            ++day;
        }

        return day;
    }

    void convert()
    {
        while (_day > GetMonthDay(_year, _month))
        {
            _day -= GetMonthDay(_year, _month);
            ++_month;
        }
    }

    void Print()
    {
        printf("%4d-%02d-%02d\n", _year, _month, _day);
    }

private:
    int _year = 1;
    int _month = 1;
    int _day = 1;
};

int main() 
{
    int year = 0, day = 0;
    while (cin >> year >> day) 
    {
        Date d(year, day);
        d.convert();
        d.Print();
    }

    return 0;
}
