#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <memory>
#include <iomanip>

using namespace std;

class Figure {
public:
    virtual string Name() const = 0;

    virtual double Perimeter() const = 0;

    virtual double Area() const = 0;
};

class Triangle : public Figure {
public:
    Triangle(int a, int b, int c)
        : a_(a), b_(b), c_(c) {}

    string Name() const override {
        return "TRIANGLE";
    }

    double Perimeter() const override {
        return a_ + b_ + c_;
    }

    double Area() const override {
        double p = Perimeter() / 2;
        return sqrt(p * (p - a_) * (p - b_) * (p - c_));
    }

private:
    int a_, b_, c_;
};

class Rect : public Figure {
public:
    Rect(int width, int height)
            : width_(width), height_(height) {}

    string Name() const override {
        return "RECT";
    }

    double Perimeter() const override {
        return 2 * (width_ + height_);
    }

    double Area() const override {
        return width_ * height_;
    }

private:
    int width_, height_;
};

const double PI = 3.14;

class Circle : public Figure {
public:
    Circle(int r) : r_(r) {}

    string Name() const override {
        return "CIRCLE";
    }

    double Perimeter() const override {
        return 2 * PI * r_;
    }

    double Area() const override {
        return PI * r_ * r_;
    }

private:
    int r_;
};

shared_ptr<Figure> CreateFigure(istream& is) {
    string figure_type;
    is >> figure_type;

    if (figure_type == "TRIANGLE") {
        int a, b, c;
        is >> a >> b >> c;

        return make_shared<Triangle>(a, b, c);
    } else if (figure_type == "RECT") {
        int width, height;
        is >> width >> height;

        return make_shared<Rect>(width, height);
    } else if (figure_type == "CIRCLE") {
        int r;
        is >> r;

        return make_shared<Circle>(r);
    }

    return nullptr;
}

int main() {
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD") {
            is >> ws;
            figures.push_back(CreateFigure(is));
        } else if (command == "PRINT") {
            for (const auto& current_figure : figures) {
                cout << fixed << setprecision(3)
                     << current_figure->Name() << " "
                     << current_figure->Perimeter() << " "
                     << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}