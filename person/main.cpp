#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Person {
public:
    Person(const string& type = "Person", const string& name = "")
            : Type(type), Name(name) {}

    void DoAction(const string& action) const {
        cout << Type << ": " << Name << " " << action << endl;
    }

    virtual void Walk(const string& destination) const {
        DoAction("walks to: " + destination);
    }

    const string GetName() const {
        return Name;
    }

    const string GetType() const {
        return Type;
    }

private:
    const string Type;

protected:
    const string Name;
};

class Student : public Person {
public:
    Student(const string& name, const string& favouriteSong)
            : Person("Student", name), FavouriteSong(favouriteSong) {}

    void Learn() const {
        DoAction("learns");
    }

    void Walk(const string& destination) const override {
        DoAction("walks to: " + destination);
        SingSong();
    }

    void SingSong() const {
        DoAction("sings a song: " + FavouriteSong);
    }

public:
    const string FavouriteSong;
};


class Teacher : public Person {
public:
    Teacher(const string& name, const string& subject)
            : Person("Teacher", name), Subject(subject) {}

    void Teach() const {
        DoAction("teaches: " + Subject);
    }

public:
    const string Subject;
};


class Policeman : public Person {
public:
    Policeman(const string& name) : Person("Policeman", name) {}

    void Check(const Person& p) const {
        ostringstream action;
        action << "checks " << p.GetType() << ". " << p.GetType() << "'s name is: " << p.GetName();
        DoAction(action.str());
    }
};

void VisitPlaces(const Person& p, const vector<string>& places) {
    for (const auto& place : places) {
        p.Walk(place);
    }
}

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});

    return 0;
}
