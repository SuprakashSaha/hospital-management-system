#ifndef APPOINTMENT_SERVICE_H
#define APPOINTMENT_SERVICE_H

#include "../core/appointment.h"
#include "../core/hospital.h"
#include "../core/doctor.h"
#include "../core/patient.h"
#include "../utils/id_generator.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class AppointmentService {

private:
    // Convert string to lowercase
    string toLower(string str) {
        transform(str.begin(), str.end(), str.begin(), ::tolower);
        return str;
    }

    // Normalize day (First letter uppercase, rest lowercase)
    string normalizeDay(string day) {
        if (day.empty()) return day;
        day = toLower(day);
        day[0] = toupper(day[0]);
        return day;
    }

public:

    // Book an appointment
    void bookAppointment(Hospital &hospital) {

        cin.clear();
        cin.ignore(10000, '\n');

        string patientName, patientID;
        cout << "\n=== Book Appointment ===\n";

        cout << "Enter Patient Name: ";
        getline(cin, patientName);

        cout << "Enter Patient ID: ";
        getline(cin, patientID);

        // Validate patient exists
        Patient* selectedPatient = nullptr;
        for (auto &p : hospital.getPatients()) {
            if (p.getPatientID() == patientID && p.getName() == patientName) {
                selectedPatient = &p;
                break;
            }
        }

        if (!selectedPatient) {
            cout << "Patient not found or name/ID mismatch!\n";
            return;
        }

        // Select day
        string day;
        cout << "Enter Day (e.g., Monday): ";
        getline(cin, day);

        day = normalizeDay(day);

        // Show doctors available on this day
        vector<Doctor*> availableDoctors;

        for (auto &d : hospital.getDoctors()) {

            for (auto &availableDay : d.getAvailableDays()) {

                if (normalizeDay(availableDay) == day) {
                    availableDoctors.push_back(&d);
                    break;
                }
            }
        }

        if (availableDoctors.empty()) {
            cout << "No doctors available on " << day << endl;
            return;
        }

        cout << "\nAvailable Doctors on " << day << ":\n";
        for (auto d : availableDoctors) {
            cout << d->getDoctorID() << " - "
                 << d->getName()
                 << " (" << d->getDepartment() << ") "
                 << d->getStartTime()
                 << " - "
                 << d->getEndTime()
                 << endl;
        }

        // Patient selects doctor
        string doctorID;
        cout << "Enter Doctor ID to select: ";
        getline(cin, doctorID);

        Doctor* selectedDoctor = nullptr;

        for (auto d : availableDoctors) {
            if (d->getDoctorID() == doctorID) {
                selectedDoctor = d;
                break;
            }
        }

        if (!selectedDoctor) {
            cout << "Invalid Doctor ID!\n";
            return;
        }

        // Show only available slots
        vector<string> freeSlots;

        for (auto &s : selectedDoctor->getSlots()) {
            if (selectedDoctor->isSlotAvailable(s)) {
                freeSlots.push_back(s);
            }
        }

        if (freeSlots.empty()) {
            cout << "No free slots available for this doctor!\n";
            return;
        }

        cout << "\nAvailable Slots:\n";
        for (int i = 0; i < freeSlots.size(); ++i) {
            cout << i + 1 << ". " << freeSlots[i] << endl;
        }

        int slotChoice;
        cout << "Select slot number: ";

        if (!(cin >> slotChoice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input!\n";
            return;
        }

        cin.ignore(10000, '\n');

        if (slotChoice < 1 || slotChoice > freeSlots.size()) {
            cout << "Invalid choice!\n";
            return;
        }

        string slot = freeSlots[slotChoice-1];

        // Book slot
        selectedDoctor->bookSlot(slot);

        // Generate appointment ID
        string appointmentID = IDGenerator::generateAppointmentID();

        // Create Appointment object
        Appointment a(
            appointmentID,
            selectedDoctor->getDoctorID(),
            selectedPatient->getPatientID(),
            selectedPatient->getName(),
            day,
            slot
        );

        hospital.addAppointment(a);

        cout << "\nAppointment booked successfully!\n";
        cout << "Appointment ID: " << appointmentID << endl;
        cout << "Doctor: " << selectedDoctor->getName() << endl;
        cout << "Patient: " << selectedPatient->getName() << endl;
        cout << "Day: " << day << ", Slot: " << slot << endl;
    }
};

#endif
