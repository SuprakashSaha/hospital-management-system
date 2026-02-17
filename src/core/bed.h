#ifndef BED_H
#define BED_H

#include <string>

using namespace std;

class Bed {

private:
    string bedID;       // Unique bed ID
    bool occupied;      // Is bed occupied
    string patientID;   // Assigned patient ID
    string patientName; // Optional: store patient name for quick reference

public:

    /* ================= CONSTRUCTOR ================= */

    Bed(string id)
        : bedID(id),
          occupied(false),
          patientID(""),
          patientName("")
    {}

    /* ================= GETTERS ================= */

    string getBedID() const { return bedID; }
    bool isOccupied() const { return occupied; }
    string getPatientID() const { return patientID; }
    string getPatientName() const { return patientName; }

    /* ================= BED OPERATIONS ================= */

    // Assign a patient to the bed
    void assignPatient(const string &pid, const string &pname) {
        occupied = true;
        patientID = pid;
        patientName = pname;
    }

    // Release the bed after discharge
    void releaseBed() {
        occupied = false;
        patientID = "";
        patientName = "";
    }
};

#endif
