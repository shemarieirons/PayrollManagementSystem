#ifndef DEPT_H
#define DEPT_H
    #include <iostream>
    #include <fstream>
    #include <string>
    #include <unistd.h>
    #include <stdexcept>
    #include <limits>
    #include <iomanip> 
    using namespace std;

    class Dept 
    {
        protected:
            int code;
            string deptName;
            double regRate;
            double ovrRate;

        public:

            //Default connstructor
            Dept()
            {
                this->code = 0;
                this->deptName = " ";
                this->regRate = 0.00;
                this->ovrRate = 0.00;
            }

            //Primary Constructor
            Dept (int code, string deptName, double regRate, double ovrRate)
            {
                this->code = code;
                this->deptName = deptName;
                this->regRate = regRate;
                this->ovrRate = ovrRate;
            }

            //Getters
            int getCode () const
            {
                return code;
            }

            string getDeptName ()
            {
                return deptName;
            }

            double getRegRate ()
            {
                return regRate;
            }

            double getovrRate ()
            {
                return ovrRate;
            }

            void addRecord()
            {
                ofstream file ("Department.txt", ios::app);
                if (!file.is_open())
                {
                    cout << "\033[31m";
                    cerr << "Error opening file.\033[0m" << endl;
                    return;
                }

                Dept newDept;
                while (true)
                {
                    cout << "Enter Department Code: ";

                    while (!(cin >> newDept.code) || cin.fail() || newDept.code < 0)
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
                            cerr << "Invalid Input.  Please ensure the Department Code is a positive integer.\033[0m" << endl;
                        }

                        cout << "Enter Department Code: ";
                    }

                    
                    if (!codeExists(newDept.code))
                    {
                        break;
                    }

                    cout << "\033[31m";
                    cerr << "Department with code " << newDept.code << " already exists. Please enter a different code.\033[0m" << endl;
                }
                
                
                cin.ignore();
                cout << "Enter Department Name: ";                
                getline(cin, newDept.deptName);
                while (newDept.deptName.empty())
                {
                    cout << "\033[31m";
                    throw invalid_argument("The department requires a name.\033[0m");
                    cout << "Enter Department Name: ";
                    getline(cin, newDept.deptName);
                }
                
                cout << "Enter Department Regular Rate: ";
                while (!(cin >> newDept.regRate) || cin.fail() || newDept.regRate < 0.0)
                {
                    cin.clear();  // clear input buffer to restore cin to a usable state
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // ignore last input
                    cout << "\033[31m";
                    
                    if (cin.fail())
                    {
                        cerr << "Invalid input. Please enter a positive numeric value for Overtime Rate.\033[0m" << endl;
                    }
                    else
                    {
                        cerr << "Invalid input. Please enter a positive numeric value for Regular Rate.\033[0m" << endl;
                    }

                    cout << "Enter Department Regular Rate: ";
                }

                cout << "Enter Department Overtime Rate: ";
                while (!(cin >> newDept.ovrRate) || cin.fail() || newDept.ovrRate < 0.0)
                {
                    cin.clear();  // clear input buffer to restore cin to a usable state
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // ignore last input
                    cout << "\033[31m";
                    
                    if (cin.fail())
                    {
                        cerr << "Invalid input. Please enter a positive numeric value for Overtime Rate.\033[0m" << endl;
                    }
                    else
                    {
                        cerr << "Invalid input. Please enter a positive numeric value for Overtime Rate.\033[0m" << endl;
                    }

                    cout << "Enter Department Overtime Rate: ";
                }
  
                cout << "\033[32m" << "Record added successfully" << "\033[0m" << endl;
                file << newDept.getCode() << "\t" << newDept.getDeptName() << "\t" << newDept.getRegRate() << "\t" << newDept.getovrRate() << endl;
                file.close();
                
            }

            void viewAll()
            {
                ifstream file("Department.txt");
                if (!file.is_open())
                {
                    cout << "\033[31m";
                    cerr << "Error opening file.\033[0m" << endl;
                    return;
                }
                
                Dept data;
                bool recordsExist = false; 

                cout << left << setw(5) << "Code" << setw(20) << "Name" << setw(15) << "Regular Rate" << setw(15) << "Overtime Rate" << endl;
                while (file >> data.code)
                {
                    file.ignore(); // Ignore the tab character after reading code
                    getline(file, data.deptName, '\t'); // Read the department name until the next tab character

                    file >> data.regRate >> data.ovrRate;

                    cout << left << setw(5) << data.getCode() << setw(20) << data.getDeptName() << setw(15) << data.getRegRate() << setw(15) << data.getovrRate() << endl;

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

            void viewNames()
            {
                ifstream file("Department.txt");
                if (!file.is_open())
                {
                    cout << "\033[31m";
                    cerr << "Error opening file.\033[0m" << endl;
                    return;
                }

                Dept data;
                while (file >> data.code)
                {
                    file.ignore(); // Ignore the tab character after reading code
                    getline(file, data.deptName, '\t'); // Read the department name until the next tab character

                    file >> data.regRate >> data.ovrRate;

                    cout << data.getCode() << " - " << data.getDeptName() << endl;
                }
                file.close();
            }

            void viewRecord(int specific)
            {
                ifstream file("Department.txt");
                if (!file.is_open())
                {
                    cout << "\033[31m";
                    cerr << "Error opening file. \033[0m" << endl;
                    return;
                }

                Dept data;
                bool found = false;
                cout << left << setw(5) << "Code" << setw(20) << "Name" << setw(15) << "Regular Rate" << setw(15) << "Overtime Rate" << endl;
                while (file >> data.code)
                {
                    file.ignore(); // Ignore the tab character after reading code
                    getline(file, data.deptName, '\t'); // Read the department name until the next tab character
                    file >> data.regRate >> data.ovrRate;

                    if (data.getCode() == specific)
                    {
                        found = true;
                        cout << left << setw(5) << data.getCode() << setw(20) << data.getDeptName() << setw(15) << data.getRegRate() << setw(15) << data.getovrRate() << endl;
                        break;
                    }
                }

                if (!found)
                {
                    cout << "\033[31m";
                    cout << "Department record with code " << specific << " not found.\033[0m" << endl;
                }

                file.close();
            }


            void updateRecord()
            {
                ifstream updateFile("Department.txt");
                if (!updateFile.is_open())
                {
                    cout << "\033[31m";
                    cerr << "Error opening file.\033[0m" << endl;
                    return;
                }

                ofstream tempFile("temp.txt");
                if (!tempFile.is_open())
                {
                    cout << "\033[31m";
                    cerr << "Error opening the temporary file created.\033[0m" << endl;
                    return;
                }

                Dept data;
                bool found = false;
                int updateCode;
                data.viewNames();
                cout << "Enter Department Code to update: ";
                cin >> updateCode;

                while (updateFile >> data.code)
                {
                    updateFile.ignore(); // Ignore the tab character after reading code
                    getline(updateFile, data.deptName, '\t'); // Read the department name until the next tab character
                    updateFile >> data.regRate >> data.ovrRate;

                    if (data.getCode() == updateCode)
                    {
                        found = true;
                        int updateChoice;

                        while (true)
                        {
                            cout << "Select aspect to update:" << endl;
                            cout << "1. Department Code" << endl;
                            cout << "2. Department Name" << endl;
                            cout << "3. Department Regular Rate" << endl;
                            cout << "4. Department Overtime Rate" << endl;
                            cout << "Enter your choice: ";

                            if (!(cin >> updateChoice) || cin.fail() || updateChoice < 1 || updateChoice > 4)
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << "\033[31m";
                                cerr << "Invalid input. Please enter a number between 1 and 4.\033[0m" << endl;
                                continue;
                            }

                            break;
                        }

                        switch (updateChoice)
                        {
                        case 1:
                            cout << "Enter new Department Code: ";
                            if (!(cin >> data.code) || cin.fail() || data.code < 0)
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << "\033[31m";
                                cerr << "Invalid input. Department Code should be a positive integer.\033[0m" << endl;
                                break;
                            }
                            break;
                        case 2:
                            cin.ignore();
                            cout << "Enter new Department Name: ";
                            getline(cin, data.deptName);
                            while (data.deptName.empty())
                            {
                                cout << "\033[31m";
                                cerr << "The department requires a name.\033[0m" << endl;
                                cout << "Enter new Department Name: ";
                                getline(cin, data.deptName);
                            }
                            break;
                        case 3:
                            cout << "Enter new Department Regular Rate: ";
                            while (!(cin >> data.regRate) || cin.fail() || data.regRate < 0.0)
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << "\033[31m";
                                cerr << "Invalid input. Please enter a positive numeric value for Regular Rate.\033[0m" << endl;
                                cout << "Enter new Department Regular Rate: ";
                            }
                            break;
                        case 4:
                            cout << "Enter new Department Overtime Rate: ";
                            while (!(cin >> data.ovrRate) || cin.fail() || data.ovrRate < 0.0)
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << "\033[31m";
                                cerr << "Invalid input. Overtime Rate cannot be negative.\033[0m" << endl;
                                cout << "Enter new Department Overtime Rate: ";
                            }
                            break;
                        }
                    }

                    tempFile << data.getCode() << "\t" << data.getDeptName() << "\t" << data.getRegRate() << "\t" << data.getovrRate() << endl;
                }

                updateFile.close();
                tempFile.close();

                if (!found)
                {
                    cout << "\033[31m";
                    cerr << "Department record with code " << updateCode << " was not found.\033[0m" << endl;
                    remove("temp.txt");
                }
                else
                {
                    remove("Department.txt");
                    rename("temp.txt", "Department.txt");
                    cout << "\033[32m" << "Record updated successfully" << "\033[0m" << endl;
                }
            }


            bool codeExists(int codeToCheck)
            {
                ifstream file("Department.txt");
                if (!file.is_open())
                {
                    cout << "\033[31m";
                    cerr << "Error opening file.\033[0m" << endl;
                    return false;
                }

                Dept data;
                while (file >> data.code)
                {
                    file.ignore();
                    getline(file, data.deptName, '\t');

                    file >> data.regRate >> data.ovrRate;

                    if (data.getCode() == codeToCheck)
                    {
                        file.close();
                        return true;
                    }
                }

                file.close();
                return false;
            }

            void setDeptCode(int code) {
                this->code = code;
            }

            string readDeptNameFromFile(int specific)
            {
                ifstream file("Department.txt");
                if (!file.is_open())
                {
                    cout << "\033[31m";
                    cerr << "Error opening file.\033[0m" << endl;
                    return "Error opening file";
                }

                Dept data;
                string temp;
                while (file >> data.code)
                {
                    file.ignore(); // Ignore the tab character after reading code
                    getline(file, data.deptName, '\t'); // Read the department name until the next tab character
                    file >> data.regRate >> data.ovrRate;

                    if (data.getCode() == specific)
                    {
                        temp = data.getDeptName();
                        break;
                    }
                }
                file.close();
                return temp;
            }


            double readRegRateFromFile(int specific)
            {
                ifstream file("Department.txt");
                if (!file.is_open())
                {
                    cout << "\033[31m";
                    cerr << "Error opening file.\033[0m" << endl;
                    return -1; // Assuming a default value if not found
                }

                Dept data;
                double temp = -1; // Assuming a default value if not found
                while (file >> data.code)
                {
                    file.ignore(); // Ignore the tab character after reading code
                    getline(file, data.deptName, '\t'); // Read the department name until the next tab character
                    file >> data.regRate >> data.ovrRate;

                    if (data.getCode() == specific)
                    {
                        temp = data.getRegRate();
                        break;
                    }
                }
                file.close();
                return temp;
            }


            double readOvrRateFromFile(int specific)
            {
                ifstream file("Department.txt");
                if (!file.is_open())
                {
                    cout << "\033[31m";
                    cerr << "Error opening file.\033[0m" << endl;
                    return -1; // Assuming a default value if not found
                }

                Dept data;
                double temp = -1; // Assuming a default value if not found
                while (file >> data.code)
                {
                    file.ignore(); // Ignore the tab character after reading code
                    getline(file, data.deptName, '\t'); // Read the department name until the next tab character
                    file >> data.regRate >> data.ovrRate;

                    if (data.getCode() == specific)
                    {
                        temp = data.getovrRate();
                        break;
                    }
                }
                file.close();
                return temp;
            }
    };
#endif