#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <iomanip>
#include "CourseMenu.h"
using namespace std;

class Schedule {
    private:
    struct SchedNode {
        int numUnits, yearLevel;
        string courseTitle, courseCode, section, weekDay, startTime, endTime, roomNumber, time;
        int schedHour, schedMinute, schedSecond;
        double amountMinute;

        SchedNode *left;
        SchedNode *right;
    } *holder, *current;

    public:
    SchedNode *root;
    Schedule();
    int ScheduleMenu();
    int EditMenu();
    void AddScheduleData();
    void AddScheduleRecord(string, string, string, string, string, int, int, int, int, int, double);
    void TimeFormat();
    void ViewSchedule();
    void EditSchedule();
    void DeleteSchedule();
    void UpperString(string&);
    void LoadFiles();
    void AddFileNameRecord();
};

Schedule::Schedule() {
    root = NULL;
    LoadFiles();
}

int Schedule::ScheduleMenu() {
    int choice;

    do {
        cout << "-- Schedule Management --\n\n";
        cout << "[1] Add a Schedule\n";
        cout << "[2] View Schedules\n";
        cout << "[3] Edit a Schedule\n";
        cout << "[4] Delete a Schedule\n";
        cout << "[0] Return to Main Menu\n";
        cout << ":: ";
        cin >> choice;
        cin.ignore();
    } while (choice < 0 || choice > 4);
    return choice;
}

int Schedule::EditMenu() {
    int choice;
    do {
        cout << "\n\n-- Edit Schedule Menu --\n\n";
        cout << "[1] Edit Day\n";
        cout << "[2] Edit Time\n";
        cout << "[3] Edit Section\n";
        cout << "[4] Edit Room\n";
        cout << "[0] Return to Schedule Menu\n";
        cout << ":: ";
        cin >> choice;
        cin.ignore();
    } while (choice < 0 || choice > 4);
    return choice;
}

void Schedule::AddScheduleData() {
    int schedHour, schedMinute, schedSecond, amountMinute, numUnits, yearLevel;
    string courseTitle, courseCode, section, weekDay, roomNumber;

    cout << "Enter Course Code: ";
    getline(cin, courseCode);
    cout << "Enter Course Name: ";
    getline(cin, courseTitle);
    cout << "Enter Section for the Course: ";
    getline(cin, section);
    cout << "Enter Day the Course to be scheduled for: ";
    getline(cin, weekDay);
    cout << "Enter Room Number: ";
    getline(cin, roomNumber);
    cout << "Enter Number of Units: ";
    cin >> numUnits;
    cin.ignore();
    cout << "Enter Year Level: ";
    cin >> yearLevel;
    cin.ignore();
    cout << "Enter Start Hour of the schedule: ";
    cin >> schedHour;
    cin.ignore();
    cout << "Enter Start Minute of the schedule: ";
    cin >> schedMinute;
    cin.ignore();
    cout << "Enter Start Second of the schedule: ";
    cin >> schedSecond;
    cin.ignore();
    cout << "Enter Amount of Minute for the Course: ";
    cin >> amountMinute;
    cin.ignore();

    UpperString(courseCode);
    UpperString(courseTitle);
    UpperString(section);
    UpperString(roomNumber);
    UpperString(weekDay);

    AddScheduleRecord(courseTitle, section, weekDay, courseCode, roomNumber, numUnits, yearLevel, schedHour, schedMinute, schedSecond, amountMinute);
}

void Schedule::AddScheduleRecord(string courseName, string block, string day, string courseId, string rNumber, int units, int yLevel, int sHour, int sMin, int sSec, double amountMinute) {
    string schedFile, time, sectionChecker; 
    SchedNode* parent = NULL;
    holder = new SchedNode;
    holder -> courseTitle = courseName;
    holder -> section = block;
    holder -> weekDay = day;
    holder -> courseCode = courseId;
    holder -> numUnits = units;
    holder -> yearLevel = yLevel;
    holder -> roomNumber = rNumber;
    holder -> schedHour = sHour;
    holder -> schedMinute = sMin;
    holder -> schedSecond = sSec;
    holder -> amountMinute = amountMinute;
    holder->left = NULL;
    holder->right = NULL;

    schedFile = "Schedules\\" + holder->section + "_" + holder->courseCode + "_" + holder->weekDay + ".txt";
    ifstream ifile(schedFile);
    if (ifile.is_open()) {
        cout << "Schedule Already Exists!\n";
        ifile.close();
        return;
    }
            
    if (root == NULL) {
        root = holder;
        cout << "Schedule successfully added!\n";
    }

    else {
        current = root;
        while (current != NULL) {
            parent = current;
            if (block < current->section || day < current->weekDay || courseId < current->courseCode) {
                current = current->left;
            }
            else if (block > current->section || day > current -> weekDay || courseId > current->courseCode) {
                current = current->right;
            }
            else {
                cout << "Schedule Already Exists!\n";
                return;
            }
        }
        if (block < parent->section) {
            parent->left = holder;
        }
        else {
            parent->right = holder;
        }
        cout << "Schedule successfully added!\n";
        AddFileNameRecord();
    }

    TimeFormat();
    ofstream ofile(schedFile);
    ofile << holder->courseCode << "\n";
    ofile << holder->courseTitle << "\n";
    ofile << holder->section << "\n";
    ofile << holder->numUnits << "\n";
    ofile << holder->weekDay << "\n";
    ofile << holder->startTime << " - " << holder->endTime << "\n";
    ofile << holder->roomNumber << "\n";
    ofile.close();

}

