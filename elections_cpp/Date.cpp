#include <iostream>
#include "Date.h"
using namespace std;

const int Date::DAYS_PER_MONTH[13] = { -1,31,28,31,30, 31, 30, 31, 31, 30, 31, 30, 31 };

const int
Date::MIN_DAY = 1,
Date::MAX_MONTH = 12,
Date::MIN_MONTH = 1,
Date::MIN_YEAR = 1,
Date::MAX_YEAR = 2024;

Date::Date() : _day(1), _month(1), _year(2021) {
}

Date::Date(istream& in) {
	load(in);
}

Date::Date(int day, int month, int year) {
	setDate(day, month, year);
}

Date::Date(const Date& other) {
	_year = other._year;
	_month = other._month;
	_day = other._day;
}

Date::~Date() {
}

void Date::setDate(int day, int month, int year) {
	setYear(year);
	setMonth(month);
	setDay(day);
}

void Date::setDate(const Date& other) {
    setDate(other._day, other._month, other._year);
}

void Date::setDay(int day) {
	if (day < MIN_DAY || day > DAYS_PER_MONTH[_month])
		throw invalid_argument("Invalid day");

	_day = day; 
}

void Date::setMonth(int month) {
	if (month < MIN_MONTH || month > MAX_MONTH) 
		throw invalid_argument("Invalid month");

	_month = month;
}

void Date::setYear(int year) {
	if (year < MIN_YEAR || year > MAX_YEAR) 
		throw invalid_argument("Invalid year");

	_year = year; 
}

ostream& operator<<(ostream& os, const Date& date) {
	os << date._day << "/" << date._month << "/" << date._year;
	return os;
}
    
istream& operator>>(istream& in, Date& date) {
	int day, month, year;
	in >> day >> month >> year;
	date.setDate(day, month, year);
	return in;
}

const Date& Date::operator=(const Date& other) {
	_year = other._year;
	_month = other._month;
	_day = other._day;
	return *this;
}

bool Date::load(istream& in){
	in.read(rcastc(&_day), sizeof(_day));
	in.read(rcastc(&_month), sizeof(_month));
	in.read(rcastc(&_year), sizeof(_year));
	if (!in.good()) {
		std::cout << "Error reading" << std::endl;
		exit(-1);
	}
	return true;
}

bool Date::save(ostream& out) const{
	out.write(rcastcc(&_day), sizeof(_day));
	out.write(rcastcc(&_month), sizeof(_month));
	out.write(rcastcc(&_year), sizeof(_year));
	if (!out.good()) {
		std::cout << "Error writing" << std::endl;
		exit(-1);
	}
	return true;
}