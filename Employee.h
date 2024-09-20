#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "Dept.h"
#include "Date.h"

using namespace std;

class Employee : public Dept, public Date {
private:
    int id;
    string fname;
    string lname;
    int deptCode;
    string position;
    double hours;
    string trn;
    string nis;
    Date dob;
    Date hired;
    string empDeptName;
    double empRegRate;
    double empOvrRate;

public:
    Employee() {
        deptCode = 0;
        id = 0;
        fname = " ";
        lname = " ";
        trn = " ";
        nis = " ";
        dob.setDate(1, 1, 1000);
        hired.setDate(1, 1, 1000);
        position = " ";
        hours = 0;
    }

    int getId() {
        return id;
    }

    string getFname() {
        return fname;
    }

    string getLname() {
        return lname;
    }

    int getDeptCode() {
        return deptCode;
    }

    string getPosition() {
        return position;
    }

    double getHours() {
        return hours;
    }

    string getTrn() {
        return trn;
    }

    string getNis() {
        return nis;
    }

    string getDob() {
        return dob.getDate();
    }

    string getHired() {
        return hired.getDate();
    }

    string getEmpDeptName() {
        return empDeptName;
    }

    double getEmpRegRate() {
        return empRegRate;
    }

    double getEmpOvrRate() {
        return empOvrRate;
    }

    

