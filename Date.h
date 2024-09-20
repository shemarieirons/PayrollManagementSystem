#ifndef DATE_H
#define DATE_H
#include <iostream>
#include <stdexcept>
#include <limits>

using namespace std;

class Date {
private:
    int day;
    int month;
    int year;

public:
    Date() {
        day = 0;
        month = 0;
        year = 0;
    }

    void setDate(int m, int d, int y) {
        while (true) {
            try {
                if (valid(m, d, y)) {
                    day = d;
                    month = m;
                    year = y;
                    break;  // Exit the loop if the input is valid
                } else {
                    cout << "\033[31m";
                    throw invalid_argument("Invalid date.\033[0m");
                }
            } catch (const invalid_argument& e) {
                cerr << e.what() << endl;
                // Prompt the user to enter the date again
                cout << "Enter date (in the format mm dd yy): ";
                cin >> m >> d >> y;

                if (cin.fail()) {
                    // Clear the fail state
                    cin.clear();
                    // Ignore the rest of the input until a newline character
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cerr << "Invalid input. Please enter integers for the date." << endl;
                }
            }
        }
    }

    string getDay() const {
        return (day < 10) ? "0" + to_string(day) : to_string(day);
    }

    string getMonth() const {
        return (month < 10) ? "0" + to_string(month) : to_string(month);
    }

    int getYear() const {
        return year;
    }

    string getDate() {
        return getMonth() + "/" + getDay() + "/" + to_string(getYear());
    }

    bool valid(int m, int d, int y) {
        return (m >= 1 && m <= 12) && (d >= 1 && d <= 31) && (y >= 1000 && y <= 9999);
    }

    int setDateFromString()
    {
        return day, month, year;
    }
};
#endif