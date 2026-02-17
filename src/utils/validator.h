#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <iostream>
#include <regex>

using namespace std;

class Validator {
public:
    static bool validateAge(int age) {
        return age > 0 && age < 120;
    }

    static bool validateGender(string gender) {
        return (gender == "Male" ||
                gender == "Female" ||
                gender == "Other");
    }

    static bool validateTimeFormat(string time) {
        regex pattern("^([01][0-9]|2[0-3]):([0-5][0-9])$");
        return regex_match(time, pattern);
    }
};

#endif
