#ifndef DOCTOR_H
#define DOCTOR_H

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

class Doctor {

private:
    string doctorID;
    string name;
    int age;
    string degree;
    string department;

    vector<string> availableDays;  // e.g., Monday, Tuesday
    string startTime;  // HH:MM format
    string endTime;    // HH:MM format

    vector<string> slots;        // All 15-min slots
    vector<string> bookedSlots;  // Slots already booked

public:

    /* ================= CONSTRUCTOR ================= */

    Doctor(string id,
           string name,
           int age,
           string degree,
           string department,
           vector<string> days,
           string start,
           string end)
        : doctorID(id),
          name(name),
          age(age),
          degree(degree),
          department(department),
          availableDays(days),
          startTime(start),
          endTime(end)
    {
        generateSlots();
    }

    /* ================= GETTERS ================= */

    string getDoctorID() const { return doctorID; }
    string getName() const { return name; }
    int getAge() const { return age; }
    string getDegree() const { return degree; }
    string getDepartment() const { return department; }
    vector<string> getAvailableDays() const { return availableDays; }
    string getStartTime() const { return startTime; }
    string getEndTime() const { return endTime; }
    vector<string> getSlots() const { return slots; }
    vector<string> getBookedSlots() const { return bookedSlots; }

    /* ================= SLOT MANAGEMENT ================= */

    // Generate 15-min slots from startTime to endTime
    void generateSlots() {
        slots.clear();
        int sh, sm, eh, em;
        sscanf(startTime.c_str(), "%d:%d", &sh, &sm);
        sscanf(endTime.c_str(), "%d:%d", &eh, &em);

        while (sh < eh || (sh == eh && sm < em)) {
            int endH = sh;
            int endM = sm + 15;
            if (endM >= 60) {
                endM -= 60;
                endH += 1;
            }

            stringstream ss;
            ss << setw(2) << setfill('0') << sh << ":" << setw(2) << setfill('0') << sm
               << "-" << setw(2) << setfill('0') << endH << ":" << setw(2) << setfill('0') << endM;

            slots.push_back(ss.str());

            sh = endH;
            sm = endM;
        }
    }

    // Check if slot is available
    bool isSlotAvailable(const string &slot) const {
        return find(bookedSlots.begin(), bookedSlots.end(), slot) == bookedSlots.end();
    }

    // Book a slot
    void bookSlot(const string &slot) {
        if (isSlotAvailable(slot))
            bookedSlots.push_back(slot);
    }

    // Free a booked slot
    void freeSlot(const string &slot) {
        auto it = find(bookedSlots.begin(), bookedSlots.end(), slot);
        if (it != bookedSlots.end())
            bookedSlots.erase(it);
    }
};

#endif