void Schedule::ViewSchedule() {
    string schedFile;
    ifstream ifile;
    string scheduleData[7];

    ifstream schedIfile("Schedules\\SCHEDULES.txt");
    if (schedIfile.is_open()) {
        string line;
        while (getline(schedIfile, line)) {
            schedFile = "Schedules\\" + line + ".txt";
            ifile.open(schedFile);
            if (ifile.is_open()) {
                for (int i = 0; i < 7; i++) {
                    getline(ifile, scheduleData[i]);
                }
                ifile.close();
                cout <<"|" <<"----------------------------------------------------------------------------------------------------------------------"<< "|\n";
                cout << "|" << setw(11) << scheduleData[0] << " | " << setw(10) << scheduleData[1] << " | " << setw(5) << scheduleData[2] << " | " << setw(10) << scheduleData[3] << " | " << setw(10) << scheduleData[4] << " | " << setw(10) << scheduleData[5] << " | " << setw(10) << scheduleData[6] << " |\n";
                cout <<"|" <<"----------------------------------------------------------------------------------------------------------------------"<< "|\n";
            } else {
                cout << "Failed to open file: " << schedFile << endl;
            }
        }
        schedIfile.close();
    } else {
        cout << "Failed to open SCHEDULES.txt file." << endl;
    }
}

void Schedule::EditSchedule() {
    string section, courseCode, weekDay, schedFile, newSchedFile, newDay, newSection, newRoom;
    int schedHour, schedMinute, schedSecond, amountMinute;

    cout << "Enter Section: ";
    getline(cin, section);
    cout << "Enter Course Code: ";
    getline(cin, courseCode);
    cout << "Enter Day: ";
    getline(cin, weekDay);

    UpperString(section);
    UpperString(courseCode);
    UpperString(weekDay);

    schedFile = "Schedules\\" + section + "_" + courseCode + "_" + weekDay + ".txt";

    ifstream ifile(schedFile);
    if (ifile.is_open()) {
        ifile.close();

        SchedNode* temp = root;
        while (temp != NULL) {
            if (temp->section == section && temp->courseCode == courseCode && temp->weekDay == weekDay) {
                break;
            } else if (temp->section < section || temp->weekDay < weekDay || temp->courseCode < courseCode) {
                temp = temp->right;
            } else {
                temp = temp->left;
            }
        }

        if (temp == NULL) {
            cout << "Schedule not found!\n";
            return;
        }

        
        while (true) {        
            switch (EditMenu()) {
                case 1: {
                    cout << "Enter new Day: ";
                    getline(cin, newDay);
                    UpperString(newDay);
                    holder->weekDay = newDay;
                    newSchedFile = "Schedules\\" + holder->section + "_" + holder->courseCode + "_" + holder->weekDay + ".txt";
                    rename(schedFile.c_str(), newSchedFile.c_str());
                    schedFile = newSchedFile;
                break;
                }
                case 2: {
                    cout << "Enter new Start Hour: ";
                    cin >> schedHour;
                    cin.ignore();
                    cout << "Enter new Start Minute: ";
                    cin >> schedMinute;
                    cin.ignore();
                    cout << "Enter new Start Second: ";
                    cin >> schedSecond;
                    cin.ignore();
                    cout << "Enter Amount of Minute for the Course: ";
                    cin >> amountMinute;
                    cin.ignore();

                    holder->schedHour = schedHour;
                    holder->schedMinute = schedMinute;
                    holder->schedSecond = schedSecond;
                    holder->amountMinute = amountMinute;
                    TimeFormat();
                    break;
                }
                case 3: {
                    cout << "Enter new Section: ";
                    getline(cin, newSection);
                    UpperString(newSection);
                    holder->section = newSection;

                    newSchedFile = "Schedules\\" + holder->section + "_" + holder->courseCode + "_" + holder->weekDay + ".txt";
                    rename(schedFile.c_str(), newSchedFile.c_str());
                    schedFile = newSchedFile;
                    break;
                }
                case 4: {
                    cout << "Enter new Room: ";
                    getline(cin, newRoom);
                    UpperString(newRoom);
                    holder->roomNumber = newRoom;
                    break;
                }
                case 0:
                    return;
                default:
                    cout << "Invalid choice!\n";
                    return;
            }

            ofstream ofile(schedFile);
            ofile << holder->courseCode << "\n";
            ofile << holder->courseTitle << "\n";
            ofile << holder->section << "\n";
            ofile << holder->numUnits << "\n";
            ofile << holder->weekDay << "\n";
            ofile << holder->startTime << " - " << holder->endTime << "\n";
            ofile << holder->roomNumber << "\n";
            ofile.close();
            cout << "Schedule successfully edited!\n";
            return;
        }
    } else {
        cout << "Schedule not found!\n";
    }
}

