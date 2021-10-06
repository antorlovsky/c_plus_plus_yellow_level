#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

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

bool IsPalindrom(const string& str) {
    int string_size = str.size();

    for (int i = 0; i < string_size / 2; ++i) {
        if (str[i] != str[string_size - 1 - i])
            return false;
    }

    return true;
}

void TestEmpty() {
    {
        Assert(IsPalindrom(""), "Empty");
    }
    {
        Assert(IsPalindrom("e"), "One symbol");
    }
    {
        Assert(IsPalindrom("ee"), "Two symbols");
    }
    {
        Assert(!IsPalindrom("ea"), "Two symbols");
    }
}

void TestSpace() {
    {
        Assert(IsPalindrom(" madam "), "Extra space");
    }
    {
        Assert(!IsPalindrom(" madam"), "Extra space");
    }
    {
        Assert(!IsPalindrom("madam "), "Extra space");
    }
    {
        Assert(IsPalindrom("ma d am"), "Extra middle space");
    }
    {
        Assert(!IsPalindrom("ma dam"), "Extra middle space");
    }
    {
        Assert(IsPalindrom("    madam    "), "Extra tab");
    }
    {
        Assert(!IsPalindrom("       madam"), "Extra tab");
    }
    {
        Assert(!IsPalindrom("madam      "), "Extra tab");
    }
}

void TestEdge() {
    {
        Assert(!IsPalindrom("amadam"), "Extra first");
    }
    {
        Assert(!IsPalindrom("madamz"), "Extra last");
    }
    {
        Assert(!IsPalindrom("madzam"), "Wrong range");
    }
    {
        Assert(!IsPalindrom("mqadzabm"), "Wrong range");
    }
}

void TestPalindrom() {
    {
        Assert(IsPalindrom("madam"), "True palindrom");
    }
    {
        Assert(IsPalindrom("wasitacaroracatisaw"), "True range");
    }
    {
        Assert(!IsPalindrom("12345"), "False palindrom");
    }
}

int main() {
    TestRunner runner;
    runner.RunTest(TestEmpty, "TestEmpty");
    runner.RunTest(TestSpace, "TestSpace");
    runner.RunTest(TestEdge, "TestEdge");
    runner.RunTest(TestPalindrom, "TestPalindrom");
    return 0;
}