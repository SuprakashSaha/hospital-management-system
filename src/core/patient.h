#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <iostream>

using namespace std;

class Patient {

private:
    string patientID;
    string name;
    int ageYears;
    int ageMonths;
    string gender;
    string address;   // optional, can store for emergency patients

public:

    /* ================= CONSTRUCTOR ================= */

    Patient(string id,
            string name,
            int years,
            int months,
            string gender,
            string address = "")
        : patientID(id),
          name(name),
          ageYears(years),
          ageMonths(months),
          gender(gender),
          address(address)
    {}

    /* ================= GETTERS ================= */

    string getPatientID() const { return patientID; }
    string getName() const { return name; }
    int getAgeYears() const { return ageYears; }
    int getAgeMonths() const { return ageMonths; }
    string getGender() const { return gender; }
    string getAddress() const { return address; }

    /* ================= VALIDATION ================= */

    // Validate gender input
    static bool isValidGender(const string &g) {
        return g == "Male" || g == "Female" || g == "Others";
    }

    // Validate age input
    static bool isValidAge(int years, int months) {
        return (years >= 0 && years <= 120) &&
               (months >= 0 && months <= 11) &&
               !(years == 0 && months == 0); // at least 1 month
    }
};

#endif
