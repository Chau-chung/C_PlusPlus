#include <iostream>
#include <assert.h>

using namespace std;

class Date
{
public:
    Date(int year, int month, int day)
        :_year(year)
        , _month(month)
        , _day(day)
    {}

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

    bool operator<(const Date& d) const
    {
        if (_year < d._year)
        {
            return true;
        }
        else if (_year == d._year)
        {
            if (_month < d._month)
            {
                return true;
            }
            else if (_month == d._month)
            {
                return _day < d._day;
            }
        }

        return false;
    }

    Date& operator+=(int day)
    {
        _day += day;
        while (_day > GetMonthDay(_year, _month))
        {
            _day -= GetMonthDay(_year, _month);
            ++_month;
            if (_month == 13)
            {
                ++_year;
                _month = 1;
            }
        }

        return *this;
    }

    Date operator+(int day) const
    {
        Date tmp(*this);
        tmp += day;

        return tmp;
    }

    Date& operator++()
    {
        *this += 1;
        return *this;
    }

    int operator-(const Date& d) const
    {
        Date max = *this;
        Date min = d;

        if (*this < d)
        {
            max = d;
            min = *this;
        }

        int days = 0;
        while (min < max)
        {
            ++min;
            ++days;
        }

        return days + 1;
    }

private:
    int _year;
    int _month;
    int _day;
};

int main() 
{
    int year = 0, month = 0, day = 0;
    while (scanf("%4d%2d%2d", &year, &month, &day) != EOF) 
    {
        Date d1(year, month, day);

        scanf("%4d%2d%2d", &year, &month, &day);
        Date d2(year, month, day);

        cout << d1 - d2 << endl;
    }

    return 0;
}
