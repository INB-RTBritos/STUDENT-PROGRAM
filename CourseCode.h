#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cctype>

using namespace std;

class Course {
private:
    // These are the private member variables for course information.
    string CourseCode;
    string CourseTitle;
    int Units;
    int YearLevel;

public:
    // This is the constructor for course information
    Course(string code = "", string title = "", int unit = 0, int year = 0)
        : CourseCode(code), CourseTitle(title), Units(unit), YearLevel(year) {}

    // These are the declaration for the function members for course information
    void Display() const;
    string GetFileName() const;
    void SaveToFile() const;
    void LoadFromFile(const string& fileName);

    string GetCourseCode() const { return CourseCode; }
    void SetCourseCode(const string& code) { CourseCode = code; }
    
    string GetCourseTitle() const { return CourseTitle; }
    void SetCourseTitle(const string& title) { CourseTitle = title; }
    
    int GetUnits() const { return Units; }
    void SetUnits(int units) { Units = units; }
    
    int GetYearLevel() const { return YearLevel; }
    void SetYearLevel(int year) { YearLevel = year; }
};

class Node {
public:
    // These are the private member variables for Node
    Course course;
    Node* left;
    Node* right;

    // This is the constructor of Node
    Node(Course c) : course(c), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    // These are the private members for BinaryTree
    Node* root;
    BinaryTree() : root(nullptr) {}
    void Insert(const Course& course);
    void ViewCourses() const;
    Node* Find(const string& CourseCode) const;
    void Remove(const string& CourseCode);

private:
    Node* Insertion(Node* node, const Course& course);
    void InOrder(Node* node) const;
    Node* Find(Node* node, const string& CourseCode) const;
    Node* Remove(Node* node, const string& CourseCode);
    Node* MinValueNode(Node* node);
};

//These are function declarations
void HeaderDesign();
bool IsAlphaString(const string& str);
void AddCourse(BinaryTree& tree);
void EditCourse(BinaryTree& tree);
void DeleteCourse(BinaryTree& tree);
void LoadCourses(BinaryTree& tree);
int CourseCodeMenu();
int CourseFunctionalities();
void UpdateRecordList(const string& courseCode, bool isAdding);
void HeaderDesignCopy2();

// This function pauses the screen to prevent the program from carrying tasks consecutively
void Pause(){
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
    system("clear");
}

void Course::Display() const {
    cout << "| " << setw(11) << CourseCode << " | " << setw(60) << CourseTitle << " | "
         << setw(5) << Units << " | " << setw(10) << YearLevel << " |\n";
    cout << "+" << setw(97) << setfill('-') << "" << setfill(' ') << "+" << endl;
}

string Course::GetFileName() const {
    return "output/CourseRecords/" + CourseCode + ".txt";
}

void Course::SaveToFile() const {
    ofstream file(GetFileName());
    if (file.is_open()) {
        file << CourseCode << endl;
        file << CourseTitle << endl;
        file << Units << endl;
        file << YearLevel << endl;
        file.close();
        UpdateRecordList(CourseCode, true);
    } else {
        cerr << "Unable to open file for writing: " << GetFileName() << endl;
    }
}

void Course::LoadFromFile(const string& fileName) {
    ifstream file(fileName);
    if (file.is_open()) {
        getline(file, CourseCode);
        getline(file, CourseTitle);
        file >> Units;
        file.ignore();
        file >> YearLevel;
        file.ignore();
        file.close();
    } else {
        cerr << "Unable to open file for reading: " << fileName << endl;
    }
}

void BinaryTree::Insert(const Course& course) {
    root = Insertion(root, course);
}

void BinaryTree::ViewCourses() const {
    system("clear");
    HeaderDesignCopy2();
    if (root == nullptr) {
        cout << "No courses available." << endl;
        return;
    }
    cout << endl;
    cout << "+" << setw(97) << setfill('=') << "" << setfill(' ') << "+\n";
    cout << "|                                         COURSE RECORDS                                          |\n";
    cout << "+" << setw(97) << setfill('=') << "" << setfill(' ') << "+\n";
    cout << "| Course Code |                           Course Title                       | Units | Year Level |\n";
    cout << "|" << setw(97) << setfill('=') << "" << setfill(' ') << "+\n";

    InOrder(root);
    cout << endl;
}

Node* BinaryTree::Find(const string& CourseCode) const {
    return Find(root, CourseCode);
}

void BinaryTree::Remove(const string& CourseCode) {
    root = Remove(root, CourseCode);
}

Node* BinaryTree::Insertion(Node* node, const Course& course) {
    if (node == nullptr) return new Node(course);
    if (course.GetCourseCode() < node->course.GetCourseCode())
        node->left = Insertion(node->left, course);
    else
        node->right = Insertion(node->right, course);
    return node;
}

