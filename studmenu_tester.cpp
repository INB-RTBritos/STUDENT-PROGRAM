#include <iostream>
#include <cctype>
#include <string>
#include "src\StudentMenu.h"

using namespace std;

int main()
{
    StudentDetails sNode;
    string firstName, lastName, middleName, degreeProgram, studentGender, studentAddress, birthMonthName, fullBirthday;
    int idNumber, yearLevel, choice, counter = 0, birthDay, birthYear, birthMonthNum, idToView, idToEdit, idToDelete, sortChoice;
    sNode.FetchStudentInfo();

    while (true)
    {
        cout << "1. Add Student" << endl;
        cout << "2. View Student List" << endl;
        cout << "3. View Student's Record" << endl;
        cout << "4. Edit Student Info" << endl;
        cout << "5. Delete Student" << endl
             << endl;
        cout << "0. Exit" << endl;
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 0:
        {
            return 0;
        }
        case 1:
        {
            while (true)
            {
                cout << "Enter First Name: ";
                getline(cin, firstName);

                if (sNode.IsValidName(firstName))
                    break;
            }

            while (true)
            {
                cout << "Enter Middle Name: ";
                getline(cin, middleName);

                if (sNode.IsValidName(middleName))
                    break;
            }

            while (true)
            {
                cout << "Enter Last Name: ";
                getline(cin, lastName);

                if (sNode.IsValidName(lastName))
                    break;
            }

            cout << "Enter Birth Month: ";
            cin >> birthMonthName;
            while (!sNode.IsValidBirthMonth(birthMonthName))
            {
                cout << "Invalid Month! Please enter a valid birth month." << endl;
                cout << "Enter Birth Month: ";
                cin >> birthMonthName;
            }

            cout << "Enter Birth Day: ";
            cin >> birthDay;

            cout << "Enter Birth Year: ";
            cin >> birthYear;
            while (!sNode.IsValidBirthDate(birthDay, birthMonthName, birthYear))
            {
                cout << "Invalid Birth Date! Please enter a valid Birth Date." << endl;
                cout << "Enter Birth Month: ";
                cin >> birthMonthName;
                cout << "Enter Birth Day: ";
                cin >> birthDay;
                cout << "Enter Birth Year: ";
                cin >> birthYear;
            }

            while (true)
            {
                cout << "Enter Gender (Male or Female): ";
                cin >> studentGender;
                cin.ignore();

                if (sNode.IsValidGender(studentGender))
                    break;
            }

            while (true)
            {
                cout << "Enter City Address (ex. Manila City): ";
                getline(cin, studentAddress);

                if (sNode.IsValidName(studentAddress))
                    break;
            }

            while (true)
            {
                cout << "Enter ID Number (9-digit ID Number): ";
                cin >> idNumber;

                if (sNode.IsValidStudentNum(idNumber))
                    break;
            }

            while (true)
            {
                cout << "Enter Degree Program (ex. BSITCST): ";
                cin >> degreeProgram;

                if (sNode.IsValidName(degreeProgram))
                    break;
            }

            while (true)
            {
                cout << "Enter Year Level (1-4): ";
                cin >> yearLevel;
                cin.ignore();

                if (yearLevel >= 1 && yearLevel <= 4)
                    break;
                else
                    cout << "Enter a Valid Year Level." << endl;
            }

            birthMonthNum = sNode.MonthNameToNumber(birthMonthName); // Convert month name to number(int)
            fullBirthday = to_string(birthMonthNum) + "/" + to_string(birthDay) + "/" + to_string(birthYear); // Convert into the full birthday format (string)
            // Insert he new value to the tree
            sNode.AddStudent(firstName, lastName, middleName, degreeProgram, studentGender, studentAddress, fullBirthday, idNumber, yearLevel);
            break;
        }
        case 2:
        {
            sNode.ViewStudents();
            break;
        }
        case 3:
        {
            sNode.ViewStudents();
            cout << endl;

            while (true) // to edit
            {
                cout << "Enter Student Number to View: ";
                cin >> idToView;

                if (sNode.IsValidStudentNum(idToView))
                    break;
            }
            
            sNode.ViewDetails(to_string(idToView));

            break;
        }
        case 4:
        {
            sNode.ViewStudents();
            cout << endl;

            while (true) // to edit
            {
                cout << "Enter Student Number to Edit: ";
                cin >> idToEdit;

                if (sNode.IsValidStudentNum(idToEdit))
                    break;
            }

            sNode.EditStudent(to_string(idToEdit));
            
            cout << endl << "Successfully Edited" << endl << endl;

            break;
        }
        case 5:
        {
            sNode.ViewStudents();
            cout << endl;

            while (true) // to edit
            {
                cout << "Enter Student Number to Delete: ";
                cin >> idToDelete;

                if (sNode.IsValidStudentNum(idToDelete))    
                    break;
            }

            sNode.DeleteStudent(to_string(idToDelete));
            
            cout << endl << "Successfully Deleted" << endl << endl;

            break;
        } 
        }
    }
}