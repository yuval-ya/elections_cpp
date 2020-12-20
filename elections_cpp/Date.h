#pragma once
#include <iostream>

class Date
{
private:
	int	_day, _month, _year;

public:
	Date();
	Date(int day, int month, int year);
	Date(const Date&);
	~Date();

	bool setDate(const Date& other);
	bool setDate(int day, int month, int year);
	bool setDay(int day);
	bool setMonth(int month);
	bool setYear(int year);

	int getDay() const { return _day; }
	int getMonth() const { return _month; }
	int getYear() const { return _year; }

	friend std::ostream& operator<<(std::ostream&, const Date&);
	friend std::istream& operator>>(std::istream&, Date&);
	
	const Date& operator=(const Date&);
};

