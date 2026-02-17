#ifndef DISCHARGE_SERVICE_H
#define DISCHARGE_SERVICE_H

#include "../core/hospital.h"

class DischargeService {
public:
    void dischargePatient(Hospital &hospital) {

        string pid;
        cout << "Enter Patient ID to discharge: ";
        cin >> pid;

        // Free bed
        for(auto &bed : hospital.getBeds()) {
            if(bed.getPatientID() == pid) {
                bed.freeBed();
                cout << "Bed Freed.\n";
            }
        }

        // Complete appointment and free slot
        for(auto &a : hospital.getAppointments()) {
            if(a.getPatientID() == pid && a.isActive()) {
                a.discharge();

                for(auto &d : hospital.getDoctors()) {
                    if(d.getDoctorID() == a.getDoctorID()) {
                        d.addSlot(a.getSlotTime());
                        break;
                    }
                }

                hospital.incrementServed();
                cout << "Appointment Closed.\n";
            }
        }

        cout << "Discharge Completed.\n";
    }
};

#endif
