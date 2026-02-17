#ifndef EMERGENCY_SERVICE_H
#define EMERGENCY_SERVICE_H

#include "../core/hospital.h"

class EmergencyService {
private:
    string generatePatientID() {
        string id = "P";
        for(int i=0;i<6;i++)
            id += to_string(rand()%10);
        return id;
    }

public:
    void admitEmergency(Hospital &hospital) {

        string name, gender, address;
        int age;

        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Gender: ";
        cin >> gender;
        cout << "Enter Age: ";
        cin >> age;
        cout << "Enter Address: ";
        cin >> address;

        for(auto &bed : hospital.getBeds()) {
            if(bed.isAvailable()) {

                string id = generatePatientID();
                Patient p(id, name, age, gender, address, "EMERGENCY");
                hospital.addPatient(p);

                bed.allocate(id);

                cout << "Emergency Admission Successful!\n";
                cout << "Patient ID: " << id << endl;
                cout << "Allocated Bed: " << bed.getBedID() << endl;
                return;
            }
        }

        cout << "No Beds Available!\n";
    }
};

#endif
