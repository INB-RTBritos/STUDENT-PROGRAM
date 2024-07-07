#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <cstdio>

using namespace std;
class StudentDetails
{
private:
    // Declare Student Information variables.
    struct StudentNode
    {
        string firstName, lastName, middleName, degreeProgram, studentGender, studentAddress, birthday;
        int idNumber, yearLevel;
        StudentNode *left;
        StudentNode *right;
    } *node, *current;

public:
    StudentNode *root;
    // Add input validation functions.
    bool IsValidName(string);
    bool IsValidGender(string);
    int MonthNameToNumber(string &);
    bool IsValidBirthMonth(string &);
    bool IsValidBirthDate(int, string &, int);
    // Constructor
    StudentDetails();
    // Add main functions
    void AddStudent(string, string, string, string, string, string, string, int, int);
    void SaveIDToList();
    void ViewDetails(string);
    void EditStudent(string);
    void DeleteStudent(string);
    void RestoreStudentInfo(int, string, string, string, string, string, string, string, int);
    void FetchEachStudentFile(string);
    void FetchStudentInfo();
    void ViewStudent(StudentNode *);
};

bool StudentDetails::IsValidName(string str) // Function for checking if the input is Alpha or a Space mostly used for names and such
{
    // Convert the string to lowercase manually
    for (int i = 0; i < str.length(); i++)
    {
        if (!isalpha(str[i]) && !isspace(str[i])) // Check if alpha or a space
        {
            cout << "Please Enter a Valid Name (a-z)" << endl;
            return false;
        }
    }

    return true;
}

bool StudentDetails::IsValidGender(string str) // Function to check if the input is either male or female regardless of the case
{
    // Convert the string to lowercase manually
    for (int i = 0; i < str.length(); ++i)
    {
        str[i] = tolower(str[i]);
    }

    // Check if the string is male or female
    if (str == "male" || str == "female")
    {
        return true;
    }
    else
    {
        cout << "Please Enter a Valid Gender." << endl;
        return false;
    }
}

int StudentDetails::MonthNameToNumber(string &monthName) // Converts the month name input into its corresponding number
{
    if (monthName == "January")
    {
        return 1;
    }
    if (monthName == "February")
    {
        return 2;
    }
    if (monthName == "March")
    {
        return 3;
    }
    if (monthName == "April")
    {
        return 4;
    }
    if (monthName == "May")
    {
        return 5;
    }
    if (monthName == "June")
    {
        return 6;
    }
    if (monthName == "July")
    {
        return 7;
    }
    if (monthName == "August")
    {
        return 8;
    }
    if (monthName == "September")
    {
        return 9;
    }
    if (monthName == "October")
    {
        return 10;
    }
    if (monthName == "November")
    {
        return 11;
    }
    if (monthName == "December")
    {
        return 12;
    }
    return -1;
}

