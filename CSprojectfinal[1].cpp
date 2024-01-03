#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct StudentRecord {
    string name;
    int age;
    bool gender;
    char grade;
    int yearofenrollment;
    int id;
    float gpa; // GPA should be of type float
};

int totalStudents() {
    int num;
    cout << "Enter the total number of students: " << endl;
    cin >> num;
    return num;
}

int generateID(int length = 8) {
    int id = 0;
    for (int i = 0; i < length; ++i) {
        id = id * 10 + (rand() % 10);
    }
    return id;
}

void saveToFile(StudentRecord records[], int num) {
    ofstream my_file("project.txt", ios::out);
    if (!my_file.is_open()) {
        cout << "Error creating/opening the file!" << endl;
    } else {
        cout << "File created/opened successfully!\n";
    }

    for (int i = 0; i < num; ++i) {
        my_file << records[i].id << " " << records[i].name << " " << records[i].age << " " << records[i].gender << " " << records[i].grade << " " << records[i].yearofenrollment << " " << records[i].gpa << endl;
    }

    my_file.close();
}

void loadFromFile(StudentRecord records[], int& num) {
    ifstream fin("project.txt", ios::in);
    int i = 0;
    while (fin >> records[i].id >> records[i].name >> records[i].age >> records[i].gender >> records[i].grade >> records[i].yearofenrollment >> records[i].gpa) {
        ++i;
    }
    num = i;
    fin.close();
}

float gpaCalc(StudentRecord& record) {
    do {
        cout << "Enter the grade for " << record.name << ": ";
        cin >> record.grade;
        record.grade = toupper(record.grade);

        switch (record.grade) {
            case 'A':
                record.gpa = 4.0;
                break;
            case 'B':
                record.gpa = 3.0;
                break;
            case 'C':
                record.gpa = 2.0;
                break;
            case 'D':
                record.gpa = 1.0;
                break;
            case 'F':
                record.gpa = 0.0;
                break;
            default:
                record.gpa = 0.0;
                cout << "Entered invalid grade for " << record.name << ". Please try again." << endl;
        }

        if (record.gpa != 0.0) {
            cout << "GPA for " << record.name << " is: " << record.gpa << endl;
        }

    } while (record.gpa == 0.0);

    return record.gpa;
}

void searchAndDelete(StudentRecord records[], int& num) {
    int targetID;

    cout << "Enter the id of the record to be deleted: ";
    cin >> targetID;

    int index = -1;
    for (int i = 0; i < num; ++i) {
        if (records[i].id == targetID) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        for (int i = index; i < num - 1; ++i) {
            records[i] = records[i + 1];
        }

        --num;

        cout << "Record with id " << targetID << " deleted successfully.\n";
    } else {
        cout << "Record with id " << targetID << " not found.\n";
    }
}

void displayRecords(const StudentRecord records[], int num) {
    cout << "\nID\tName\tAge\tGender\tGrade\tYear\tGPA\n";
    cout << "------------------------------------------------------------\n";

    for (int i = 0; i < num; ++i) {
        cout << records[i].id << "\t"
             << records[i].name << "\t"
             << records[i].age << "\t"
             << records[i].gender << "\t"
             << records[i].grade << "\t"
             << records[i].yearofenrollment << "\t"
             << records[i].gpa << "\n";
    }

    cout << "------------------------------------------------------------\n";
}

void insertAfter(StudentRecord records[], int& num) {
    int targetID;

    cout << "Enter the id after which the new record should be inserted: ";
    cin >> targetID;

    int index = -1;
    for (int i = 0; i < num; ++i) {
        if (records[i].id == targetID) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        cout << "Enter details for the new student record:\n";
        cout << "id: ";
        cin >> records[num].id;

        records[num].gpa = gpaCalc(records[num]);

        for (int i = num; i > index + 1; --i) {
            records[i] = records[i - 1];
        }

        records[index + 1] = records[num];

        ++num;

        cout << "New record inserted successfully.\n";
    } else {
        cout << "Record with id " << targetID << " not found.\n";
    }
}

void insertBefore(StudentRecord records[], int& num) {
    int targetID;

    cout << "Enter the id before which the new record should be inserted: ";
    cin >> targetID;

    int index = -1;
    for (int i = 0; i< num; ++i) {
        if (records[i].id == targetID) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        cout << "Enter details for the new student record:\n";
        cout << "id: ";
        cin >> records[num].id;

        records[num].gpa = gpaCalc(records[num]);

        for (int i = num; i > index; --i) {
            records[i] = records[i - 1];
        }

        records[index] = records[num];

        ++num;

        cout << "New record inserted successfully.\n";
    } else {
        cout << "Record with id " << targetID << " not found.\n";
    }
}

StudentRecord* enterSecondSet(StudentRecord records[], int& num, int& numSecondSet) {
    cout << "Enter the number of records for the second set: ";
    cin >> numSecondSet;

    StudentRecord* secondSet = new StudentRecord[numSecondSet];

    for (int i = 0; i < numSecondSet; ++i) {
        cout << "Enter the details for record " << i + 1 << " in the second set:\n";

        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, secondSet[i].name);

        cout << "Enter your age: ";
        cin >> secondSet[i].age;

        secondSet[i].id = generateID();
        cout << "Enter your gender (1 for male, 0 for female): ";
        cin >> secondSet[i].gender;

        if (secondSet[i].gender) {
            cout << "Gender: Male\n";
        } else {
            cout << "Gender: Female\n";
        }

        secondSet[i].gpa = gpaCalc(secondSet[i]);
    }

    return secondSet;
}