    void addRecord() {
        ofstream file("Employee.txt", ios::app);
        if (!file.is_open()) {
            cout << "\033[31m";
            throw runtime_error("Error opening file.\033[0m");
        }

        Employee newEmp;
        while (true)
        {
            cout << "Enter Employee ID No: ";
            while (!(cin >> newEmp.id) || cin.fail() || newEmp.id< 0)
            {
                cin.clear();  // clear input buffer to restore cin to a usable state
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // ignore last input
                cout << "\033[31m";

                if (cin.fail())
                {
                    cerr << "Invalid input. Please enter an integer.\033[0m" << endl;
                }
                else
                {
                    cerr << "Invalid Input.  Please ensure the ID Number is a positive integer.\033[0m" << endl;
                }

                cout << "Enter Employee ID No: ";
            }

            if (!codeExists(newEmp.id))
            {
                break;
            }

            cout << "\033[31m";
            cerr << "Employee with ID number " << newEmp.id << " already exists. Please enter a different number.\033[0m" << endl;
        }

        cin.ignore();
        cout << "Enter Employee First Name: ";
        getline(cin, newEmp.fname);
        while (newEmp.fname.empty()) {
            cout << "\033[31m";
            throw invalid_argument("The employee must have a first name.\033[0m");
            cout << "Enter Employee First Name: ";
            getline(cin, newEmp.fname);
        }

        cout << "Enter Employee Last Name: ";
        getline(cin, newEmp.lname);
        while (newEmp.lname.empty()) {
            cout << "\033[31m";
            throw invalid_argument("The employee must have a last name.\033[0m");
            cout << "Enter Employee Last Name: ";
            getline(cin, newEmp.lname);
        }

        int cont=1;
            do{
                cout << endl;
                cout << "Department Codes" << endl;
                Dept::viewNames();
                cout << "Enter Employee Department code: ";
                int temp;
                cin >> temp;
                if (Dept::codeExists(temp) == true)
                {
                    newEmp.deptCode = temp;
                    newEmp.empDeptName = readDeptNameFromFile(temp);
                    newEmp.empRegRate = readRegRateFromFile(temp);
                    newEmp.empOvrRate = readOvrRateFromFile(temp);
                    cont = 0;
                }
                else
                {
                    cout << "\033[31m";
                    cout << "Code was not found. Please ensure department exists.\033[0m"<<endl;
                }
            }while(cont!=0);
        cin.ignore();

        cout << "Enter Employee TRN: ";
        getline(cin, newEmp.trn);
        while (newEmp.trn.empty()) {
            cout << "\033[31m";
            throw invalid_argument("The employee must have a TRN.\033[0m");
            cout << "Enter Employee TRN: ";
            getline(cin, newEmp.trn);
        }

        cout << "Enter Employee NIS: ";
        getline(cin, newEmp.nis);
        while (newEmp.nis.empty()) {
            cout << "\033[31m";
            throw invalid_argument("The employee must have a NIS.\033[0m");
            cout << "Enter Employee NIS: ";
            getline(cin, newEmp.nis);
        }
        
        cout << "Enter Employee Date of Birth in the format (mm dd yyyy): ";
        int m, d, y;
        cin >> m >> d >> y;
        cin.ignore();
        newEmp.dob.setDate(m,d,y);
        while (newEmp.dob.getDate().empty()) {
            cout << "\033[31m";
            throw invalid_argument("The employee must have a birth date.\033[0m");
            cout << "Enter Employee Date of Birth in the format (mm dd yyyy): ";
            int m, d, y;
            cin >> m >> d >> y;
            cin.ignore();
            newEmp.dob.setDate(m,d,y);
        }

        cout << "Enter Employee Date of Hire in the format (mm dd yyyy):";
        cin >> m >> d >> y;
        newEmp.hired.setDate(m,d,y);
        cin.ignore();
        while (newEmp.hired.getDate().empty()) {
            cout << "\033[31m";
            throw invalid_argument("The employee must have a hiring date.\033[0m");
            cout << "Enter Employee Date of Hire in the format (mm dd yyyy):";
            cin >> m >> d >> y;
            newEmp.hired.setDate(m,d,y);
            cin.ignore();
        }

        cout << "Enter Employee Position: ";
        getline(cin, newEmp.position);
        while (newEmp.position.empty()) {
            cout << "\033[31m";
            throw invalid_argument("The employee must have a position.\033[0m");
            cout << "Enter Employee Position: ";
            getline(cin, newEmp.position);
        }

        cout << "Enter Employee's hours worked: ";
        while (!(cin >> newEmp.hours) || newEmp.hours < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\033[31m";
        
        if (cin.fail()) {
            cerr << "Invalid input. Please enter a numerical value.\033[0m" << endl;
        } else {
            cerr << "Invalid input. Hours worked should not be negative.\033[0m" << endl;
        }

        cout << "Enter Employee's hours worked: ";
        }

        file << newEmp.getId() << "\t" << newEmp.getFname() << "\t" << newEmp.getLname() << "\t" << newEmp.getDeptCode() << "\t" << newEmp.getPosition() << "\t" << newEmp.getHours() << "\t" << newEmp.getTrn() << "\t" << newEmp.getNis() << "\t" << newEmp.dob.getDate() << "\t" << newEmp.hired.getDate() <<"\t" << newEmp.getEmpRegRate() << "\t" << newEmp.getEmpOvrRate() << "\t" << newEmp.getEmpDeptName() << endl;
        cout << "\033[32m" << "Record added successfully" << "\033[0m" << endl;
        file.close();
    }

    void viewAll() {
        ifstream file("Employee.txt");
        if (!file.is_open()) {
            cout << "\033[31m";
            throw runtime_error("Error opening file.\033[0m");
            return;
        }

        Employee emp1;
        int tempCode;
        string tempDOB = emp1.dob.getDate(), tempHired = emp1.hired.getDate();
        bool recordsExist = false; 

        cout << left << setw(8) << "ID" << setw(15) << "First" << setw(15) << "Last" << setw(8) << "Dept."
             << setw(20) << "Position" << setw(20) << "Hours" << endl;
        cout << left << setw(8) << "No. " << setw(15) << "Name" << setw(15) << "Name" << setw(8) << "Code" << setw(10) << "Worked"<< endl;

        while (file >> emp1.id){
            file.ignore();
            getline (file, emp1.fname, '\t');
            getline(file, emp1.lname, '\t');
            file >> tempCode;
            file.ignore();
            getline(file, emp1.position, '\t'); // Read the department name until the next tab character
            file >> emp1.hours >> emp1.trn >> emp1.nis >> tempDOB >> tempHired >> emp1.regRate >> emp1.empOvrRate;
            file.ignore(); // Ignore the tab character after reading code
            getline(file, emp1.deptName);
            emp1.deptCode = tempCode;
            cout << left << setw(8) << emp1.getId() << setw(15) << emp1.getFname() << setw(15) << emp1.getLname()
            << setw(8) << emp1.getDeptCode() << setw(20) << emp1.getPosition() << setw(10) << emp1.getHours() << endl;
            recordsExist = true;
        }

        file.close();
        if (!recordsExist)
        {
            system("cls");
            cout << "\033[31m";
            cerr << "No records found in the file.  Please ensure that you have added records.\033[0m" << endl;
        }
    }


    void viewRecord(int specific) {
        ifstream file("Employee.txt");
        if (!file.is_open()) {
            cout << "\033[31m";
            throw runtime_error("Error opening file.\033[0m");
            return;
        }

        Employee emp1;
        int tempCode;
        string tempDOB = emp1.dob.getDate(), tempHired = emp1.hired.getDate();
        bool found = false;
        while (file >> emp1.id){ 
            getline (file, emp1.fname, '\t');
            getline(file, emp1.lname, '\t');
            file >> tempCode;
            file.ignore();
            getline(file, emp1.position, '\t'); // Read the department name until the next tab character
            file >> emp1.hours >> emp1.trn >> emp1.nis >> tempDOB >> tempHired >> emp1.empRegRate >> emp1.empOvrRate;
            file.ignore(); // Ignore the tab character after reading code
            getline(file, emp1.deptName);
            if (emp1.getId() == specific) {
                found = true;
                emp1.deptCode = tempCode;
                cout << left << setw(8) << "ID" << setw(15) << "First" << setw(15) << "Last" << setw(8) << "Dept."
                << setw(20) << "Position" << setw(20) << "Hours" << endl;
                cout << left << setw(8) << "No. " << setw(15) << "Name" << setw(15) << "Name" << setw(8) << "Code" << setw(10) << "Worked"<< endl;
                cout << left << setw(8) << emp1.getId() << setw(15) << emp1.getFname() << setw(15) << emp1.getLname() << setw(8) << emp1.getDeptCode() << setw(20) << emp1.getPosition() << setw(10) << emp1.getHours() << endl;
                break;
            }
        }

        if (!found) {
            cout << "\033[31m";
            cout << "Employee with ID number " << specific << " not found.\033[0m" << endl;
        }

        file.close();
    }

    void updateRecord(int update) {
        ifstream updateFile("Employee.txt");
        if (!updateFile.is_open()) {
            cout << "\033[31m";
            cerr << "Error opening file.\033[0m" << endl;
            return;
        }

        ofstream tempFile("temp.txt");
        if (!tempFile.is_open()) {
            cout << "\033[31m";
            cerr << "Error opening the temporary file created.\033[0m" << endl;
            return;
        }

        Employee emp1;
        int tempCode;
        string tempDOB, tempHired;

        bool found = false;
        while (updateFile >> emp1.id)
        {
            updateFile.ignore();
            getline (updateFile, emp1.fname, '\t');
            getline (updateFile, emp1.lname, '\t');
            updateFile >> tempCode;
            updateFile.ignore();
            getline(updateFile, emp1.position, '\t'); // Read the department name until the next tab character
            updateFile >> emp1.hours >> emp1.trn >> emp1.nis >> tempDOB >> tempHired >> emp1.empRegRate >> emp1.empOvrRate;
            updateFile.ignore(); // Ignore the tab character after reading code
            getline(updateFile, emp1.deptName);
            
            emp1.deptCode = tempCode;

            if (emp1.getId() == update) 
            {
                found = true;
                while (true)
                {
                    cout << "\033[32m" << "Employee found. Choose what to update:" << "\033[0m" << endl;
                    cout << left << setw(30) << "1. Employee ID" << setw(30) << "2. First Name" << setw(30) << "3. Last Name" 
                    << setw(30)  << "\n4. Department Code" << setw(30) << "5. Position" << setw(30) << "6. TRN" << 
                    setw(30)  <<"\n7. NIS" << setw(30) << "8. Date of Birth" << setw(30) << "9. Date Hired" << 
                    setw(30)  << "\n10. Hours" << setw(30)  << "Anything else to cancel" << endl;
                    int upd;
                    while (!(cin >> upd) || cin.fail() || (upd < 1 ) || (upd > 10))
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "\033[31m";
                        if (cin.fail()) {
                            cerr << "Invalid input. Please enter a numerical value.\033[0m" << endl;
                        } else {
                            cerr << "Input does not match any menu item.\033[0m" << endl;
                        }

                        cout << "Please select from the menu: ";
                    }
                    cin.ignore();

                    int cont = 1;
                    switch (upd)
                    {
                    case 1:
                        cout << "Enter new Employee ID No: ";
                        if (!(cin >> emp1.id) || cin.fail() || emp1.id < 0)
                        {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "\033[31m";

                            if (cin.fail())
                            {
                                cerr << "Invalid input. ID number should be a positive integer.\033[0m" << endl;
                            }
                            else
                            {
                                cerr << "Invalid input. ID number should be a positive integer.\033[0m" << endl;
                            }

                            break;
                        }

                        if (!codeExists(emp1.id)) {
                            break;
                        }

                        cout << "\033[31m";
                        cerr << "Employee with id " << emp1.id << " already exists. Please enter a different id number.\033[0m" << endl;
                        break;
                    
                    case 2:
                        cin.ignore();
                        cout << "Enter new Employee First Name: ";
                        getline(cin, emp1.fname);
                        while (emp1.fname.empty()) {
                            cout << "\033[31m";
                            throw invalid_argument("The employee must have a first name.\033[0m");
                            cout << "Enter new Employee First Name: ";
                            getline(cin, emp1.fname);
                        }                        
                        break;
                    
                    case 3:
                        cout << "Enter new Employee Last Name: ";
                        getline(cin, emp1.lname);
                        while (emp1.lname.empty()) {
                            cout << "\033[31m";
                            throw invalid_argument("The employee must have a last name.\033[0m");
                            cout << "Enter new Employee Last Name: ";
                            getline(cin, emp1.lname);
                        }
                        break;
                    
                    case 4:
                        do{
                            cout << endl;
                            cout << "Department Codes" << endl;
                            Dept::viewNames();
                            cout << "Enter new Employee Department code: ";
                            int temp;
                            cin >> temp;
                            if (Dept::codeExists(temp) == true)
                            {
                                emp1.deptCode = temp;
                                emp1.empDeptName = readDeptNameFromFile(temp);
                                emp1.empRegRate = readRegRateFromFile(temp);
                                emp1.empOvrRate = readOvrRateFromFile(temp);
                                cont = 0;
                            }
                            else
                            {
                                cout << "\033[31m";
                                cout << "Code was not found. Please ensure department exists.\033[0m"<<endl;
                            }
                        }while(cont!=0);
                        cin.ignore();
                        break;

                    case 5:
                        cout << "Enter new Employee Position: ";
                        getline(cin, emp1.position);
                        while (emp1.position.empty()) {
                            cout << "\033[31m";
                            throw invalid_argument("The employee must have a position.\033[0m");
                            cout << "Enter new Employee Position: ";
                            getline(cin, emp1.position);
                        }
                        break;
                    
                    case 6:
                        cout << "Enter new Employee TRN: ";
                        getline(cin, emp1.trn);
                        while (emp1.trn.empty()) {
                            cout << "\033[31m";
                            throw invalid_argument("The employee must have a TRN.\033[0m");
                            cout << "Enter new Employee TRN: ";
                            getline(cin, emp1.trn);
                        }
                        break;
                    
                    case 7:
                        cout << "Enter new Employee NIS: ";
                        getline(cin, emp1.nis);
                        while(emp1.nis.empty()){
                            cout << "\033[31m";
                            throw invalid_argument("The employee must have a NIS.\033[0m");
                            cout << "Enter new Employee NIS: ";
                            getline(cin, emp1.nis);
                        }
                        break;

                    case 8:
                        cout << "Enter new Employee new Date of Birth in the format (mm dd yyyy): ";
                        int m, d, y;
                        cin >> m >> d >> y;
                        cin.ignore();
                        emp1.dob.setDate(m,d,y);
                        while (emp1.dob.getDate().empty()) {
                            cout << "\033[31m";
                            throw invalid_argument("The employee must have a birth date.\033[0m");
                            cout << "Enter new Employee new Date of Birth in the format (mm dd yyyy): ";
                            int m, d, y;
                            cin >> m >> d >> y;
                            cin.ignore();
                            emp1.dob.setDate(m,d,y);
                        }
                        tempDOB = emp1.dob.getDate();
                        break;

                    case 9:
                        cout << "Enter new Employee Date of Hire in the format (mm dd yyyy):";
                        cin >> m >> d >> y;
                        cin.ignore();
                        emp1.hired.setDate(m,d,y);
                        while (emp1.hired.getDate().empty()) {
                            cout << "\033[31m";
                            throw invalid_argument("The employee must have a birth date.\033[0m");
                            cout << "Enter new Employee Date of Hire in the format (mm dd yyyy):";
                            cin >> m >> d >> y;
                            cin.ignore();
                            emp1.setDate(m,d,y);
                            tempHired = emp1.hired.getDate();
                        }
                        break;
                    case 10:
                        cout << "Enter new Employee's hours worked: ";
                        while (!(cin >> emp1.hours) || emp1.hours < 0) 
                        {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "\033[31m";
                        
                        if (cin.fail()) {
                            cerr << "Invalid input. Please enter a numerical value.\033[0m" << endl;
                        } else {
                            cerr << "Invalid input. Hours worked should not be negative.\033[0m" << endl;
                        }

                        cout << "Enter new Employee's hours worked: ";
                        }
                        cin.ignore();
                        break;
                    default:
                        break;
                    }
                    break;
                }
                tempFile << emp1.id << "\t" << emp1.fname << "\t" << emp1.lname << "\t" << emp1.getDeptCode() << "\t" << emp1.position << "\t" << emp1.hours << "\t" << emp1.trn << "\t" << emp1.nis << "\t" << tempDOB << "\t" << tempHired <<"\t" << emp1.getEmpRegRate() << "\t" << emp1.getEmpOvrRate() << "\t" << emp1.deptName << endl;
            }
            else
            {
                tempFile << emp1.id << "\t" << emp1.fname << "\t" << emp1.lname << "\t" << emp1.getDeptCode() << "\t" << emp1.position << "\t" << emp1.hours << "\t" << emp1.trn << "\t" << emp1.nis << "\t" << tempDOB << "\t" << tempHired <<"\t" << emp1.getEmpRegRate() << "\t" << emp1.getEmpOvrRate() << "\t" << emp1.deptName << endl;
            }
        }
            updateFile.close();
            tempFile.close();

            if (!found) {
                cout << "\033[31m";
                cout << "Employee with ID number " << update << " was not found.\033[0m" << endl;
                remove("temp.txt");
            } else {
                remove("Employee.txt");
                rename("temp.txt", "Employee.txt");
                cout << "\033[32m" << "Record updated successfully" << "\033[0m" << endl;
            }
    }

