//============================================================================
// Name        : coursePlanner.cpp
// Author      : Brian Dell Blackman
// Version     : 1.0
// Copyright   : Copyright � 2023 SNHU COCE
// Description : Project Two
//============================================================================
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

class Course {
public:
    string id;
    string name;
    string prerequisites;
    string userInput;
};

//Add Course to Vector
void addCourseToVector(vector<Course>& courseVector, const Course& course) {
    courseVector.push_back(course);
}

// Create Course Object
Course createCourseObject(const vector <string>& courseDetails) {
    Course course;
    course.id = courseDetails[0];
    course.name = courseDetails[1];
    course.prerequisites = courseDetails[2];
    return course;
}

//Reads File
void readCourseInformation(const string& fileName, vector<Course>& courseVector) {
    ifstream file(fileName);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            vector<string> courseDetails;
            string detail;
            while (getline(iss, detail, ',')) {
                courseDetails.push_back(detail);
            }

            if (courseDetails.size() != 3) {
                cerr << "Error: Incorrect file format" << endl;
                continue;
            }

            Course course = createCourseObject(courseDetails);
            addCourseToVector(courseVector, course);
        }
    }

    else {
        cout << "File Did Not Open." << endl;
    }

    

    file.close();
    cout << "Data loaded successfully." << endl;
    cout << endl;
}

//Prints Single Course Details
void printCourseDetails(const Course& course) {
    cout << endl;
    cout << "Course ID: " << course.id << endl;
    cout << "Course Name: " << course.name << endl;
    cout << "Prerequisites: " << course.prerequisites << endl;
    cout << endl;
}

//Search Vector for Course Using Course Id
void searchCourse(const vector<Course>& courseVector, const string& searchTerm) {
    for (const auto& course : courseVector) {
        if (course.id == searchTerm || course.name.find(searchTerm) != string::npos) {
            printCourseDetails(course);
            
        }
    }
}

//Print All Courses In Alphanumeric Order
void printSortedCoursesVector(const vector<Course>& courseVector) {
    if (courseVector.empty()) {
        cout << "Data not loaded. Please load the data first." << endl;
        return;
    }

    vector<Course> sortedCourses = courseVector;
    for (int i = 0; i < sortedCourses.size() - 1; i++) {
        int j = i;
        while (j > 0 && sortedCourses[j].id < sortedCourses[j - 1].id) {
            Course temp = sortedCourses[j];
            sortedCourses[j] = sortedCourses[j - 1];
            sortedCourses[j - 1] = temp;
            --j;

        }
    }

    cout << endl;
    cout << "Alphanumeric Ordered list:" << endl;
    cout << endl;
    for (int i = 0; i < sortedCourses.size(); i++) {
        cout << sortedCourses[i].id << ", ";
        cout << sortedCourses[i].name << endl;
    }

    cout << endl;

}

//Prints Menu
void displayMenu() {
    cout << "Menu:" << endl;
    cout << "1. Load file data into data structure" << endl;
    cout << "2. Print alphanumerically ordered list of all Computer Science courses" << endl;
    cout << "3. Print course title and prerequisites for a specific course" << endl;
    cout << "9. Exit" << endl;
    cout << endl;
}

//Call To Load Data File
void loadData(vector<Course>& courseVector) {

    readCourseInformation("CS 300 ABCU_Advising_Program_Input.txt", courseVector);
}

//Call To Print Sorted List
void printSortedCourses(const vector<Course>& courseVector) {
    printSortedCoursesVector(courseVector);
}

//Call To Print Single Course Details
void printCourseDetails(const std::vector<Course>& courseVector) {
    if (courseVector.empty()) {
        cout << "Data not loaded. Please load the data first." << endl;
        return;
    }

    cout << "Enter course number:" << endl;
    string courseNumber;
    cin >> courseNumber;
    

    bool found = false;
    for (const auto& course : courseVector) {
        if (course.id == courseNumber) {
            printCourseDetails(course);
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Course not found." << endl;
    }
}
//Main Method
int main() {
    vector<Course> courseVector;
    int choice;

    //Runs Menu Selection
    while (true) {
        displayMenu();
        cout << "Enter your choice:" << endl;
        cin >> choice;
        cout << endl;

        switch (choice) {
        case 1:
            loadData(courseVector);
            break;
        case 2:
            printSortedCourses(courseVector);
            break;
        case 3:
            printCourseDetails(courseVector);
            break;
        case 9:
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
