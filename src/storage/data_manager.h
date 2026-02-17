#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "../core/doctor.h"
#include "../core/patient.h"
#include "../core/appointment.h"
#include "../core/bed.h"

#include "../utils/json.hpp"

#include <fstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;
using json = nlohmann::json;

class DataManager
{

private:
    const string doctorsFile = "storage/doctors.json";
    const string patientsFile = "storage/patients.json";
    const string appointmentsFile = "storage/appointments.json";
    const string bedsFile = "storage/beds.json";

public:
    /* ================= SAVE ================= */

    void saveDoctors(const vector<Doctor> &doctors)
    {
        json j;
        for (auto &d : doctors)
        {
            j.push_back({{"doctorID", d.getDoctorID()},
                         {"name", d.getName()},
                         {"age", d.getAge()},
                         {"degree", d.getDegree()},
                         {"department", d.getDepartment()},
                         {"availableDays", d.getAvailableDays()},
                         {"startTime", d.getStartTime()},
                         {"endTime", d.getEndTime()},
                         {"slots", d.getSlots()},
                         {"bookedSlots", d.getBookedSlots()}});
        }
        ofstream out(doctorsFile);
        out << j.dump(4);
        out.close();
    }

    void savePatients(const vector<Patient> &patients)
    {
        json j;
        for (auto &p : patients)
        {
            j.push_back({{"patientID", p.getPatientID()},
                         {"name", p.getName()},
                         {"ageYears", p.getAgeYears()},
                         {"ageMonths", p.getAgeMonths()},
                         {"gender", p.getGender()},
                         {"address", p.getAddress()}});
        }
        ofstream out(patientsFile);
        out << j.dump(4);
        out.close();
    }

    void saveAppointments(const vector<Appointment> &appointments)
    {
        json j;
        for (auto &a : appointments)
        {
            j.push_back({{"appointmentID", a.getAppointmentID()},
                         {"doctorID", a.getDoctorID()},
                         {"patientID", a.getPatientID()},
                         {"patientName", a.getPatientName()},
                         {"day", a.getDay()},
                         {"slot", a.getSlot()}});
        }
        ofstream out(appointmentsFile);
        out << j.dump(4);
        out.close();
    }

    void saveBeds(const vector<Bed> &beds)
    {
        json j;
        for (auto &b : beds)
        {
            j.push_back({{"bedID", b.getBedID()},
                         {"occupied", b.isOccupied()},
                         {"patientID", b.getPatientID()},
                         {"patientName", b.getPatientName()}});
        }
        ofstream out(bedsFile);
        out << j.dump(4);
        out.close();
    }

    /* ================= LOAD ================= */

    void loadDoctors(vector<Doctor> &doctors)
    {
        ifstream in(doctorsFile);
        if (!in.is_open())
            return;
        json j;
        in >> j;
        in.close();

        doctors.clear();
        for (auto &d : j)
        {
            Doctor doc(
                d["doctorID"],
                d["name"],
                d["age"],
                d["degree"],
                d["department"],
                d["availableDays"].get<vector<string>>(),
                d["startTime"],
                d["endTime"]);

            // Restore booked slots
            for (auto &slot : d["bookedSlots"])
                doc.bookSlot(slot);

            doctors.push_back(doc);
        }

        cout << "Loading doctors.json..." << endl;
    }

    void loadPatients(vector<Patient> &patients)
    {
        ifstream in(patientsFile);
        if (!in.is_open())
            return;
        json j;
        in >> j;
        in.close();

        patients.clear();
        for (auto &p : j)
        {
            patients.push_back(Patient(
                p["patientID"],
                p["name"],
                p["ageYears"],
                p["ageMonths"],
                p["gender"],
                p["address"]));
        }
    }

    void loadAppointments(vector<Appointment> &appointments)
    {
        ifstream in(appointmentsFile);
        if (!in.is_open())
            return;
        json j;
        in >> j;
        in.close();

        appointments.clear();
        for (auto &a : j)
        {
            appointments.push_back(Appointment(
                a["appointmentID"],
                a["doctorID"],
                a["patientID"],
                a["patientName"],
                a["day"],
                a["slot"]));
        }
    }

    void loadBeds(vector<Bed> &beds)
    {
        ifstream in(bedsFile);
        if (!in.is_open())
            return;
        json j;
        in >> j;
        in.close();

        beds.clear();
        for (auto &b : j)
        {
            Bed bed(b["bedID"]);
            if (b["occupied"])
            {
                bed.assignPatient(b["patientID"], b["patientName"]);
            }
            beds.push_back(bed);
        }
    }
};

#endif
