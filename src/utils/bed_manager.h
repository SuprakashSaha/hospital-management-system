#ifndef BED_MANAGER_H
#define BED_MANAGER_H

#include "../core/bed.h"
#include <vector>

using namespace std;

class BedManager {
public:
    static void initializeBeds(vector<Bed> &beds, int totalBeds) {
        beds.clear();
        for(int i = 1; i <= totalBeds; i++) {
            beds.push_back(Bed(i));
        }
    }

    static int allocateBed(vector<Bed> &beds, string patientID) {
        for(auto &bed : beds) {
            if(bed.isAvailable()) {
                bed.allocate(patientID);
                return bed.getBedID();
            }
        }
        return -1; // No bed available
    }

    static void freeBed(vector<Bed> &beds, string patientID) {
        for(auto &bed : beds) {
            if(bed.getPatientID() == patientID) {
                bed.freeBed();
                break;
            }
        }
    }

    static void showBeds(vector<Bed> &beds) {
        for(auto &bed : beds) {
            bed.display();
        }
    }
};

#endif
