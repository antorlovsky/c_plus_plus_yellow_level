#pragma once

#include "date.h"

#include <memory>
#include <string>

using namespace std;

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class LogicalOperation {
    Or,
    And
};

template <typename T>
bool CompareValues(Comparison cmp, const T& lhs, const T& rhs) {
    switch (cmp) {
        case Comparison::Less:
            return lhs < rhs;
        case Comparison::LessOrEqual:
            return lhs <= rhs;
        case Comparison::Greater:
            return lhs > rhs;
        case Comparison::GreaterOrEqual:
            return lhs >= rhs;
        case Comparison::Equal:
            return lhs == rhs;
        case Comparison::NotEqual:
            return lhs != rhs;
    }
}

class Node {
public:
    virtual bool Evaluate(const Date& date, const string& event) const = 0;
};

class EmptyNode : public Node {
public:
    bool Evaluate(const Date& date, const string& event) const override;
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(Comparison cmp, const Date& date);

    bool Evaluate(const Date& date, const string& event) const override;

private:
    const Comparison cmp_;
    const Date date_;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(Comparison cmp, const string value);

    bool Evaluate(const Date& date, const string& event) const override;

private:
    const Comparison cmp_;
    const string value_;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(const LogicalOperation operation, shared_ptr<Node> left, shared_ptr<Node> right);

    bool Evaluate(const Date& date, const string& event) const override;

private:
    LogicalOperation operation_;
    shared_ptr<const Node> left_, right_;
};