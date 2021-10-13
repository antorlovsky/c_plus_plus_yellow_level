#include "node.h"

bool EmptyNode::Evaluate(const Date& date, const string& event) const {
    return true;
}

DateComparisonNode::DateComparisonNode(Comparison cmp, const Date& date) : cmp_(cmp), date_(date) {}

bool DateComparisonNode::Evaluate(const Date& date, const string& event) const {
    return CompareValues(cmp_, date, date_);
}

EventComparisonNode::EventComparisonNode(Comparison cmp, const string value): cmp_(cmp), value_(value) {}

bool EventComparisonNode::Evaluate(const Date& date, const string& event) const {
    return CompareValues(cmp_, event, value_);
}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation operation, shared_ptr<Node> left, shared_ptr<Node> right)
    : operation_(operation), left_(left), right_(right) {}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
    switch (operation_) {
        case LogicalOperation::Or:
            return left_->Evaluate(date, event) || right_->Evaluate(date, event);
        case LogicalOperation::And:
            return left_->Evaluate(date, event) && right_->Evaluate(date, event);
    }
}
