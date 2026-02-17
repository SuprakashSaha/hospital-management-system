#ifndef PATIENT_SERVICE_H
#define PATIENT_SERVICE_H

#include "../core/patient.h"
#include "../core/hospital.h"
#include "../core/bed.h"
#include "../utils/id_generator.h"

#include <iostream>
#include <string>

using namespace std;

class PatientService {

public:

    // Register a normal outpatient
    void registerPatient(Hospital &hospital) {

        cin.clear();
        cin.ignore(10000, '\n');

        string name, gender;
        int ageYears, ageMonths;

        cout << "\n=== Patient Registration (Outpatient) ===\n";

        // Name
        cout << "Enter Name: ";
        getline(cin, name);

        // Gender validation
        do {
            cout << "Enter Gender (Male/Female/Others): ";
            getline(cin, gender);
        } while (!Patient::isValidGender(gender));

        // Age validation
        do {
            cout << "Enter Age (Years): ";
            cin >> ageYears;
            cout << "Enter Age (Months): ";
            cin >> ageMonths;
            cin.ignore(10000, '\n');
        } while (!Patient::isValidAge(ageYears, ageMonths));

        // Generate unique patient ID
        string id = IDGenerator::generatePatientID();

        // Create patient object
        Patient p(id, name, ageYears, ageMonths, gender);

        // Add to hospital system
        hospital.addPatient(p);

        cout << "\nPatient registered successfully!\n";
        cout << "Patient ID: " << id << endl;
    }

    // Register an emergency patient
    void registerEmergencyPatient(Hospital &hospital) {

        cin.clear();
        cin.ignore(10000, '\n');

        string name, gender, address;
        int ageYears, ageMonths;

        cout << "\n=== Emergency Patient Registration ===\n";

        // Name
        cout << "Enter Name: ";
        getline(cin, name);

        // Gender validation
        do {
            cout << "Enter Gender (Male/Female/Others): ";
            getline(cin, gender);
        } while (!Patient::isValidGender(gender));

        // Age validation
        do {
            cout << "Enter Age (Years): ";
            cin >> ageYears;
            cout << "Enter Age (Months): ";
            cin >> ageMonths;
            cin.ignore(10000, '\n');
        } while (!Patient::isValidAge(ageYears, ageMonths));

        // Address
        cout << "Enter Address: ";
        getline(cin, address);

        // Generate unique patient ID
        string id = IDGenerator::generatePatientID();

        // Assign bed if available
        Bed* assignedBed = nullptr;
        for (auto &b : hospital.getBeds()) {
            if (!b.isOccupied()) {
                b.assignPatient(id, name);
                assignedBed = &b;
                break;
            }
        }

        if (assignedBed) {
            cout << "Assigned Bed ID: " << assignedBed->getBedID() << endl;
        } else {
            cout << "No beds available! Patient will wait.\n";
        }

        // Create patient object
        Patient p(id, name, ageYears, ageMonths, gender, address);

        // Add to hospital system
        hospital.addPatient(p);

        cout << "\nEmergency Patient registered successfully!\n";
        cout << "Patient ID: " << id << endl;
    }
};

#endif
