#ifndef ID_GENERATOR_H
#define ID_GENERATOR_H

#include <string>
#include <cstdlib>
#include <ctime>
#include <set>
#include <sstream>
#include <iomanip>

using namespace std;

class IDGenerator {

private:
    static set<string> usedDoctorIDs;
    static set<string> usedPatientIDs;
    static set<string> usedAppointmentIDs;

    // Helper to generate 6-digit random number as string
    static string randomSixDigits() {
        int num = rand() % 900000 + 100000; // ensures 6 digits
        stringstream ss;
        ss << setw(6) << setfill('0') << num;
        return ss.str();
    }

public:

    // Initialize random seed
    static void init() {
        srand(time(0));
    }

    // Generate unique Doctor ID
    static string generateDoctorID() {
        string id;
        do {
            id = "D" + randomSixDigits();
        } while (usedDoctorIDs.find(id) != usedDoctorIDs.end());
        usedDoctorIDs.insert(id);
        return id;
    }

    // Generate unique Patient ID
    static string generatePatientID() {
        string id;
        do {
            id = "P" + randomSixDigits();
        } while (usedPatientIDs.find(id) != usedPatientIDs.end());
        usedPatientIDs.insert(id);
        return id;
    }

    // Generate unique Appointment ID
    static string generateAppointmentID() {
        string id;
        do {
            id = "A" + randomSixDigits();
        } while (usedAppointmentIDs.find(id) != usedAppointmentIDs.end());
        usedAppointmentIDs.insert(id);
        return id;
    }
};

// Initialize static members
set<string> IDGenerator::usedDoctorIDs;
set<string> IDGenerator::usedPatientIDs;
set<string> IDGenerator::usedAppointmentIDs;

#endif
