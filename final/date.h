#pragma once

#include <iostream>

using namespace std;

class Date {
public:
    Date(int year, int month, int day);

    int GetYear() const;

    int GetMonth() const;

    int GetDay() const;

private:
    const int year_;
    const int month_;
    const int day_;
};

Date ParseDate(istream& is);

ostream& operator<<(ostream& os, const Date& date);
bool operator<(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);