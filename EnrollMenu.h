#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <cctype>
#include "CourseCode.h"

using namespace std;


class EnrollMenu
{
private:
    string studentID, studentName, courseCode, courseTitle, courseUnits, courseYearLevel, courseSchedule, blockSection;

public:
    void Pause();
    int EnrollmentMenu();
    int EnrollFunctionalities();

    // Validation Functions
    bool isEnrolled(string, string, string, string);
    bool isExisting(string);
    bool blockSectionExists(string);
    bool courseCodeExists(string);
    bool scheduleExists(string);
    // Function Prototypes
    void EnrollStudent(string);
    void ViewEnrollees();
    int ViewSchedules(string, int);
};

void EnrollMenu::Pause() // Function to replace "system("pause")"
{
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get(); // Wait for the user to press Enter
}

int EnrollMenu::EnrollmentMenu() {
    // Enrollment Menu Functions
    int choice;
    do {
        HeaderDesign();
        cout << "-- Enrollment Menu --\n\n";
        cout << "[1] Enroll Students\n";
        cout << "[2] View Enrollee\n";
        cout << "[0] Return To Main Menu\n\n";
        cout << ":: ";
        cin >> choice;
        cin.ignore();
    } while (choice < 0 || choice > 2);
    system("clear");
    return choice;
}

int EnrollMenu::EnrollFunctionalities() {
    string studentID;
    // Continuation of Menu Functions
    while (true) {
        switch (EnrollmentMenu()) {
            case 1:
            while (true){
                system("clear");
            HeaderDesign();
            cout << "Enter student ID: ";
            cin >> studentID;
            if (isExisting(studentID)){ // checking if the student id is already added in the student management menu.
            EnrollStudent(studentID); // proceeding to enroll the student
            }
            }
            break;
            case 2:
            system("clear");
            ViewEnrollees(); // Proceed to View Enrollees function
            break;
            case 0:
            return 0;
            break;
            default:
            return 0;
            break;
        }
    }
    return 0;
}

int EnrollMenu::ViewSchedules(string courseCode, int identifier) {
    string schedFile;
    ifstream ifile;
    string scheduleData[7];
    ifstream schedIfile("output/Schedules/SCHEDULES.txt"); // to open the schedule file which contains the schedules per each course
    if (schedIfile.is_open()) {
        string line;
        HeaderDesign();
        while (getline(schedIfile, line)) { // while loop to traverse the schedule file
            if(line.find(courseCode) != string::npos) { // finding the line which has the course code so that it only shows the coursecode entered by the user
            schedFile = "output/Schedules/" + line + ".txt";
            ifile.open(schedFile);
            if (ifile.is_open()) {
                for (int i = 0; i < 7; i++) {
                    getline(ifile, scheduleData[i]);
                    identifier++;
                }
                ifile.close();
                cout <<"|" <<"----------------------------------------------------------------------------------------------------------------------"<< "|\n";
                cout << "|" << setw(11) << scheduleData[0] << " | " << setw(10) << scheduleData[1] << " | " << setw(5) << scheduleData[2] << " | " << setw(10) << scheduleData[3] << " | " << setw(10) << scheduleData[4] << " | " << setw(10) << scheduleData[5] << " | " << setw(10) << scheduleData[6] << " |\n";
                cout <<"|" <<"----------------------------------------------------------------------------------------------------------------------"<< "|\n";
            } else {
                cout << "Failed to open file: " << schedFile << endl;
            }
            }
        }
        schedIfile.close();
        return identifier; // return identifier so that the enroll student can proceed outside the while loop
    } else {
        cout << "Failed to open SCHEDULES.txt file." << endl;
        return identifier;
    }
}

