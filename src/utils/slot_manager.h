#ifndef SLOT_MANAGER_H
#define SLOT_MANAGER_H

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class SlotManager {
public:
    static vector<string> generateSlots(string start, string end) {
        vector<string> slots;

        int startHour = stoi(start.substr(0,2));
        int startMin  = stoi(start.substr(3,2));
        int endHour   = stoi(end.substr(0,2));
        int endMin    = stoi(end.substr(3,2));

        int totalStart = startHour * 60 + startMin;
        int totalEnd   = endHour * 60 + endMin;

        while(totalStart + 20 <= totalEnd) {
            int h = totalStart / 60;
            int m = totalStart % 60;

            ostringstream oss;
            if(h < 10) oss << "0";
            oss << h << ":";
            if(m < 10) oss << "0";
            oss << m;

            slots.push_back(oss.str());
            totalStart += 20;
        }

        return slots;
    }
};

#endif
