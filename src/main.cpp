#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "core/hospital.h"
#include "core/doctor.h"
#include "core/patient.h"
#include "core/appointment.h"
#include "core/bed.h"

#include "services/doctor_service.h"
#include "services/patient_service.h"
#include "services/appointment_service.h"
#include "utils/id_generator.h"
#include "storage/data_manager.h"

using namespace std;

int main()
{
    IDGenerator::init(); // Initialize random seed

    Hospital hospital;
    DataManager dataManager;

    // 🔹 Set total beds (Example: 100)
    hospital.setTotalBeds(100);

    // Load previous data
    dataManager.loadDoctors(hospital.getDoctors());
    dataManager.loadPatients(hospital.getPatients());
    dataManager.loadAppointments(hospital.getAppointments());
    dataManager.loadBeds(hospital.getBeds());

    // 🔹 If beds are empty (first run), auto-create 100 beds
    if (hospital.getBeds().empty())
    {
        for (int i = 1; i <= hospital.getTotalBeds(); ++i)
        {
            Bed bed("B" + to_string(i));
            hospital.addBed(bed);
        }
        dataManager.saveBeds(hospital.getBeds());
    }

    DoctorService doctorService;
    PatientService patientService;
    AppointmentService appointmentService;

    int choice = -1;

    while (choice != 0)
    {

        cout << "\n=== Hospital Management System ===\n";
        cout << "1. Doctor Registration\n";
        cout << "2. Doctor Login\n";
        cout << "3. Patient Registration (Outpatient)\n";
        cout << "4. Emergency Patient Registration\n";
        cout << "5. Book Appointment\n";
        cout << "6. Show Departments & Number of Doctors\n";
        cout << "7. Show Total Patients Served\n";
        cout << "8. Show Bed Status\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";

        cin >> choice;
        cin.ignore(10000, '\n');

        switch (choice)
        {

        case 1:
            doctorService.registerDoctor(hospital);
            dataManager.saveDoctors(hospital.getDoctors());
            break;

        case 2:
            doctorService.login(hospital);
            dataManager.saveDoctors(hospital.getDoctors());
            break;

        case 3:
            patientService.registerPatient(hospital);
            dataManager.savePatients(hospital.getPatients());
            break;

        case 4:
            patientService.registerEmergencyPatient(hospital);
            dataManager.savePatients(hospital.getPatients());
            dataManager.saveBeds(hospital.getBeds());
            break;

        case 5:
            appointmentService.bookAppointment(hospital);
            dataManager.saveAppointments(hospital.getAppointments());
            dataManager.saveDoctors(hospital.getDoctors());
            break;

        case 6:
        {
            cout << "\nDepartments Available:\n";
            vector<string> depts;

            for (auto &d : hospital.getDoctors())
            {
                if (find(depts.begin(), depts.end(), d.getDepartment()) == depts.end())
                    depts.push_back(d.getDepartment());
            }

            for (auto &dep : depts)
            {
                int count = 0;
                for (auto &d : hospital.getDoctors())
                    if (d.getDepartment() == dep)
                        count++;

                cout << dep << " - " << count << " doctor(s)\n";
            }

            break;
        }

        case 7:
            cout << "\nTotal Patients Served: "
                 << hospital.getPatients().size() << endl;
            break;

        case 8:
            cout << "\n=== Bed Status ===\n";
            cout << "Total Beds: " << hospital.getTotalBeds() << endl;
            cout << "Occupied Beds: " << hospital.getOccupiedBeds() << endl;
            cout << "Available Beds: " << hospital.getAvailableBeds() << endl;
            break;

        case 0:
            cout << "Exiting... Saving Data.\n";
            dataManager.saveDoctors(hospital.getDoctors());
            dataManager.savePatients(hospital.getPatients());
            dataManager.saveAppointments(hospital.getAppointments());
            dataManager.saveBeds(hospital.getBeds());
            break;

        default:
            cout << "Invalid choice! Try again.\n";
            break;
        }
    }

    return 0;
}
