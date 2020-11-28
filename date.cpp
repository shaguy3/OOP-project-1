#include "date.h"

Date::Date(int _day, int _month, int _year) :
    day(_day), month(_month), year(_year) {}

int Date::getDay() {
    return day;
}

int Date::getMonth() {
    return month;
}

int Date::getYear() {
    return year;
}

bool Date::setDay(int _day) {
    day = _day;
}

bool Date::setMonth(int _month) {
    month = _month;
}

bool Date::setYear(int _year) {
    year = _year;
}

Date::~Date() {
}