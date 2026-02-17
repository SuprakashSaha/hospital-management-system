#ifndef DOCTOR_SERVICE_H
#define DOCTOR_SERVICE_H

#include "../core/doctor.h"
#include "../core/hospital.h"
#include "../core/appointment.h"
#include "../utils/id_generator.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class DoctorService
{

public:
    // Register a new doctor
    void registerDoctor(Hospital &hospital)
    {

        cin.clear();
        cin.ignore(10000, '\n');

        string name, degree, department;
        int age;
        int numDays;
        vector<string> days;
        string startTime, endTime;

        cout << "\n=== Doctor Registration ===\n";

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        while (!(cin >> age) || age <= 25 || age > 80)
        {
            cout << "Invalid age (25-80). Enter again: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cin.ignore(10000, '\n');

        cout << "Enter Degree (e.g., M.B.B.S, Dental): ";
        getline(cin, degree);

        cout << "Enter Department: ";
        getline(cin, department);

        cout << "Enter number of available days: ";
        while (!(cin >> numDays) || numDays <= 0 || numDays > 7)
        {
            cout << "Invalid number of days (1-7): ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cin.ignore(10000, '\n');

        days.clear();
        for (int i = 0; i < numDays; i++)
        {
            string day;
            cout << "Enter Day " << i + 1 << ": ";
            getline(cin, day);
            days.push_back(day);
        }

        cout << "Enter Start Time (HH:MM, 24h): ";
        getline(cin, startTime);
        cout << "Enter End Time (HH:MM, 24h): ";
        getline(cin, endTime);

        string id = IDGenerator::generateDoctorID();

        Doctor d(id, name, age, degree, department, days, startTime, endTime);

        hospital.addDoctor(d);

        cout << "\nDoctor Registered Successfully!\n";
        cout << "Doctor ID: " << id << endl;
    }

    // Doctor login
    void login(Hospital &hospital)
    {
        cin.clear();
        cin.ignore(10000, '\n');

        string doctorID;
        cout << "\n=== Doctor Login ===\n";
        cout << "Enter Doctor ID: ";
        getline(cin, doctorID);

        Doctor *loggedDoctor = nullptr;

        for (auto &d : hospital.getDoctors())
        {
            if (d.getDoctorID() == doctorID)
            {
                loggedDoctor = &d;
                break;
            }
        }

        if (!loggedDoctor)
        {
            cout << "Invalid Doctor ID!\n";
            return;
        }

        cout << "\nWelcome Dr. " << loggedDoctor->getName() << endl;

        vector<Appointment> &appointments = hospital.getAppointments();
        vector<int> doctorAppointmentIndexes;

        cout << "\nBooked Slots:\n";

        int count = 1;

        for (int i = 0; i < appointments.size(); ++i)
        {
            if (appointments[i].getDoctorID() == loggedDoctor->getDoctorID())
            {
                cout << count << ". "
                     << appointments[i].getDay()
                     << " | "
                     << appointments[i].getSlot()
                     << " | Patient: "
                     << appointments[i].getPatientName()
                     << endl;

                doctorAppointmentIndexes.push_back(i);
                count++;
            }
        }

        if (doctorAppointmentIndexes.empty())
        {
            cout << "No booked slots yet.\n";
            return;
        }

        int choice;
        cout << "\nEnter slot number to free (0 to exit): ";
        cin >> choice;
        cin.ignore(10000, '\n');

        if (choice == 0)
            return;

        if (choice < 1 || choice > doctorAppointmentIndexes.size())
        {
            cout << "Invalid choice!\n";
            return;
        }

        int appointmentIndex = doctorAppointmentIndexes[choice - 1];
        string slot = appointments[appointmentIndex].getSlot();

        // Free slot in doctor
        loggedDoctor->freeSlot(slot);

        // Remove appointment
        appointments.erase(appointments.begin() + appointmentIndex);

        cout << "Slot freed and appointment removed successfully!\n";
    }
};

#endif