StudentRecord* mergeArrays(StudentRecord records[], int num, StudentRecord secondSet[], int numSecondSet, int& mergedNum) {
    mergedNum = num + numSecondSet;

    StudentRecord* mergedSet = new StudentRecord[mergedNum];

    for (int i = 0; i < num; ++i) {
        mergedSet[i] = records[i];
    }

    for (int i = 0; i < numSecondSet; ++i) {
        mergedSet[num + i] = secondSet[i];
    }

    return mergedSet;
}

void compareAndDisplay(StudentRecord records[], int num, StudentRecord secondSet[], int numSecondSet) {
    cout << "\nComparing and Displaying Records:\n";
    cout << "\nFirst Set of Records:\n";
    displayRecords(records, num);

    cout << "\nSecond Set of Records:\n";
    displayRecords(secondSet, numSecondSet);

    cout << "\nMerged Set of Records:\n";
    int mergedNum;
    StudentRecord* mergedSet = mergeArrays(records, num, secondSet, numSecondSet, mergedNum);
    displayRecords(mergedSet, mergedNum);

    delete[] mergedSet;
}

void sortArray(StudentRecord records[], int num, bool sortByStudentID) {
    for (int i = 0; i < num - 1; ++i) {
        for (int j = 0; j < num - i - 1; ++j) {
            if ((sortByStudentID && records[j].id > records[j + 1].id) ||
                (!sortByStudentID && records[j].name > records[j + 1].name)) {
                StudentRecord temp = records[j];
                records[j] = records[j + 1];
                records[j + 1] = temp;
            }
        }
    }
}

void arrayManipulationMenu(StudentRecord records[], int& num) {
    int choice;

    do {
        cout << "\nArray Manipulation Menu:\n";
        cout << "1. Append a new record\n";
        cout << "2. Search and delete a student record\n";
        cout << "3. Insert a new record after a specific ID\n";
        cout << "4. Insert a new record before a specific ID\n";
        cout << "5. Display all records\n";
        cout << "6. Save\n";
        cout << "8. Second Set of Records\n";  // Task 5
        cout << "9. Record Comparison and Merging\n";  // Task 6
        cout << "10. Sort Records\n";  // Task 7
        cout << "11. Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter details for the new student record:\n";
                cout << "id: ";
                cin >> records[num].id;
                records[num].gpa = gpaCalc(records[num]);
                ++num;
                break;

            case 2:
                searchAndDelete(records, num);
                break;

            case 3:
                insertAfter(records, num);
                break;

            case 4:
                insertBefore(records, num);
                break;

            case 5:
                displayRecords(records, num);
                break;

            case 6:
                saveToFile(records, num);
                break;

            case 7:
                loadFromFile(records, num);
                break;

            case 8:
                // Task 5: Second Set of Records
                {
                    int numSecondSet;
                    StudentRecord* secondSet = enterSecondSet(records, num, numSecondSet);
                    num += numSecondSet;
                    delete[] secondSet;
                }
                break;

            case 9:
                // Task 6: Record Comparison and Merging
                {
                    int numSecondSet;
                    StudentRecord* secondSet = enterSecondSet(records, num, numSecondSet);
                    int mergedNum;
                    StudentRecord* mergedSet = mergeArrays(records, num, secondSet, numSecondSet, mergedNum);
                    compareAndDisplay(records, num, secondSet, numSecondSet);
                    delete[] secondSet;
                    delete[] mergedSet;
                }
                break;

            case 10:
                // Task 7: Sorting
                {
                    int sortBy;
                    cout << "Sort by (1 for ID, 2 for Name): ";
                    cin >> sortBy;
                    bool sortByStudentID = (sortBy == 1);
                    sortArray(records, num, sortByStudentID);
                }
                break;

            case 11:
                cout << "Exiting array manipulation menu.\n";
                break;

            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != 11);
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    int num = totalStudents();
    StudentRecord* records = new StudentRecord[num];

    float overallGPA = 0.0;

    for (int i = 0; i < num; ++i) {
        cout << "Enter the details for student " << i + 1 << ":\n";

        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, records[i].name);

        cout << "Enter your age: ";
        cin >> records[i].age;
        records[i].id = generateID();
        cout << "Enter your gender (1 for male, 0 for female): ";
        cin >> records[i].gender;

        if (records[i].gender) {
            cout << "Gender: Male\n";
        } else {
            cout << "Gender: Female\n";
        }

        records[i].gpa = gpaCalc(records[i]);
        overallGPA += records[i].gpa;
    }

    if (num > 0) {
        overallGPA /= num;
        cout << "The Overall GPA is " << overallGPA << endl;
    } else {
        cout << "No students entered. Overall GPA not calculated.\n";
    }

    arrayManipulationMenu(records, num);

    delete[] records; // Free dynamically allocated memory

    return 0;
}