bool StudentDetails::IsValidBirthMonth(string &month) // Function to check if the input is a valid month
{
    string validMonths[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    for (string &validMonth : validMonths)
    {
        if (month == validMonth)
        {
            return true;
        }
    }
    return false;
}

bool StudentDetails::IsValidBirthDate(int birthday, string &month, int year) // Function to check if the date of birth is valid, checks leap years and such
{
    int monthNumber = MonthNameToNumber(month);

    if (monthNumber == -1)
    {
        return false; // Invalid month
    }

    if (birthday < 1 || birthday > 31)
    {
        return false; // Invalid day
    }

    if (monthNumber == 2)
    {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        {
            return birthday <= 29; // Leap year
        }
        else
        {
            return birthday <= 28; // Non-leap year
        }
    }
    else if (monthNumber == 4 || monthNumber == 6 || monthNumber == 9 || monthNumber == 11)
    {
        return birthday <= 30; // April, June, September, November have 30 days
    }
    else
    {
        return true; // All other months have 31 days
    }
}

StudentDetails::StudentDetails() // Constructor
{
    root = NULL;
}

void StudentDetails::AddStudent(string fName, string lName, string mName, string dProgram, string sGender, string sAddress, string bDay, int idNum, int yrLvl) // Function to add student into the tree and creates a file to store their data
{
    string filename;
    // Create and instantiate the node
    node = new StudentNode;
    node->firstName = fName;
    node->lastName = lName;
    node->middleName = mName;
    node->degreeProgram = dProgram;
    node->studentGender = sGender;
    node->studentAddress = sAddress;
    node->birthday = bDay;
    node->idNumber = idNum;
    node->yearLevel = yrLvl;
    node->left = NULL;
    node->right = NULL;

    // Check if the tree is empty
    if (root == NULL)
    {
        // Set the new node as the root
        root = node;
        cout << "New Student is Successfully Added\n";
    }
    else
    {                   // If the tree has nodes already
        current = root; // Get the root node
        while (current != NULL)
        {
            // If the value of the new node is lesser than the current, go left
            if (idNum < current->idNumber)
            {
                if (current->left == NULL)
                {
                    // If the left pointer of the currrent node is empty
                    //   insert the new node to the left of the current node
                    current->left = node;
                    cout << "New Student is Successfully Added\n";
                    break;
                }
                else
                {
                    // Go to the next node if the left pointer has a child already
                    current = current->left;
                }
                // If the value of the new node is greater than the current, go right
            }
            else if (idNum > current->idNumber)
            {
                if (current->right == NULL)
                {
                    // If the right pointer of the currrent node is empty
                    //   insert the new node to the right of the current node
                    current->right = node;
                    cout << "New Student is Successfully Added\n";
                    break;
                }
                else
                {
                    // Go to the next node if the right pointer has a child already
                    current = current->right;
                }
            }
            else
            {
                cout << "Duplicate values are not allowed in trees.";
                return;
            }
        }
    }

    // Generate a filename from the input id, use to_string function to convert int to string
    filename = to_string(idNum) + ".txt";
    // Create the file object and open the file
    ofstream ofile(filename);
    if (!ofile) // Error display if the file won't open
    {
        cerr << "Error opening file" << endl;
        return;
    }
    // Store data to file
    ofile << node->idNumber << endl;
    ofile << node->firstName << endl;
    ofile << node->middleName << endl;
    ofile << node->lastName << endl;
    ofile << node->birthday << endl;
    ofile << node->studentGender << endl;
    ofile << node->studentAddress << endl;
    ofile << node->degreeProgram << endl;
    ofile << node->yearLevel << endl;
    // Close the ofstream object, always close the object after using it to avoid problems
    ofile.close();

    SaveIDToList(); // Save the student id to the idlist file
}

void StudentDetails::SaveIDToList() // Saves the Stud num to a list for reading purposes
{
    // Create another file to store all of the student numbers
    ofstream ofile("idlist.txt", ios::app);
    if (!ofile) // Error display if the file won't open
    {
        cerr << "Error opening file" << endl;
        return;
    }
    // Store the idNumber
    ofile << node->idNumber << endl;

    // Close the file
    ofile.close();
}

// This shows ID Number and full names of all students in the program. The list must be sorted.
void StudentDetails::ViewStudent(StudentNode *tempNode)
{
    if (tempNode == NULL)
    { // Base case of the recursion
        return;
    }
    // Left -> Root -> Right
    ViewStudent(tempNode->left);
    cout << tempNode->idNumber << "\t\t" << tempNode->firstName << " " << tempNode->middleName << " " << tempNode->lastName << endl;
    ViewStudent(tempNode->right);
}

void StudentDetails::FetchStudentInfo() // Reads the idlist file to traverse through the student files
{
    string filename;
    // Open a ifstream object and open the idlist file
    ifstream ifile("idlist.txt");
    if (!ifile) // Error display if the file won't open
    {
        cerr << "Error opening file" << endl;
        return;
    }
    while (getline(ifile, filename))
    { // Fetch data stored in the file one line at a time
        FetchEachStudentFile(filename);
    }

    ifile.close();
}

void StudentDetails::FetchEachStudentFile(string idOfFile) // Reads each student file to restore it to the tree upon start of program
{
    int idNum, yrLvl, i = 0;
    string fName, mName, lName, bDay, sGender, sAddress, dProgram;
    string *s = new string[9];

    ifstream ifile(idOfFile + ".txt"); // Opens the student file given by the FetchStudentInfo func
    if (!ifile) // Error display if the file won't open
    {
        cerr << "Error opening file" << endl;
        return;
    }
    while (getline(ifile, s[i]))
    { // Fetch data stored in the file one line at a time
        i++;
    }

    idNum = stoi(s[0]);
    fName = s[1];
    mName = s[2];
    lName = s[3];
    bDay = s[4];
    sGender = s[5];
    sAddress = s[6];
    dProgram = s[7];
    yrLvl = stoi(s[8]);

    ifile.close();

    RestoreStudentInfo(idNum, fName, mName, lName, bDay, sGender, sAddress, dProgram, yrLvl); // Passes the information to the RestoreStudentInfo function to insert the info into the tree again
}

void StudentDetails::RestoreStudentInfo(int idNum, string fName, string mName, string lName, string bDay, string sGender, string sAddress, string dProgram, int yrLvl) // Restores the data into the tree
{
    // Create and instantiate the node
    node = new StudentNode;
    node->firstName = fName;
    node->lastName = lName;
    node->middleName = mName;
    node->degreeProgram = dProgram;
    node->studentGender = sGender;
    node->studentAddress = sAddress;
    node->birthday = bDay;
    node->idNumber = idNum;
    node->yearLevel = yrLvl;
    node->left = NULL;
    node->right = NULL;

    // Check if the tree is empty
    if (root == NULL)
    {
        // Set the new node as the root
        root = node;
        cout << "Student Info Restored\n";
    }
    else
    {                   // If the tree has nodes already
        current = root; // Get the root node
        while (current != NULL)
        {
            // If the value of the new node is lesser than the current, go left
            if (idNum < current->idNumber)
            {
                if (current->left == NULL)
                {
                    // If the left pointer of the currrent node is empty
                    //   insert the new node to the left of the current node
                    current->left = node;
                    cout << "Student Info Restored\n";
                    break;
                }
                else
                {
                    // Go to the next node if the left pointer has a child already
                    current = current->left;
                }
                // If the value of the new node is greater than the current, go right
            }
            else if (idNum > current->idNumber)
            {
                if (current->right == NULL)
                {
                    // If the right pointer of the currrent node is empty
                    //   insert the new node to the right of the current node
                    current->right = node;
                    cout << "Student Info Restored\n";
                    break;
                }
                else
                {
                    // Go to the next node if the right pointer has a child already
                    current = current->right;
                }
            }
            else
            {
                cout << "Duplicate values are not allowed in trees.";
                return;
            }
        }
    }
}

void StudentDetails::ViewDetails(string idNum) // Preview details inside the student's record
{
    int i = 0;
    string *s = new string[9];
    ifstream ifile(idNum + ".txt");
    if (!ifile) // Error display if the file won't open
    {
        cerr << "Error opening file" << endl;
        return;
    }
    while (getline(ifile, s[i]))
    { // Fetch data stored in the file one line at a time and saves it in the string array
        i++;
    }
    // Prints the details stored in the string array
    cout << "\n\nStudent Number: " << s[0] << endl;
    cout << "First Name: " << s[1] << endl;
    cout << "Middle Name: " << s[2] << endl;
    cout << "Last Name: " << s[3] << endl;
    cout << "Birthday: " << s[4] << endl;
    cout << "Gender: " << s[5] << endl;
    cout << "Address: " << s[6] << endl;
    cout << "Degree Program: " << s[7] << endl;
    cout << "Year Level: " << s[8] << endl
         << endl;

    ifile.close();
}

void StudentDetails::EditStudent(string idToEdit)
{
    string fName, mName, lName, bDay, sGender, sAddress, dProgram, birthMonthName, fullBirthday, filename, temp;
    int idNum, yrLvl, choice, birthDay, birthYear, birthMonthNum, i = 0;
    string *s = new string[9];
    ifstream ifile(idToEdit + ".txt");
    if (!ifile) // Error display if the file won't open
    {
        cerr << "Error opening file" << endl;
        return;
    }
    while (getline(ifile, s[i]))
    { // Fetch data stored in the file one line at a time
        i++;
    }

    idNum = stoi(s[0]);
    fName = s[1];
    mName = s[2];
    lName = s[3];
    bDay = s[4];
    sGender = s[5];
    sAddress = s[6];
    dProgram = s[7];
    yrLvl = stoi(s[8]);

    ifile.close();
    // Same with the ViewDetails function, this reprints the information so that the user would know which info they will be editing
    cout << "\n\n1. Student Number: " << idNum << endl;
    cout << "2. First Name: " << fName << endl;
    cout << "3. Middle Name: " << mName << endl;
    cout << "4. Last Name: " << lName << endl;
    cout << "5. Birthday: " << bDay << endl;
    cout << "6. Gender: " << sGender << endl;
    cout << "7. Address: " << sAddress << endl;
    cout << "8. Degree Program: " << dProgram << endl;
    cout << "9. Year Level: " << yrLvl << endl
         << endl;

    cout << "What do you want to edit (1-9): "; // Ask what part to edit
    cin >> choice;
    cin.ignore();

    switch (choice)
    {
    case 1:
    {
        while (true)
        {
            cout << "Enter new ID Number (9-digit ID Number): ";
            cin >> idNum;
            cin.ignore();

            if (idNum >= 201500000 && idNum < 202500000)
                break;
            else
                cout << "Enter a Valid Student Number." << endl;
        }

        ifstream ifile("idlist.txt");
        ofstream ofile("temp.txt");

        if (!ifile || !ofile) // Error display if the file/s won't open
        {
            cerr << "Error opening file" << endl;
            return;
        }

        while (getline(ifile, temp)) // Reads the file and stores strings in temp
        {
            size_t pos = temp.find(idToEdit); // Looks for the id to edit in the list

            while (pos != string::npos) // While everything that has to be replaced isnt replaced yet
            {
                temp.replace(pos, idToEdit.length(), to_string(idNum));     // Replaces the id in the list with the new one starting at the pos
                pos = temp.find(idToEdit, pos + to_string(idNum).length()); // Looks again for other id match
            }

            ofile << temp << "\n"; // Writes the modified line in the temp file
        }

        ifile.close();
        ofile.close();

        // Replace the original idlist.txt with the temporary file
        // Error display if it doesn't go through
        if (remove("idlist.txt") != 0)
        {
            cerr << "Error deleting file: idlist.txt" << endl;
        }
        if (rename("temp.txt", "idlist.txt") != 0)
        {
            cerr << "Error renaming file: temp.txt to idlist.txt" << endl;
        }

        break;
    }
    case 2:
    {
        while (true)
        {
            cout << "Enter new First Name: ";
            getline(cin, fName);

            if (IsValidName(fName))
                break;
        }
        break;
    }
    case 3:
    {
        while (true)
        {
            cout << "Enter new Middle Name: ";
            getline(cin, mName);

            if (IsValidName(mName))
                break;
        }
        break;
    }
    case 4:
    {
        while (true)
        {
            cout << "Enter new Last Name: ";
            getline(cin, lName);

            if (IsValidName(lName))
                break;
        }
        break;
    }
    case 5:
    {
        cout << "Enter new Birth Month: ";
        cin >> birthMonthName;
        while (!IsValidBirthMonth(birthMonthName))
        {
            cout << "Invalid Month! Please enter a valid birth month." << endl;
            cout << "Enter Birth Month: ";
            cin >> birthMonthName;
        }

        cout << "Enter new Birth Day: ";
        cin >> birthDay;

        cout << "Enter new Birth Year: ";
        cin >> birthYear;
        while (!IsValidBirthDate(birthDay, birthMonthName, birthYear))
        {
            cout << "Invalid Birth Date! Please enter a valid Birth Date." << endl;
            cout << "Enter Birth Month: ";
            cin >> birthMonthName;
            cout << "Enter Birth Day: ";
            cin >> birthDay;
            cout << "Enter Birth Year: ";
            cin >> birthYear;
        }

        birthMonthNum = MonthNameToNumber(birthMonthName);                                                // Convert month name to number(int)
        fullBirthday = to_string(birthMonthNum) + "/" + to_string(birthDay) + "/" + to_string(birthYear); // Convert into the full birthday format (string)
        break;
    }
    case 6:
    {
        while (true)
        {
            cout << "Enter new Gender (Male or Female): ";
            cin >> sGender;
            cin.ignore();

            if (IsValidGender(sGender))
                break;
        }
        break;
    }
    case 7:
    {
        while (true)
        {
            cout << "Enter new City Address (ex. Manila City): ";
            getline(cin, sAddress);

            if (IsValidName(sAddress))
                break;
        }
        break;
    }
    case 8:
    {
        while (true)
        {
            cout << "Enter new Degree Program (ex. BSITCST): ";
            cin >> dProgram;

            if (IsValidName(dProgram))
                break;
        }
        break;
    }
    case 9:
    {
        while (true)
        {
            cout << "Enter new Year Level (1-4): ";
            cin >> yrLvl;
            cin.ignore();

            if (yrLvl >= 1 && yrLvl <= 4)
                break;
            else
                cout << "Enter a Valid Year Level." << endl;
        }
        break;
    }
    }

    // Generate a filename from the input id, use to_string function to convert int to string
    filename = to_string(idNum) + ".txt";
    // Create the file object and open the file
    ofstream ofile(filename);

    // Store data to file, overwrites the existing details
    ofile << idNum << endl;
    ofile << fName << endl;
    ofile << mName << endl;
    ofile << lName << endl;
    ofile << bDay << endl;
    ofile << sGender << endl;
    ofile << sAddress << endl;
    ofile << dProgram << endl;
    ofile << yrLvl << endl;
    // Close the ofstream object, always close the object after using it to avoid problems
    ofile.close();
}

void StudentDetails::DeleteStudent(string idNum)
{
    string temp, line;
    string filename = idNum + ".txt";
    remove(filename.c_str());

    ifstream ifile("idlist.txt");
    ofstream ofile("temp.txt");

    if (!ifile || !ofile) // Error display if the file/s won't open
    {
        cerr << "Error opening file" << endl;
        return;
    }

    // Read each line from idlist.txt
    while (getline(ifile, line))
    {
        // If the line doesn't contain the idNum, write it to the temporary file
        if (line.find(idNum) == string::npos)
        {
            ofile << line << "\n";
        }
    }

    ifile.close();
    ofile.close();

    // Replace the original idlist.txt with the temporary file
    // Error display if it doesn't go through
    if (remove("idlist.txt") != 0)
    {
        cerr << "Error deleting file: idlist.txt" << endl;
    }
    if (rename("temp.txt", "idlist.txt") != 0)
    {
        cerr << "Error renaming file: temp.txt to idlist.txt" << endl;
    }
}