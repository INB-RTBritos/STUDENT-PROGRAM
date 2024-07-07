#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cctype>
#include <stack>
#include <list>

using namespace std;

class Course {
public:
    string courseCode;
    string courseTitle;
    int units;
    int yearLevel;

    Course(string code = "", string title = "", int unit = 0, int year = 0) 
        : courseCode(code), courseTitle(title), units(unit), yearLevel(year) {}

    void display() const {
        cout << "| " << setw(11) << courseCode << " | " << setw(50) << courseTitle << " | "
             << setw(5) << units << " | " << setw(10) << yearLevel << " |\n";
        cout <<"|" <<"---------------------------------------------------------------------------------------"<< "| " << endl;
    }
};

class Node {
public:
    Course course;
    Node* left;
    Node* right;

    Node(Course c) : course(c), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    Node* root;

    BinaryTree() : root(nullptr) {}

    void insert(const Course& course) {
        root = insert(root, course);
    }

    void viewCourses() const {
        if (root == nullptr) {
            cout << "No courses available." << endl;
            return;
        }
        
        cout << "|=======================================================================================|\n";
        cout << "|                                    COURSE RECORDS                                     |\n";
        cout << "|=======================================================================================|\n";
        cout << "| Course Code | Course Title                                       | Units | Year Level |\n";
        cout << "|=======================================================================================|\n";

        inOrder(root);

        cout << "|=======================================================================================|\n";
    }

    Node* find(const string& courseCode) const {
        return find(root, courseCode);
    }

    void remove(const string& courseCode) {
        root = remove(root, courseCode);
    }

private:
    Node* insert(Node* node, const Course& course) {
        if (node == nullptr) return new Node(course);
        if (course.courseCode < node->course.courseCode)
            node->left = insert(node->left, course);
        else
            node->right = insert(node->right, course);
        return node;
    }

    void inOrder(Node* node) const {
        if (node == nullptr) return;
        inOrder(node->left);
        node->course.display();
        inOrder(node->right);
    }

    Node* find(Node* node, const string& courseCode) const {
        if (node == nullptr || node->course.courseCode == courseCode)
            return node;
        if (courseCode < node->course.courseCode)
            return find(node->left, courseCode);
        return find(node->right, courseCode);
    }

    Node* remove(Node* node, const string& courseCode) {
        if (node == nullptr) return node;

        if (courseCode < node->course.courseCode) {
            node->left = remove(node->left, courseCode);
        } else if (courseCode > node->course.courseCode) {
            node->right = remove(node->right, courseCode);
        } else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = minValueNode(node->right);
            node->course = temp->course;
            node->right = remove(node->right, temp->course.courseCode);
        }
        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }
};

bool isAlphaString(const string& str) {
    for (char c : str) {
        if (!isalpha(c) && c != ' ') return false;
    }
    return true;
}

void addCourse(BinaryTree& tree) {
    string code, title;
    int units, year;
    cout << "Enter course code: ";
    cin >> code;
    cin.ignore();
    cout << "Enter course title: ";
    getline(cin, title);
    while (!isAlphaString(title)) {
        cout << "Invalid title. Enter course title again: ";
        getline(cin, title);
    }
    cout << "Enter number of units: ";
    cin >> units;
    cout << "Enter year level: ";
    cin >> year;

    Course course(code, title, units, year);
    tree.insert(course);
    ofstream file("courses.txt", ios::app);
    if (file.is_open()) {
        file << code << "," << title << "," << units << "," << year << "\n";
        file.close();
    } else {
        cerr << "Unable to open file for writing.\n";
    }
}

void editCourse(BinaryTree& tree) {
    string code;
    cout << "Enter course code to edit: ";
    cin >> code;
    Node* node = tree.find(code);
    if (node == nullptr) {
        cout << "Course not found.\n";
        return;
    }

    string title;
    int units, year;
    cout << "Enter new course title: ";
    cin.ignore();
    getline(cin, title);
    while (!isAlphaString(title)) {
        cout << "Invalid title. Enter new course title again: ";
        getline(cin, title);
    }
    cout << "Enter new number of units: ";
    cin >> units;
    cout << "Enter new year level: ";
    cin >> year;

    node->course.courseTitle = title;
    node->course.units = units;
    node->course.yearLevel = year;

    ofstream file("courses.txt");
    if (file.is_open()) {
        stack<Node*> s;
        Node* current = tree.root;
        while (current != nullptr || !s.empty()) {
            while (current != nullptr) {
                s.push(current);
                current = current->left;
            }
            current = s.top();
            s.pop();
            file << current->course.courseCode << "," << current->course.courseTitle << "," << current->course.units << "," << current->course.yearLevel << "\n";
            current = current->right;
        }
        file.close();
    } else {
        cerr << "Unable to open file for writing.\n";
    }
}

void deleteCourse(BinaryTree& tree) {
    string code;
    cout << "Enter course code to delete: ";
    cin >> code;
    Node* node = tree.find(code);
    if (node == nullptr) {
        cout << "Course not found.\n";
        return;
    }

    tree.remove(code);

    ofstream file("courses.txt");
    if (file.is_open()) {
        stack<Node*> s;
        Node* current = tree.root;
        while (current != nullptr || !s.empty()) {
            while (current != nullptr) {
                s.push(current);
                current = current->left;
            }
            current = s.top();
            s.pop();
            file << current->course.courseCode << "," << current->course.courseTitle << "," << current->course.units << "," << current->course.yearLevel << "\n";
            current = current->right;
        }
        file.close();
    } else {
        cerr << "Unable to open file for writing.\n";
    }
}

void loadCourses(BinaryTree& tree) {
    ifstream file("courses.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t pos = 0;
            string token;
            list<string> tokens;
            while ((pos = line.find(',')) != string::npos) {
                token = line.substr(0, pos);
                tokens.push_back(token);
                line.erase(0, pos + 1);
            }
            tokens.push_back(line);

            if (tokens.size() == 4) {
                auto it = tokens.begin();
                string code = *it++;
                string title = *it++;
                int units = stoi(*it++);
                int year = stoi(*it);

                Course course(code, title, units, year);
                tree.insert(course);
            }
        }
        file.close();
    } else {
        cerr << "Unable to open file for reading.\n";
    }
}