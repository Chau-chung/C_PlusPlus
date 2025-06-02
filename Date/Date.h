#pragma once

#include <iostream>
#include <assert.h>
using namespace std;

class Date
{
public:
	bool CheckInvalid() const;
	Date(int year = 1900, int month = 1, int day = 1);
	
	bool operator==(const Date& d) const;
	bool operator!=(const Date& d) const;
	bool operator<(const Date& d) const;
	bool operator<=(const Date& d) const;
	bool operator>(const Date& d) const;
	bool operator>=(const Date& d) const;
	
	// 日期+=天数
	Date& operator+=(int day);

	// 日期+天数
	Date operator+(int day) const;

	// 日期-天数
	Date operator-(int day) const;

	// 日期-=天数
	Date& operator-=(int day);

	// 前置++
	Date& operator++();

	// 后置++
	Date operator++(int);

	// 后置--
	Date operator--(int);

	// 前置--
	Date& operator--();
	
	// 日期-日期 返回天数
	int operator-(const Date& d) const;

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

	friend ostream& operator<<(ostream& out, const Date& d);
	friend istream& operator>>(istream& in, Date& d);

private:
	int _year;
	int _month;
	int _day;
};

ostream& operator<<(ostream& out, const Date& d);
istream& operator>>(istream& in, Date& d);