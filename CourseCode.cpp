#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cctype>
#include <stack>
#include <list>
#include "CourseCode.h"

using namespace std;


int main() {
    BinaryTree tree;
    loadCourses(tree);

    int choice;
    do {
        cout << "Course Management Menu:\n";
        cout << "1. Add Course\n";
        cout << "2. View Courses\n";
        cout << "3. Edit Course\n";
        cout << "4. Delete Course\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                addCourse(tree);
                break;
            case 2:
                tree.viewCourses();
                break;
            case 3:
                editCourse(tree);
                break;
            case 4:
                deleteCourse(tree);
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