bool EnrollMenu::courseCodeExists(string courseCode) {
    ifstream file("output/CourseRecords/recordlist.txt"); // finds if the courseCode line exists
    string line;
    while (getline(file, line)) {
        if (line.find(courseCode) != string::npos) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}


bool EnrollMenu::scheduleExists(string courseSchedule)
{
    ifstream file("output/Schedules/SCHEDULES.txt"); // finds if the courseSchedule line exists
    string line;
    while (getline(file, line))
    {
        if (line.find(courseSchedule) != string::npos)
        {
            file.close();
            return true;
        }
        else{
            file.close();
            return false;
        }
    }
    file.close();
    return false;
}

bool EnrollMenu::blockSectionExists(string blockSection) // finds if the blockSectionExists
{
    ifstream file("output/Schedules/SCHEDULES.txt");
    string line;
    while (getline(file, line))
    {
            if (line.find(blockSection) != string::npos)
        {
            file.close();
            return true;
        }
        else{
            file.close();
            return false;
        }
    }
    file.close();
    return false;
}

bool EnrollMenu::isExisting(string studentID)
{
    ifstream file("output/Students/idlist.txt");
    string line;
    while (getline(file, line))
    {
        if (line.find(studentID) != string::npos)
        {
            file.close();
            return true;
        }
    }
    file.close();
    cout << "Student ID not found.\n";
    return false;
}

bool EnrollMenu::isEnrolled(string studentID, string courseCode, string courseSchedule, string blockSection)
{
    ifstream file("output/Students/Enrolled Courses" + blockSection + "-" + courseCode + "-" + courseSchedule + "list.txt");
    string line;
    while (getline(file, line))
    {
        if (line.find(studentID) != string::npos)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void EnrollMenu::EnrollStudent(string studentID)
{
    BinaryTree tree;
    LoadCourses(tree); // used from coursecode.h to load the courses into a binary tree
    int sure = 0, identifier = 0;
    string line;
    string courseCode, courseSchedule, blockSection, studentFirstName, studentLastName, studentMiddlename;
    if (isEnrolled(studentID, blockSection, courseCode, courseSchedule))
    {
        cout << "Student is already enrolled in the course.\n";
        return;
    }
    do
    {
        do // to make sure if you really want to enroll in the course the user inputted. if not it will loop so that you can enter another course code
        {
            do // course code validation
            {
                system("clear");
                tree.ViewCourses(); // viewing the tree which contains the courses
                cout << "Enter course code: ";
                cin >> courseCode;
                if (courseCodeExists(courseCode) == false)
                {
                    cout << "Course not found.\n";
                    Pause();
                }
            } while (courseCodeExists(courseCode) == false);
            cout << "Are you sure you want to enroll in this course? (1 for yes, 0 for no): ";
            cin >> sure;
        } while (sure == 0);
        system("clear");
        identifier = ViewSchedules(courseCode, identifier);
        if (identifier == 0) {
            char choices;
            do {
            cout << "No schedules found, Press Y to return to main menu, press N to enter another course code.";
            cin >> choices;
            if (choices == 'Y' || choices == 'y'){
                return;
            }
            else if (choices == 'N' || choices == 'n')
            {
                continue;
            }
            else{
                cout << "Invalid Input, please enter right input.";
            }
            } while (choices != 'Y' || choices != 'y' || choices == 'N' || choices == 'n');
        }
    } while (identifier == 0);
    do
    {
        cout << "\nEnter block section: ";
        cin >> blockSection;
        if (blockSectionExists(blockSection) == false)
        {
            cout << "Block section not found, Please try again.\n";
        }
    } while (blockSectionExists(blockSection) == false);
    do
    {
        cout << "\nEnter course schedule: ";
        cin >> courseSchedule;
        if (scheduleExists(courseSchedule) == false)
        {
            cout << "Schedule not found, Please try again.\n";
        }
    } while (scheduleExists(courseSchedule) == false);

    ifstream studfile("output/Students/" + studentID + ".txt");
    if (studfile.is_open())
    {
        getline(studfile, studentID); // Read the student ID
        getline(studfile, studentFirstName);
        getline(studfile, studentLastName);
        getline(studfile, studentMiddlename);
        studfile.close();
    }
    else
    {
        cerr << "Unable to open file for reading.\n";
    }
    ofstream file("output/Students/Enrolled Courses/" + blockSection + "_" + courseCode + "_" + courseSchedule + "_LIST.txt", ios::app);
    if (file.is_open())
    {
        file << studentID << "-" << studentLastName << "-" << studentFirstName << "-" << studentMiddlename << "\n";
        file.close();
    }
    else
    {
        cout << "Unable to open file for writing.\n";
        return;
    }
    cout << "Student enrolled successfully.\n";
    return;
}

void EnrollMenu::ViewEnrollees()
{
    BinaryTree tree;
    string courseCode, courseSchedule, blockSection;
    int identifier;
    string studentID, studentFirstName, studentLastName, studentMiddlename;
    HeaderDesign();
    LoadCourses(tree);
    do // course code validation
    {
        system("clear");
        tree.ViewCourses();
        cout << "Enter course code: ";
        cin >> courseCode;
        if (courseCodeExists(courseCode) == false)
        {
            cout << "Course not found.\n";
        }
    } while (courseCodeExists(courseCode) == false);
    system("clear");
    HeaderDesign();
    ViewSchedules(courseCode, identifier);
    do // block section validation
    {
        cout << "Enter block section: ";
        cin >> blockSection;
        if (blockSectionExists(blockSection) == false)
        {
            cout << "\nBlock section not found, Please try again.\n";
        }
    } while (blockSectionExists(blockSection) == false);
    do // schedule validation
    {
        cout << "\nEnter course schedule: ";
        cin >> courseSchedule;
        if (scheduleExists(courseSchedule) == false)
        {
            cout << "\nSchedule not found, Please try again.\n";
        }
    } while (scheduleExists(courseSchedule) == false);
    ifstream file("output/Students/Enrolled Courses/" + blockSection + "_" + courseCode + "_" + courseSchedule + "_LIST.txt");
    string line;
    if (!file.is_open())
    {
        cout << "File is not existing.\n";
        return;
    }
    system("clear");
    HeaderDesign();
    cout << "\nEnrolled Students in " << courseCode << " " << blockSection << " " << courseSchedule << ":\n";
    cout << "===========================================================================================\n";
    while (getline(file, line)) // to add student details into temp variable so that you can display the student information
    {
        studentID = line.substr(0, line.find("-"));
        line.erase(0, line.find("-") + 1);
        studentLastName = line.substr(0, line.find("-"));
        line.erase(0, line.find("-") + 1);
        studentFirstName = line.substr(0, line.find("-"));
        line.erase(0, line.find("-") + 1);
        studentMiddlename = line;
        cout << studentID << " " << studentLastName << ", " << studentFirstName << " " << studentMiddlename << "\n";
    }
    cout << "===========================================================================================\n";
    file.close();
    Pause();
    system("clear");
}
