#include "Date.h"

#include <iostream>
using namespace std;


const int
Date::MAX_DAY = 31,
Date::MIN_DAY = 1,
Date::MAX_MONTH = 12,
Date::MIN_MONTH = 1,
Date::MIN_YEAR = 1,
Date::MAX_YEAR = 2024;

Date::Date() : _day(1), _month(1), _year(2021) {
}


Date::Date(int day, int month, int year) : Date() {
	setDate(day, month, year);
}


Date::Date(const Date& other) {
	_year = other._year;
	_month = other._month;
	_day = other._day;
}


Date::~Date() {

}


bool Date::setDate(int day, int month, int year) {
	if (!(checkDay(day) && checkMonth(month) && checkYear(year)))
	{
		return false;
	}
	_year = year;
	_month = month;
	_day = day;
	return true;
}


bool Date::setDate(const Date& other) {
    return setDate(other._day, other._month, other._year);
}


bool Date::setDay(int day) {
	if (!checkDay(day)) {
		return false;
	}
	_day = day; 
	return true;
}


bool Date::setMonth(int month) {
	if (!checkMonth(month)) {
		return false;
	}
	_month = month;
	return true;
}


bool Date::setYear(int year) {
	if (!checkYear(year)) {
		return false;
	}
	_year = year; 
	return true;
}


ostream& operator<<(ostream& os, const Date& date) {
	os << date._day << "/" << date._month << "/" << date._year;
	return os;
}

    
istream& operator>>(istream& in, Date& date) {
	in >> date._day >> date._month >> date._year;
	return in;
}

    
const Date& Date::operator=(const Date& other) {
	_year = other._year;
	_month = other._month;
	_day = other._day;
	return *this;
}

    
bool Date::checkDay(int day) {
    return day >= MIN_DAY && day <= MAX_DAY;
}

    
bool Date::checkMonth(int month) {
    return month >= MIN_MONTH && month <= MAX_MONTH;
}

    
bool Date::checkYear(int year) {
    return year >= MIN_YEAR && year <= MAX_YEAR;
}
