#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "doctor.h"
#include "patient.h"
#include "appointment.h"
#include "bed.h"

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Hospital
{

private:
    vector<Doctor> doctors;
    vector<Patient> patients;
    vector<Appointment> appointments;
    vector<Bed> beds;

    int totalPatientsServed = 0;

    // 🔹 NEW: Bed Capacity Control
    int totalBeds = 0;

public:
    /* ================= ADD FUNCTIONS ================= */

    void addDoctor(const Doctor &d)
    {
        doctors.push_back(d);
    }

    void addPatient(const Patient &p)
    {
        patients.push_back(p);
    }

    void addAppointment(const Appointment &a)
    {
        appointments.push_back(a);
    }

    void addBed(const Bed &b)
    {
        beds.push_back(b);
    }

    void showDepartments(Hospital &hospital)
    {
        vector<string> depts;
        for (auto &d : hospital.getDoctors())
        {
            if (find(depts.begin(), depts.end(), d.getDepartment()) == depts.end())
                depts.push_back(d.getDepartment());
        }

        cout << "\nAvailable Departments:\n";
        for (auto &dept : depts)
            cout << " - " << dept << endl;
    }

    /* ================= GETTERS ================= */

    vector<Doctor> &getDoctors()
    {
        return doctors;
    }

    vector<Patient> &getPatients()
    {
        return patients;
    }

    vector<Appointment> &getAppointments()
    {
        return appointments;
    }

    vector<Bed> &getBeds()
    {
        return beds;
    }

    /* ================= BED MANAGEMENT ================= */

    // Set total number of beds (Example: 100)
    void setTotalBeds(int bedsCount)
    {
        totalBeds = bedsCount;
    }

    // Get total beds
    int getTotalBeds() const
    {
        return totalBeds;
    }

    // Get occupied beds
    int getOccupiedBeds() const
    {
        int occupied = 0;
        for (const auto &b : beds)
        {
            if (b.isOccupied())
                occupied++;
        }
        return occupied;
    }

    // Get available beds
    int getAvailableBeds() const
    {
        return totalBeds - getOccupiedBeds();
    }

    /* ================= STATS ================= */

    int getTotalPatientsServed() const
    {
        return totalPatientsServed;
    }

    void setTotalPatientsServed(int total)
    {
        totalPatientsServed = total;
    }

    void incrementPatientsServed()
    {
        totalPatientsServed++;
    }
};

#endif
