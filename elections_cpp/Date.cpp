#include "Date.h"

#include <iostream>
using namespace std;

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
	if (year < 1 || year > 2022 || 
		month < 1 || month > 12 || 
		day < 1 || day > 31) 
	{
		return false;
	}
	_year = year;
	_month = month;
	_day = day;
	return true;
}

bool Date::setDate(const Date& other) {
	if (other._year < 1 || other._year > 2022 || 
		other._month < 1 || other._month > 12 || 
		other._day < 1 || other._day > 31) 
	{
		return false;
	}
	_year = other._year;
	_month = other._month;
	_day = other._day;
	return true;
}

bool Date::setDay(int day) {
	if (day < 1 || day > 31) {
		return false;
	}
	_day = day; 
	return true;
}
bool Date::setMonth(int month) {
	if (month < 1 || month > 1) {
		return false;
	}
	_month = month;
	return true;
}
bool Date::setYear(int year) {
	if (year < 1 || year > 2022) {
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