#include "date.h"

#include <tuple>
#include <iostream>

Date::Date(int year, int month, int day) : year_(year), month_(month), day_(day) {}

int Date::GetYear() const {
    return year_;
}

int Date::GetMonth() const {
    return month_;
}

int Date::GetDay() const {
    return day_;
}

Date ParseDate(istream& is) {
    char dlm1, dlm2;
    int year, month, day;
    is >> year >> dlm1 >> month >> dlm2 >> day;

    if (!is || dlm1 != '-' || dlm2 != '-')
        throw invalid_argument("Error in parse date");

    return {year, month, day};
}

ostream& operator<<(ostream& os, const Date& date) {
    os.fill('0');
    os.width(4);
    os << date.GetYear() << "-";
    os.width(2);
    os << date.GetMonth() << "-";
    os.width(2);
    os << date.GetDay();
    return os;
}

bool operator<(const Date& lhs, const Date& rhs) {
    return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) < make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator==(const Date& lhs, const Date& rhs) {
    return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) == make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator!=(const Date& lhs, const Date& rhs) {
    return !(lhs == rhs);
}

bool operator<=(const Date& lhs, const Date& rhs) {
    return lhs < rhs || lhs == rhs;
}

bool operator>(const Date& lhs, const Date& rhs) {
    return !(lhs <= rhs);
}

bool operator>=(const Date& lhs, const Date& rhs) {
    return !(lhs < rhs);
}