void Schedule::DeleteSchedule() {
    string section, courseCode, weekDay, schedFile;

    cout << "Enter Section: ";
    getline(cin, section);
    cout << "Enter Course Code: ";
    getline(cin, courseCode);
    cout << "Enter Day: ";
    getline(cin, weekDay);

    UpperString(section);
    UpperString(courseCode);
    UpperString(weekDay);
    schedFile = "Schedules\\" + section + "_" + courseCode + "_" + weekDay + ".txt";

    ifstream ifile(schedFile);
    if (ifile.is_open()) {
        ifile.close();
        remove(schedFile.c_str());
        ifstream schedIfile("Schedules\\SCHEDULES.txt");
        ofstream tempFile("Schedules\\temp.txt");
        string line;
        while (getline(schedIfile, line)) {
            if (line != section + "_" + courseCode + "_" + weekDay) {
                tempFile << line << "\n";
            }
        }
        schedIfile.close();
        tempFile.close();
        remove("Schedules\\SCHEDULES.txt"); 
        rename("Schedules\\temp.txt", "Schedules\\SCHEDULES.txt");
        cout << "Schedule successfully deleted!\n";
    } else {
        cout << "Schedule not found!\n";
    }
}

void Schedule::TimeFormat() {
    const int SIZE = 100;
    struct tm time;
    char schedTime[SIZE];
    string startTime, endTime;
    int totalMinutes, amountMinutes;

    time.tm_hour = holder->schedHour;
    time.tm_min = holder->schedMinute;
    time.tm_sec = holder->schedSecond;

    time.tm_isdst = 0;
    mktime(&time);

    strftime(schedTime, SIZE, "%H:%M:%S", &time);
    holder->startTime = string(schedTime);

    totalMinutes = holder->schedHour * 60 + holder->schedMinute;
    amountMinutes = holder->amountMinute;
    totalMinutes += amountMinutes;

    time.tm_hour = totalMinutes / 60;
    time.tm_min = totalMinutes % 60;
    mktime(&time);

    strftime(schedTime, SIZE, "%H:%M:%S", &time);
    holder->endTime = string(schedTime);
}

void Schedule::UpperString(string &str) {
     for (int i = 0; i < str.length(); i++) {
        str[i] = toupper(str[i]);
    }
}

void Schedule::LoadFiles() {
    ifstream ifile("Schedules\\SCHEDULES.txt"); // Opens the txt file where all file names existing gets stored
    string schedFile, startTime, endTime;

    if (ifile.is_open()) {
        while (getline(ifile, schedFile)) { // Iterates over file names inside the text file 
            ifstream schedIfile("Schedules\\" + schedFile + ".txt");
            if (schedIfile.is_open()) {
                string scheduleData[7];
                for (int i = 0; i < 7; i++) {
                    getline(schedIfile, scheduleData[i]); // Iterates over the data of the open schedule file
                }
                schedIfile.close();

                holder = new SchedNode;
                holder->courseCode = scheduleData[0];
                holder->courseTitle = scheduleData[1];
                holder->section = scheduleData[2];
                holder->numUnits = stoi(scheduleData[3]);
                holder->weekDay = scheduleData[4];
                startTime = scheduleData[5].substr(0, 5);
                endTime = scheduleData[5].substr(7);
                holder->startTime = startTime;
                holder->endTime = endTime;
                holder->roomNumber = scheduleData[6];

                holder->schedHour = stoi(startTime.substr(0, 2));
                holder->schedMinute = stoi(startTime.substr(3, 2));
                holder->schedHour = stoi(endTime.substr(0, 2));
                holder->schedMinute = stoi(endTime.substr(3, 2));

                // Puts all the data from the found files to the record again
                if (root == NULL) {
                    root = holder; 
                } else {
                    current = root;
                    while (true) {
                        if (holder->section < current->section) {
                            if (current->left == NULL) {
                                current->left = holder;
                                break;
                            }
                            current = current->left;
                        } else {
                            if (current->right == NULL) {
                                current->right = holder;
                                break;
                            }
                            current = current->right;
                        }
                    }
                }
            } else {
                cout << "Failed to open file: " << schedFile << ".txt" << endl;
            }
        }
        ifile.close(); // Closes the schedules txt file either from the error catcher or the function has completely loaded all
                       // schedule files
    } else {
        cout << "Failed to open SCHEDULES.txt file." << endl;
    }
}

void Schedule::AddFileNameRecord() {
    ofstream ofile("Schedules\\SCHEDULES.txt", ios::app);
    ofile << holder->section + "_" + holder->courseCode + "_" + holder->weekDay + "\n";
    ofile.close();
}