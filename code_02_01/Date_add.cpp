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

    void Print()
    {
        printf("%4d-%02d-%02d\n", _year, _month, _day);
    }

private:
    int _year;
    int _month;
    int _day;
};

int main() 
{
    int count = 0;
    cin >> count;

    int year = 0, month = 0, day = 0;
    while (count--) {
        int days = 0;
        cin >> year >> month >> day >> days;

        Date d(year, month, day);
        Date tmp = d + days;

        tmp.Print();
    }

    return 0;
}
