#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>

using namespace std;

class Appointment {

private:
    string appointmentID;
    string doctorID;
    string patientID;
    string patientName; // track patient name for easy booking
    string day;         // e.g., Monday, Tuesday
    string slot;        // e.g., 10:00-10:15

public:

    /* ================= CONSTRUCTOR ================= */

    Appointment(string id,
                string docID,
                string patID,
                string patName,
                string day,
                string slot)
        : appointmentID(id),
          doctorID(docID),
          patientID(patID),
          patientName(patName),
          day(day),
          slot(slot)
    {}

    /* ================= GETTERS ================= */

    string getAppointmentID() const { return appointmentID; }
    string getDoctorID() const { return doctorID; }
    string getPatientID() const { return patientID; }
    string getPatientName() const { return patientName; }
    string getDay() const { return day; }
    string getSlot() const { return slot; }

    /* ================= SETTERS ================= */

    void setSlot(const string &newSlot) { slot = newSlot; }
    void setDay(const string &newDay) { day = newDay; }
};

#endif
