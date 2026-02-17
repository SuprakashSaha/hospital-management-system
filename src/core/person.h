#ifndef PERSON_H
#define PERSON_H

#include <iostream>
using namespace std;

class Person {
protected:
    string name;
    int age;

public:
    Person() {}
    Person(string n, int a) : name(n), age(a) {}

    virtual void display() const = 0;

    string getName() const { return name; }
    int getAge() const { return age; }

    void setName(string n) { name = n; }
    void setAge(int a) { age = a; }

    virtual ~Person() {}
};

#endif
