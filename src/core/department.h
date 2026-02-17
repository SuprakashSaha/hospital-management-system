#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <iostream>
using namespace std;

class Department {
private:
    string departmentName;
    int doctorCount;

public:
    Department() {}
    Department(string name)
        : departmentName(name), doctorCount(0) {}

    void incrementDoctor() { doctorCount++; }

    string getName() const { return departmentName; }
    int getDoctorCount() const { return doctorCount; }

    void display() const {
        cout << departmentName
             << " - Doctors: "
             << doctorCount << endl;
    }
};

#endif
