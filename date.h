#include <iostream>
#include <fstream>
#ifndef DATE_H
#define DATE_H

using namespace std;

class Date {
	int day;
	int month;
	int year;
	bool is_valid();

public:
	Date();
	Date(int day, int month, int year);
	Date(const Date& dob);
	int get_day()const { return day; }
	int get_month()const { return month; }
	int get_year()const { return year; }
	void print();
	Date operator = (const Date& d);
	friend ostream& operator << (ostream& os, const Date& s);
	friend  istream& operator >> (istream& os, Date& s);
	void file(fstream& r);
};

#endif //!