    void deleteEmp(int specific) {
        ifstream inputFile("Employee.txt");
        if (!inputFile.is_open()) {
            cout << "\033[31m";
            cerr << "Error opening file.\033[0m" << endl;
            return;
        }

        ofstream tempFile("temp.txt");
        if (!tempFile.is_open()) {
            cout << "\033[31m";
            cerr << "Error opening the temporary file.\033[0m" << endl;
            return;
        }

        Employee emp1;
        int tempCode;
        string tempDOB, tempHired;
        bool found = false;
        while (inputFile >> emp1.id) {
            inputFile.ignore();
            getline (inputFile, emp1.fname, '\t');
            getline (inputFile, emp1.lname, '\t');
            inputFile >> tempCode;
            inputFile.ignore();
            getline(inputFile, emp1.position, '\t'); // Read the department name until the next tab character
            inputFile >> emp1.hours >> emp1.trn >> emp1.nis >> tempDOB >> tempHired >> emp1.empRegRate >> emp1.empOvrRate;
            inputFile.ignore(); // Ignore the tab character after reading code
            getline(inputFile, emp1.deptName);

            emp1.deptCode = tempCode;

            if (emp1.id == specific) {
                found = true;
                cout << "\033[32m" << "Record with ID " << specific << " has been deleted."<< "\033[0m" << endl;
            } else {
                emp1.deptCode = tempCode;
                tempFile << emp1.id << "\t" << emp1.fname << "\t" << emp1.lname << "\t" << emp1.getDeptCode() << "\t" << emp1.position << "\t" << emp1.hours << "\t" << emp1.trn << "\t" << emp1.nis << "\t" << tempDOB << "\t" << tempHired <<"\t" << emp1.getEmpRegRate() << "\t" << emp1.getEmpOvrRate() << "\t" << emp1.getEmpDeptName() << endl;
            }
        }

        inputFile.close();
        tempFile.close();

        if (!found) {
            cout << "\033[31m";
            cout << "Employee with ID " << specific << " was not found.\033[0m" << endl;
            remove("temp.txt");
        } else {
            remove("Employee.txt");
            rename("temp.txt", "Employee.txt");
        }
    }