void BinaryTree::InOrder(Node* node) const {
    if (node == nullptr) return;
    InOrder(node->left);
    node->course.Display();
    InOrder(node->right);
}

Node* BinaryTree::Find(Node* node, const string& CourseCode) const {
    if (node == nullptr || node->course.GetCourseCode() == CourseCode)
        return node;
    if (CourseCode < node->course.GetCourseCode())
        return Find(node->left, CourseCode);
    return Find(node->right, CourseCode);
}

Node* BinaryTree::Remove(Node* node, const string& CourseCode) {
    if (node == nullptr) return node;

    if (CourseCode < node->course.GetCourseCode()) {
        node->left = Remove(node->left, CourseCode);
    } else if (CourseCode > node->course.GetCourseCode()) {
        node->right = Remove(node->right, CourseCode);
    } else {
        if (node->left == nullptr) {
            Node* temp = node->right;
            UpdateRecordList(node->course.GetCourseCode(), false);
            remove(node->course.GetFileName().c_str());
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            Node* temp = node->left;
            UpdateRecordList(node->course.GetCourseCode(), false);
            remove(node->course.GetFileName().c_str());
            delete node;
            return temp;
        }

        Node* temp = MinValueNode(node->right);
        node->course = temp->course;
        node->right = Remove(node->right, temp->course.GetCourseCode());
    }
    return node;
}



Node* BinaryTree::MinValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != nullptr)
        current = current->left;
    return current;
}

bool IsAlphaString(const string& str) {
    for (char c : str) {
        if (!isalpha(c) && !isspace(c))
            return false;
    }
    return true;
}

void AddCourse(BinaryTree& tree) {
    string code, title, input;
    int units, year;
    bool isValid = false;

    HeaderDesignCopy2();

    while (true) {
        cout << "Enter course code: ";
        cin >> code;
        cin.ignore();
        if (tree.Find(code) == nullptr) {
            break;
        }
        cout << "Course code already exists! Please enter a different course code." << endl;
    }

    while (true) {
        cout << "Enter course title: ";
        getline(cin, title);

        for (char c : title) {
            if (isalnum(c)) {
                isValid = true;
                break;
            }
        }

        if (isValid) {
            break;
        } else {
            cout << "Invalid input! \nCourse title must contain at least one alphanumeric character." << endl;
        }
    }

    while (true) {
        cout << "Enter number of units (0 to 9): ";
        cin >> input;

        if (input.length() == 1 && isdigit(input[0])) {
            units = input[0] - '0';
            if (units >= 0 && units <= 9) {
                break;
            }
        }
        cout << "Invalid input! Please enter a number between 0 and 9." << endl;
    }

    while (true) {
        cout << "Enter year level (1 to 4): ";
        cin >> input;

        if (input.length() == 1 && isdigit(input[0])) {
            year = input[0] - '0';
            if (year >= 1 && year <= 4) {
                break;
            }
        }
        cout << "Invalid input! Please enter a year level between 1 and 4." << endl;
    }


    Course course(code, title, units, year);
    course.SaveToFile();
    tree.Insert(course);

    cout << "Course added successfully." << endl;
    Pause();
}

void EditCourse(BinaryTree& tree) {
    string code, input, title;
    int units, year;
    bool isValid = false;
    
    cout << "Enter course code to edit: ";
    cin >> code;
    cin.ignore();
    Node* node = tree.Find(code);
    if (node == nullptr) {
        system("clear");
        cout << "Course not found.\n";
        return;
    }

    while (true) {
        cout << "Enter course title: ";
        getline(cin, title);

        for (char c : title) {
            if (isalnum(c)) {
                isValid = true;
                break;
            }
        }

        if (isValid) {
            break;
        } else {
            cout << "Invalid input! \nCourse title must contain at least one alphanumeric character." << endl;
        }
    }

    while (true) {
        cout << "Enter new number of units (0 to 9): ";
        cin >> input;

        if (input.length() == 1 && isdigit(input[0])) {
            units = input[0] - '0';
            if (units >= 0 && units <= 9) {
                break;
            }
        }
        cout << "Invalid input! Please enter a number between 0 and 9." << endl;
    }

    while (true) {
        cout << "Enter new year level (1 to 4): ";
        cin >> input;

        if (input.length() == 1 && isdigit(input[0])) {
            year = input[0] - '0';
            if (year >= 1 && year <= 4) {
                break;
            }
        }
        cout << "Invalid input! Please enter a year level between 1 and 4." << endl;
    }

    node->course.SetCourseTitle(title);
    node->course.SetUnits(units);
    node->course.SetYearLevel(year);
    node->course.SaveToFile();

    cout << "Course edited successfully!" << endl;
    Pause();
    cout << endl;
}

