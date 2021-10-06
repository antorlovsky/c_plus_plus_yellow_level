#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

void TestDefault() {
    {
        Rational empty;
        AssertEqual(empty.Numerator(), 0, "Default numerator");
        AssertEqual(empty.Denominator(), 1, "Default denominator");
    }
    {
        Rational r(0, 1);
        AssertEqual(r.Numerator(), 0, "Simple numerator");
        AssertEqual(r.Denominator(), 1, "Simple denominator");
    }
}

void TestReduce() {
    {
        Rational r(2, 4);
        AssertEqual(r.Numerator(), 1, "Reduce numerator");
        AssertEqual(r.Denominator(), 2, "Reduce denominator");
    }
    {
        Rational r(1, 5);
        AssertEqual(r.Numerator(), 1, "No reduce numerator");
        AssertEqual(r.Denominator(), 5, "No reduce denominator");
    }
    {
        Rational r(12, 16);
        AssertEqual(r.Numerator(), 3, "GCD reduce numerator");
        AssertEqual(r.Denominator(), 4, "GCD reduce denominator");
    }
}

void TestNegative() {
    {
        Rational r(-1, 5);
        AssertEqual(r.Numerator(), -1, "Negative numerator");
        AssertEqual(r.Denominator(), 5, "Positive denominator");
    }
    {
        Rational r(1, -5);
        AssertEqual(r.Numerator(), -1, "Positive numerator");
        AssertEqual(r.Denominator(), 5, "Negative denominator");
    }
    {
        Rational r(13, -39);
        AssertEqual(r.Numerator(), -1, "Positive reduce numerator");
        AssertEqual(r.Denominator(), 3, "Negative reduce denominator");
    }
    {
        Rational r(-13, 39);
        AssertEqual(r.Numerator(), -1, "Negative reduce numerator");
        AssertEqual(r.Denominator(), 3, "Positive reduce denominator");
    }
    {
        Rational r(-2, -3);
        AssertEqual(r.Numerator(), 2, "Negative numerator");
        AssertEqual(r.Denominator(), 3, "Negative denominator");
    }
}

void TestZero() {
    {
        Rational r(0, 1);
        AssertEqual(r.Numerator(), 0, "Zero numerator");
        AssertEqual(r.Denominator(), 1, "One denominator");
    }
    {
        Rational r(0, 10);
        AssertEqual(r.Numerator(), 0, "Zero numerator");
        AssertEqual(r.Denominator(), 1, "Non-one denominator");
    }
    {
        Rational r(0, -10);
        AssertEqual(r.Numerator(), 0, "Zero numerator");
        AssertEqual(r.Denominator(), 1, "Negative denominator");
    }
}

int main() {
    TestRunner runner;
    runner.RunTest(TestDefault, "TestDefault");
    runner.RunTest(TestReduce, "TestReduce");
    runner.RunTest(TestNegative, "TestNegative");
    runner.RunTest(TestZero, "TestZero");
    return 0;
}