    bool codeExists(int idToCheck)
    {
        ifstream file("Employee.txt");
        if (!file.is_open())
        {
            cout << "\033[31m";
            throw runtime_error ("Error opening file.\033[0m");
            return false;
        }

        Employee emp1;
        int tempCode;
        string tempDOB = emp1.dob.getDate(), tempHired = emp1.hired.getDate();
        while (file >> emp1.id){
            file.ignore();
            getline (file, emp1.fname, '\t');
            getline(file, emp1.lname, '\t');
            file >> tempCode;
            file.ignore();
            getline(file, emp1.position, '\t'); // Read the department name until the next tab character
            file >> emp1.hours >> emp1.trn >> emp1.nis >> tempDOB >> tempHired >> emp1.regRate >> emp1.empOvrRate;
            file.ignore(); // Ignore the tab character after reading code
            getline(file, emp1.deptName);
            // Check if the entered ID matches any existing ID
            if (emp1.getId() == idToCheck) {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }

    void  viewNames() {
        ifstream file("Employee.txt");
        if (!file.is_open()) {
            cout << "\033[31m";
            throw runtime_error("Error opening file.\033[0m");
            return;
        }

        Employee emp1;
        int tempCode;
        string tempDOB = emp1.dob.getDate(), tempHired = emp1.hired.getDate();
        bool recordsExist = false; 

        cout << "Employee ID Codes" << endl;

        while (file >> emp1.id){
            file.ignore();
            getline (file, emp1.fname, '\t');
            getline(file, emp1.lname, '\t');
            file >> tempCode;
            file.ignore();
            getline(file, emp1.position, '\t'); // Read the department name until the next tab character
            file >> emp1.hours >> emp1.trn >> emp1.nis >> tempDOB >> tempHired >> emp1.regRate >> emp1.empOvrRate;
            file.ignore(); // Ignore the tab character after reading code
            getline(file, emp1.deptName);
            cout << emp1.getId() << " - " << emp1.getFname() << " " << emp1.getLname() << endl;

            recordsExist = true;
        }
        file.close();
        file.close();
        if (!recordsExist)
        {
            system("cls");
            cout << "\033[31m";
            cerr << "No records found in the file.  Please ensure that you have added records.\033[0m" << endl;
        }
    }
};
#endif
