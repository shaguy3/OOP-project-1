#include "date.h"

Date::Date(int _day, int _month, int _year) :
    day(_day), month(_month), year(_year) {}

int Date::getDay() {
    return day;
}