void DeleteCourse(BinaryTree& tree) {
    string code;
    cout << "Enter course code to delete: ";
    cin >> code;
    cin.ignore();
    Node* node = tree.Find(code);
    if (node == nullptr) {
        system("clear");
        cout << "Course not found.\n";
        return;
    }

    tree.Remove(code);
    system("clear");


    cout << "Course deleted successfully." << endl;
    Pause();
}


void LoadCourses(BinaryTree& tree) {
    ifstream recordList("output/CourseRecords/recordlist.txt");
    string code;
    while (getline(recordList, code)) {
        Course course;
        course.LoadFromFile("output/CourseRecords/" + code + ".txt");
        tree.Insert(course);
    }
    recordList.close();
}


void UpdateRecordList(const string& courseCode, bool isAdding) {
    ifstream inFile("output/CourseRecords/recordlist.txt");
    ofstream tempFile("output/CourseRecords/temp.txt");
    string line;
    bool found = false;
    
    while (getline(inFile, line)) {
        if (line == courseCode) {
            found = true;
            if (!isAdding) continue;
        }
        tempFile << line << endl;
    }

    if (isAdding && !found) {
        tempFile << courseCode << endl;
    }

    inFile.close();
    tempFile.close();

    remove("output/CourseRecords/recordlist.txt");
    rename("output/CourseRecords/temp.txt", "output/CourseRecords/recordlist.txt");
}

int CourseCodeMenu() {
    int choice;
    do {
    HeaderDesignCopy2();
    cout << endl;
    cout << "+" << setw(97) << setfill('=') << "" << setfill(' ') << "+\n";
    cout << "|                                          COURSE MENU                                            |\n";
    cout << "+" << setw(97) << setfill('=') << "" << setfill(' ') << "+" << endl;
    cout << "|" << setw(10) << right << "[1] " << setw(87) << left << "Add Course" << "|" << endl;
    cout << "|" << setw(10) << right << "[2] " << setw(87) << left << "View Courses" << "|" << endl;
    cout << "|" << setw(10) << right << "[3] " << setw(87) << left << "Edit Course" << "|" << endl;
    cout << "|" << setw(10) << right << "[4] " << setw(87) << left << "Delete Course" << "|" << endl;
    cout << "|" << setw(10) << right << "[0] " << setw(87) << left << "Return To Menu" << "|\n";
    cout << "+" << setw(97) << setfill('-') << "" << setfill(' ') << "+" << endl << endl << endl;
    cout << ":: ";
    cin >> choice;
    cin.ignore();
    } while (choice < 0 || choice > 4);
    system("clear");
    return choice;
}

void HeaderDesignCopy2() {
    cout << "                        .|                                          _" << endl;
    cout << "                       | |                                         | |" << endl;
    cout << "                       |'|            ._____                       |'|            ._____" << endl;
    cout << "               ___    |  |            |.   |' .---" << "-|       ___    |  |            |.   |' .---" << ".  " << endl;
    cout << "       _    .-'   '-. |  |     .--'|  ||   | _|    |    .-'   '-. |  |     .--'|  ||   | _|    |" << endl;
    cout << "    .-'|  _.|  |    ||   '-__  |   |  |    ||      |  _.|  |    ||   '-__  |   |  |    ||      |  " << endl;
    cout << "    |' | |.    |    ||       | |   |  |    ||      | |.    |    ||       | |   |  |    ||      |" << endl;
    cout << " ___|  '-'     '      \"       '-'   '-.'    '`      |-'     '      \"       '-'   '-.'    '`      |___" << endl;
    cout << " ___      _        _             _   ___     _ _            _   _      _                _ _                  " << endl;
    cout << "|_ _|__ _| |___ __(_)__ _   _ _ (_) | _ )_ _(_) |_ ___ ___ | | | |_ _ (_)_ _____ _ _ __(_) |_ _  _ " << endl;
    cout << " | |/ _` | / -_|_-< / _` | | ' \\| | | _ \\ '_| |  _/ _ (_-< | |_| | ' \\| \\ V / -_) '_(_-< |  _| || | " << endl;
    cout << "|___\\__, |_\\___/__/_\\__,_| |_||_|_| |___/_| |_|\\__\\___/__/  \\___/|_||_|_|\\_/\\___|_| /__/_|\\__|\\_, |" << endl;
    cout << "    |___/                                                                                     |__/           " << endl;
}

int CourseFunctionalities() {
    BinaryTree tree;
    LoadCourses(tree);
    while (true) {
        switch (CourseCodeMenu()) {
            case 1:
            AddCourse(tree);
            break;
            case 2:
            tree.ViewCourses();
            break;
            case 3:
            EditCourse(tree);
            break;
            case 4:
            DeleteCourse(tree);
            break;
            case 0:
            return 0;
            default:
            return 0;
        }
    }
    return 0;
}




