#include "Date.h"

bool Date::CheckInvalid() const
{
	if (_year <= 0
		|| _month < 1 || _month > 12
		|| _day < 1 || _day > GetMonthDay(_year, _month))
	{
		return false;
	}
	else
	{
		return true;
	}
}

Date::Date(int year, int month, int day)
{
	_year = year;
	_month = month;
	_day = day;
}

bool Date::operator==(const Date& d) const
{
	return _year == d._year
		&& _month == d._month
		&& _day == d._day;
}

bool Date::operator!=(const Date& d) const
{
	/*return _year != d._year
		|| _month != d._month
		|| _day != d._day;*/

	return !(*this == d); 
}

bool Date::operator<(const Date& d) const
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

bool Date::operator<=(const Date& d) const
{
	return *this < d || *this == d;
}

bool Date::operator>(const Date& d) const
{
	/*if (_year > d._year)
	{
		return true;
	}
	else if (_year == d._year)
	{
		if (_month > d._month)
		{
			return true;
		}
		else if (_month == d._month)
		{
			return _day > d._day;
		}
	}

	return false;*/

	return !(*this <= d);
}

bool Date::operator>=(const Date& d) const
{
	return !(*this < d);
}

Date& Date::operator+=(int day)
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

Date Date::operator+(int day) const
{
	Date tmp(*this);
	tmp += day;

	return tmp;
}

Date Date::operator-(int day) const
{
	Date tmp(*this);
	tmp -= day;

	return tmp;
}

Date& Date::operator-=(int day)
{
	_day -= day;
	while (_day <= 0)
	{
		--_month;
		if (_month == 0)
		{
			--_year;
			_month = 12;
		}

		_day += GetMonthDay(_year, _month);
	}

	return *this;
}

Date& Date::operator++()
{
	*this += 1;
	return *this;
}

Date Date::operator++(int)
{
	Date tmp(*this);
	*this += 1;
	return tmp;
}

Date& Date::operator--()
{
	*this -= 1;
	return *this;
}

Date Date::operator--(int)
{
	Date tmp(*this);
	*this -= 1;
	return tmp;
}

int Date::operator-(const Date& d) const
{
	int flag = 1;
	Date max = *this;
	Date min = d;

	if (*this < d)
	{
		flag = -1;
		max = d;
		min = *this;
	}

	int days = 0;
	while (min < max)
	{
		++min;
		++days;
	}

	return days * flag;
}

ostream& operator<<(ostream& out, const Date& d)
{
	out << d._year << "/" << d._month << "/" << d._day << endl;

	return out;
}

istream& operator>>(istream& in, Date& d)
{
	while (1)
	{
		in >> d._year >> d._month >> d._day;

		if (!d.CheckInvalid())
		{
			cout << "Invalid Date!" << endl;
		}
		else
		{
			break;
		}
	}

	return in;
}