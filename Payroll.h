#ifndef PAYROLL_H
#define PAYROLL_H

    #include <iostream>
    #include <fstream>
    #include <string>
    #include <unistd.h>
    #include <stdexcept>
    #include "Employee.h"
    #include <ctime>
    #include <cstdlib>
    #include <iomanip>

    using namespace std;

    class Payroll 
    {
        private:
            Employee emp;
            string date;
            int chequeNumber;
            double regPay;
            double ovrPay;
            double grossPay;

        public:
            //constructor and initialization
            Payroll ()
            {
                emp=Employee();
                date = setCurrentDate();
                srand(static_cast<unsigned>(time(0))); //initializing random number generator seed
            }

            //getter for the date
            string getDate()
            {
                return date;
            }

            //setter for the date
            string setCurrentDate ()
            {
                //getting the current time
                time_t currentTime = time(0);
                tm* localTime = localtime(&currentTime);
                stringstream ss;

                //formatting the current time as mm/dd/yyyy
                    ss << setw(2) << setfill('0') << 1 + localTime->tm_mon
                    << "/" << setw(2) << setfill('0') << localTime->tm_mday
                    << "/" << 1900 + localTime->tm_year;

                    return ss.str(); 
            }

            //function to set a random number between 100 and 999
            int setChqNum()
            {
                chequeNumber = 100 + rand() % 900;
                return chequeNumber;
            }

            //function to calculate overtime pay based on hours and rate
            double getOvertimePay(double hours, double rate)
            {
                int ovtHours;
                ovtHours = hours - 40;
                if (ovtHours > 0)
                {
                    ovrPay = rate * ovtHours;
                    return ovrPay;
                }
                else
                {
                    return 0;
                }
            }
            
            //function to calculate regular pay based on hours and rate
            double getRegularPay(double hours, double rate)
            {
                if (hours <= 40)
                {
                    regPay = hours * rate;
                    return regPay;
                }
                else
                {
                    regPay = 40 * rate;
                    return regPay;
                }
            }

            //function to calculate gross pay
            double getGrossPay(double regPay, double ovrPay)
            {
                return regPay + ovrPay;
            }

            //function to add a payroll record
            void addRecord() 
            {
                //Opening the Employee file
                ifstream empFile("Employee.txt");
                if (!empFile.is_open()) {
                    cout << "\033[31m";
                    cerr << "Error opening employee file.\033[0m" << endl;
                    return;
                }

                //Opening the Payroll file in append mode
                ofstream payrollFile("Payroll.txt", ios::app);
                if (!payrollFile.is_open()) {
                    cout << "\033[31m";
                    cerr << "Error opening payroll file.\033[0m" << endl;
                    empFile.close();
                    return;
                }

                //Reading employee data from the Employee file and processing payroll records
                Employee empData;
                Payroll pay;
                int tempId = empData.getId();
                int tempCode = empData.getDeptCode();
                string tempPos = empData.getPosition();
                string tempDept = empData.getDeptName();
                string fName = empData.getFname(), lName = empData.getLname();
                double hours = empData.getHours();
                double regRate = empData.getEmpRegRate(), ovrRate=empData.getEmpOvrRate();
                string tempTrn=empData.getTrn();
                string tempNis= empData.getNis();
                string tempDob = empData.getDob();
                string tempHired = empData.getHired();

                
                bool recordsProcessed = false;
                while (empFile >> tempId) 
                {
                    empFile.ignore();
                    getline (empFile, fName, '\t');
                    getline (empFile, lName, '\t');
                    empFile >> tempCode;
                    empFile.ignore();
                    getline(empFile, tempPos, '\t');
                    empFile >> hours >> tempTrn >> tempNis >> tempDob >> tempHired >> regRate >> ovrRate;
                    empFile.ignore();
                    getline(empFile, tempDept);
                    
                    //Calculating payroll details
                    regPay = getRegularPay(hours, regRate);
                    ovrPay = getOvertimePay(hours, ovrRate);
                    grossPay = regPay + ovrPay;
                    date = setCurrentDate();
                    chequeNumber = setChqNum();

                    //Writing payroll records to the file
                    payrollFile << chequeNumber << "\t" << date << "\t" << tempId << "\t" << fName << "\t" << lName << "\t" << tempCode << "\t" << tempPos << "\t" << hours << "\t" 
                    << fixed << setprecision(2) << regPay << "\t" << ovrPay << "\t" << grossPay << endl;
                    recordsProcessed = true;
                }

                //Displays appropriate messages based on success or lack thereof
                if (recordsProcessed)
                {
                    cout << "\033[32m" << "Record added successfully" << "\033[0m" << endl;
                }
                else
                {
                    cout << "\033[31m" << "No records found in the employee file. Unable to add payroll records.\033[0m" << endl;
                }

                //Closing the file streams
                empFile.close();
                payrollFile.close();
            } 

            //Function to view a specific payroll record based on employee ID
            void viewRecord (int specific)
            {
                ifstream file("Payroll.txt");
                if (!file.is_open()) {
                    cout << "\033[31m";
                    throw runtime_error("Error opening file.\033[0m");
                    return;
                }

                Payroll pay;
                int tempCode, tempID;
                string fName, lName, tempPos;
                double hours;

                bool found = false;
                while (file >> pay.chequeNumber >> pay.date >> tempID)
                {
                    file.ignore();
                    getline (file, fName, '\t');
                    getline (file, lName, '\t');
                    file >> tempCode;
                    file.ignore();
                    getline (file, tempPos, '\t');
                    file >> hours >> pay.regPay >> pay.ovrPay >> pay.grossPay;
                    file.ignore();
                    if (tempID == specific) {
                        found = true;
                        cout << "\033[3m" << "Record was made on "<< pay.date << "(mm/dd/yyyy)"<< "\033[0m" << endl;
                        cout << "CHQ" << pay.chequeNumber <<endl;
                        cout << endl;
                        cout << left << setw(10) << "ID" << left << setw(15) << "First" << left << setw(15) << "Last" << left << setw(8) << "Dept." << left << setw(15) << "Position" << left << setw(8) << "Hours"
                            << left << setw(13) << "Regular" << left << setw(13) << "Overtime" << left << setw(13) << "Gross" << endl;
                        cout << left << setw(10) << "No" << left << setw(15) << "Name" << left << setw(15) << "Name" << left << setw(8) << "Code" << left << setw(15) << "" << left << setw(8) << "Worked"
                            << left << setw(13) << "Pay" << left << setw(13) << "Pay" << left << setw(13) << "Pay" << endl;
                        cout << left << setw(10) << tempID << left << setw(15) << fName << left << setw(15) << lName << left << setw(8) << tempCode << left << setw(15) << tempPos << left << setw(8) << hours
                        << fixed << setprecision(2) << left << setw(0) << "$" << left << setw(12) <<pay.regPay << left << setw(0) << "$" << left << setw(12) <<pay.ovrPay << left << setw(0) << "$" << left << setw(12) <<pay.grossPay << endl;

                        cout << endl;
                    }
                }

                if (!found) {
                    cout << "\033[31m";
                    cout << "ID number " << specific << " not found.\033[0m" << endl;
                }

                file.close();
            }            
            
            //View Department Payroll: Allows the user to view all employee payroll records for a specific department.

            void viewDept (int code)
            {
                ifstream file("Payroll.txt");
                if (!file.is_open()) {
                    cout << "\033[31m";
                    throw runtime_error("Error opening file.\033[0m");
                    return;
                }

                Payroll pay;
                int tempCode, tempID;
                string fName, lName, tempPos;
                double hours;

                bool found = false;
                while (file >> pay.chequeNumber >> pay.date >> tempID)
                {
                    file.ignore();
                    getline (file, fName, '\t');
                    getline (file, lName, '\t');
                    file >> tempCode;
                    file.ignore();
                    getline (file, tempPos, '\t');
                    file >> hours >> pay.regPay >> pay.ovrPay >> pay.grossPay;
                    file.ignore();
                    if (tempCode == code)
                    {
                        found = true;
                        cout << "\033[3m" << "Record was made on "<< pay.date << "(mm/dd/yyyy)"<< "\033[0m" << endl;
                        cout << "CHQ" << pay.chequeNumber <<endl;
                        cout << "\n";
                        cout << left << setw(10) << "ID" << left << setw(15) << "First" << left << setw(15) << "Last" << left << setw(8) << "Dept." << left << setw(15) << "Position" << left << setw(8) << "Hours"
                            << left << setw(13) << "Regular" << left << setw(13) << "Overtime" << left << setw(13) << "Gross" << endl;
                        cout << left << setw(10) << "No" << left << setw(15) << "Name" << left << setw(15) << "Name" << left << setw(8) << "Code" << left << setw(15) << "" << left << setw(8) << "Worked"
                            << left << setw(13) << "Pay" << left << setw(13) << "Pay" << left << setw(13) << "Pay" << endl;

                        cout << left << setw(10) << tempID << left << setw(15) << fName << left << setw(15) << lName << left << setw(8) << tempCode << left << setw(15) << tempPos << left << setw(8) << hours
                        << fixed << setprecision(2) << left << setw(0) << "$" << left << setw(12) <<pay.regPay << left << setw(0) << "$" << left << setw(12) <<pay.ovrPay << left << setw(0) << "$" << left << setw(12) <<pay.grossPay << endl;
                        cout << "\n";
                    }
                }

                if (!found) {
                    cout << "\033[31m";
                    cout << "Payroll for Department " << code << " not found.\033[0m" << endl;
                }

                file.close();
            }
    };
#endif

