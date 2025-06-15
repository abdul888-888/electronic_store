#include <iostream>
#include "date.h"
using namespace std;

bool Date::is_valid()
{
	return (day > 0 && month > 0 && month < 13 && year>0);
}
Date::Date()
{
	day = 0;
	month = 0;
	year = 0;

}
Date::Date(int day, int month, int year)
{
	this->day = day;
	this->month = month;
	this->year = year;
	if (!is_valid())
	{
		throw invalid_argument("invalid date");
	}
}
Date::Date(const Date& dob)
{
	this->day = dob.day;
	this->month = dob.month;
	this->year = dob.year;
}
void Date::print()
{
	cout << day << "/" << month << "/" << year;
}
Date Date::operator = (const Date& d)
{
	if (&d != this) {

		day = d.day;
		month = d.month;
		year = d.year;
	}
	return (*this);
}

ostream& operator << (ostream& os, const Date& d)
{
	os << d.day << d.month << d.year;
	return os;
}

istream& operator >> (istream& os, Date& d)
{
	os >> d.day >> d.month >> d.year;
	return os;
}
void Date::file(fstream& r)
{
	r >> *this;
}