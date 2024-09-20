#include <iostream>
#include <unistd.h>
#include <stdexcept>
#include "Dept.h"
#include "Employee.h"
#include "Payroll.h"
using namespace std;

int main()
{
    int menu = 5;
    int option = 5;
    while (menu!=4)
    {
        cout << "\033[1;34m";
        cout << "SSN Payment Management System\033[0m" << endl;
        sleep(2);
        cout << "Please select an option: " << endl;
        cout << "1. Department Rates \n2. Employee \n3. Employee Payroll \n4: Cancel"<<endl;
        while (!(cin >> menu) || cin.fail())
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
                cerr << "Invalid Input.  Please enter an integer.\033[0m" << endl;
            }
            sleep(2);
            cout << "Please select an option: " << endl;
            cout << "1. Department Rates \n2. Employee \n3. Employee Payroll \n4: Cancel"<<endl;
        }
        system("cls");


        if (menu == 1)//Employee request Department Rate
        {
            do
            {
                try {
                    cout << "\033[1;34m";
                    cout << "SSN Payment Management System \nDepartment Rates\033[0m" << endl;
                    cout << "Select One: \n1. View Specific Record \n2. View All Records \n3. Update Record \n4. Add Record \n5. Main Menu \n6. Close\n" << endl;
                    while (!(cin >> option) || cin.fail())
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
                            cerr << "Invalid Input.  Please enter an integer.\033[0m" << endl;
                        }
                        sleep(2);
                        cout << "Select One: \n1. View Specific Record \n2. View All Records \n3. Update Record \n4. Add Record \n5. Main Menu \n6. Close\n"<<endl;
                    }
                    system("cls");

                    if (option!=1 && option!=2 && option != 3 && option!=4 && option!=5 && option!=6)
                    {
                        cout << "\033[31m";
                        throw invalid_argument("\aInvalid Input. Please try again by entering number provided. \033[0m"); //Ensure that number entered is valid
                    }

                    Dept department;
                    if (option == 1)
                    {
                        cout << "Current departments" << endl;
                        department.viewNames();
                        cout << endl;
                        int view;
                        cout << "Enter the Department Code to view: ";
                        cin >> view;
                        system("cls");
                        department.viewRecord(view);
                        sleep(4);

                    }
                    else if (option == 2)
                    {
                        system("cls");
                        department.viewAll();
                        sleep(8);
                    }
                    else if (option == 3)
                    {
                        department.updateRecord();
                        sleep(1);
                    }
                    else if (option == 4)
                    {
                        department.addRecord();
                        sleep(1);
                    }
                    else if (option == 6)
                    {
                        return 0;
                    }

                    cout << "\n";
                }
                catch (const invalid_argument& e)
                {
                    cerr << "Error: " << e.what() << endl;
                }

                system("cls");

            }while (option!=5);
            continue;
        }
        
        else if (menu == 2)//Employee
        {
            do
            {
                try {
                    cout << "\033[1;34m";
                    cout << "SSN Payment Management System \nEmployee Rates\033[0m" << endl;
                    cout << "Select One: \n1. View Specific Record \n2. View All Records \n3. Update Record \n4. Add Record \n5. Main Menu \n6. Delete Specific Record \n7. Close\n" << endl;
                    while (!(cin >> option) || cin.fail())
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
                            cerr << "Invalid Input.  Please enter an integer.\033[0m" << endl;
                        }
                        sleep(2);
                        cout << "Select One: \n1. View Specific Record \n2. View All Records \n3. Update Record \n4. Add Record \n5. Main Menu \n6. Delete Specific Record \n7. Close\n" << endl;
                    }
                    system("cls");

                    if (option!=1 && option!=2 && option != 3 && option!=4 && option!=5 && option!=6 && option!=7)
                    {
                        cout << "\033[31m";
                        throw invalid_argument("\aInvalid Input. Please try again by entering number provided. \033[0m"); //Ensure that number entered is valid
                    }

                    Employee emp;
                    if (option == 1)
                    {
                        int view;
                        emp.viewNames();
                        cout << "Enter the ID number of the Employee to view: ";
                        cin >> view;
                        system("cls");
                        emp.viewRecord(view);
                        sleep(2);
                    }
                    else if (option == 2)
                    {
                        system("cls");
                        emp.viewAll();
                        sleep(4);
                    }

                    else if (option == 3)
                    {
                        int code;
                        emp.viewNames();
                        cout << "Enter ID number of Employee record to update: " << endl;
                        cin >> code;
                        system("cls");
                        emp.updateRecord(code);
                        sleep(1);
                    }

                    else if (option == 4)
                    {
                        emp.addRecord();
                        sleep(1);
                    }

                    else if (option == 6)
                    {
                        int del;
                        emp.viewNames();
                        cout << "Enter the ID number of the Employee to delete: ";
                        cin >> del;
                        system("cls");
                        emp.deleteEmp(del);
                        sleep (1);
                    }

                    else if (option == 7)
                    {
                        return 0;
                    }
                    cout << "\n";
                }
                catch (const invalid_argument& e)
                {
                    cerr << "Error: " << e.what() << endl;
                }
            }while (option!=5);
            continue;
        }

        else if (menu == 3)//Payroll
        {
            do
            {
                try {
                    cout << "\033[1;34m";
                    cout << "SSN Payment Management System \nPayroll\033[0m" << endl;
                    cout << "Select One: \n1. Process Payroll \n2. View Payroll \n3. View Department Payroll \n4. Close \n5. Main Menu" << endl;
                    while (!(cin >> option) || cin.fail())
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
                            cerr << "Invalid Input.  Please enter an integer.\033[0m" << endl;
                        }
                        sleep(2);
                        cout << "Select One: \n1. Process Payroll \n2. View Payroll \n3. View Department Payroll \n4. Close \n5. Main Menu" << endl;
                    }
                    system("cls");

                    Payroll payroll;
                    if (option == 1)
                    {
                        system("cls");
                        payroll.addRecord();
                        sleep(1);
                    }
                    else if (option == 2)
                    {
                        int id;
                        Employee emp;
                        emp.viewNames();
                        cout << "Enter id number: ";
                        cin >> id;
                        system("cls");
                        payroll.viewRecord(id);
                        sleep(2);
                    }

                    else if (option == 3)
                    {
                        int code;
                        system("cls");
                        Dept view;
                        cout << "Enter Department code to view: " << endl;
                        view.viewNames();
                        cout << endl;
                        cout << "Code: ";
                        cin >> code;
                        system("cls");
                        payroll.viewDept(code);
                        sleep(7);
                    }

                    else if (option == 4)
                    {
                        return 0;
                    }
                    
                }
                catch (const invalid_argument& e)
                {
                    cerr << "Error: " << e.what() << endl;
                }
            }while (option!=5);
            continue;
        }
    }
    cout<< "\033[1;34m";
    cout << "Thank you!\033[0m" << endl;
    return 0;
}
