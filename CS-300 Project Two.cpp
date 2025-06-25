// CS-300 Project Two.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <vector>
#include <limits>

using namespace std;

string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
}

// define a structure to hold course information
struct Course {
    string courseID; // unique identifier
    string courseName;
    string prerequisites;
};

// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a course
    Node(Course aCourse) :
        Node() {
        course = aCourse;
    }
};
// Declare Binary Search Tree Class
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);
    Node* removeNode(Node* node, string courseId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PostOrder();
    void PreOrder();
    void Insert(Course course);
    Course Search(string courseId);
    void loadFromFile(const std::string& filename);
};

//Default constructor
BinarySearchTree::BinarySearchTree() {
    // Initialize housekeeping variable
    root = nullptr;
}

//Destructor
BinarySearchTree::~BinarySearchTree() {
    // Recurse from root deleting every node
    while (root != nullptr) {
        removeNode(root, root->course.courseID);
    }
}


 //Traverse the tree in order
void BinarySearchTree::InOrder() {
    // Call method that containts logic
    inOrder(root);
}


//Traverse the tree in post-order 
void BinarySearchTree::PostOrder() {
    // Call method that containts logic
    postOrder(root);
}


//Traverse the tree in pre-order

void BinarySearchTree::PreOrder() {
    // Call method that contains logic
    preOrder(root);
}



//Insert a course
void BinarySearchTree::Insert(Course course) {
    // Create new node for root
    if (root == nullptr) {
        root = new Node(course);
    }
    else {
        addNode(root, course);
    }
}
//Search for a course
Course BinarySearchTree::Search(string courseID) {

    Node* currentNode = root;

    while (currentNode != NULL) {
        // If current node matches, return it
        if (currentNode->course.courseID == courseID) {

            return currentNode->course;
        }
        // If course is smaller, traverse left subtree
        else if (courseID < currentNode->course.courseID) {

            currentNode = currentNode->left;
        }
        // Traverse right subtree
        else {

            currentNode = currentNode->right;
        }
    }
    Course course;
    return course;
}

//Method to add node
void BinarySearchTree::addNode(Node* node, Course course) {
    // If node is higher than course, add it to left subtree
    if (course.courseID.compare(node->course.courseID) < 0) {
        if (node->left == nullptr) {
            node->left = new Node(course);
        }
        // If left node exists, traverse down left subtree
        else {
            addNode(node->left, course);
        }
    }
    // If node is lower than course, add it to right subtree
    else {
        if (node->right == nullptr) {
            node->right = new Node(course);
        }
        // If right node exists, traverse down right subtree
        else {
            addNode(node->right, course);
        }
    }
}
void BinarySearchTree::inOrder(Node* node) {
    if (node != nullptr) {
        inOrder(node->left); // Traverse left side
        std::cout << node->course.courseID << ": " << node->course.courseName << endl;
        if (!node->course.prerequisites.empty()) {
            std::cout << " | Prerequisites: " << node->course.prerequisites;
        }
        std::cout << std::endl;

        inOrder(node->right); // Traverse right side
    }
}
void BinarySearchTree::postOrder(Node* node) {
    if (node != nullptr) {
        postOrder(node->left); // Left subtree
        postOrder(node->right); // Right subtree
        cout << node->course.courseID << ": " << node->course.courseName << "|" << endl;
    }
}

void BinarySearchTree::preOrder(Node* node) {
    if (node != nullptr) {
        std::cout << node->course.courseID << ": " << node->course.courseName << endl;
        preOrder(node->left); // Left subtree
        preOrder(node->right); // Right subtree
    }
}

Node* BinarySearchTree::removeNode(Node* node, string courseID) {

    if (node == nullptr) {
        return node;
    }
    if (courseID.compare(node->course.courseID) < 0) {
        node->left = removeNode(node->left, courseID);
    }
    else if (courseID.compare(node->course.courseID) > 0) {
        node->right = removeNode(node->right, courseID);
    }
    else {
        // No kids
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        // No kids
        else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        // Two children
        Node* temp = node->right;
        while (temp && temp->left != nullptr) {
            temp = temp->left;
        }

        node->course = temp->course;
        node->right = removeNode(node->right, temp->course.courseID);
    }
    return node;
}

//Display course information
void displayCourse(Course course) {
    cout << course.courseID << ": " << course.courseName << " | " << endl;
    if (!course.prerequisites.empty()) {
        cout << " | Prerequisites: " << course.prerequisites;
    }
    else {
        cout << " | Prerequisites: None";
    }
    cout << endl;
    return;
}
//Load data from file into BST
void BinarySearchTree::loadFromFile(const string& filename) {

    ifstream inputFile(filename); 
    if (!inputFile) { //Error handling
        cout << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        vector<string> tokens;
        size_t start = 0, end;

        while ((end = line.find(',', start)) != string::npos) { //CSV file seperated by commas
            tokens.push_back(trim(line.substr(start, end - start)));
            start = end + 1;
        }
        tokens.push_back(trim(line.substr(start)));

        if (tokens.size() < 2) continue;

        Course course;
        course.courseID = tokens[0];
        course.courseName = tokens[1];
        course.prerequisites = "";

        for (size_t i = 2; i < tokens.size(); ++i) {
            if (!tokens[i].empty()) {
                if (!course.prerequisites.empty())
                    course.prerequisites += ", ";
                course.prerequisites += tokens[i];
            }
        }

        Insert(course); //Add course to tree
    }

    inputFile.close();
}
//Method for opening file
string promptForFilename() {
    string filename;

    while (true) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\n" << "Enter the filename: " << flush;
        getline(cin >> ws, filename);

        cout << "Trying to open: [" << filename << "]" << endl;

        ifstream inputFile(filename);
        if (inputFile) {
            inputFile.close();
            cout << "File opened successfully." << endl;
            return filename;
        }
        else {
            cout << "File not found or cannot be opened. Try again.\n";
        }
    }
}
//Main method
int main(int argc, char* argv[]) {

    //Create BST structure
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Course course;
    cout << "\n" << "Welcome to the course planner." << endl;
    bool dataLoaded = false; 

    int choice = 0;
    while (choice != 9) { //Loop to handle menu options
        cout << "\nChoose option.\n" << endl;
        cout << "  1. Load Data Structure" << endl;
        cout << "  2. Print Course List" << endl;
        cout << "  3. Print Course" << endl;
        cout << "  9. Exit" << endl;
        cout << "\nEnter choice: ";

        if (!(cin >> choice)) {
            // Handle non-integer input
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (choice != 1 && choice != 2 && choice != 3 && choice != 9) {
            cout << "Invalid choice. Please enter valid option.\n";
            continue;
        }

        switch (choice) {

        case 1: {

            // Complete the method call to load the courses
            string filename = promptForFilename();
            bst->loadFromFile(filename); //Call method to load BST
            dataLoaded = true;
            break;
        }

        case 2:
            if (!dataLoaded) { //Check if data is loaded first
                cout << "Please load course file first (Option 1)." << endl;
                break;
            }
            cout << "Here is a sample schedule:" << endl;
            bst->InOrder(); //Call method to print alphabetical list
            cout << endl;
            break;

        case 3:
            if (!dataLoaded) { // Check if data is loaded first
                cout << "Please load course file first (Option 1)." << endl;
                break;
            }
            cout << "\n" << "What course do you want to know more about?: ";
            string courseKey;
            getline(cin >> ws, courseKey);

            course = bst->Search(courseKey); //Call method to search for course

            cout << "Search completed, courseID = " << course.courseID << "\n" << endl;

            if (!course.courseID.empty()) {
                displayCourse(course); //DIsplay course if found
            }
            else {
                cout << "Course ID " << " not found." << endl;
            }
            break;
        }
    }

    cout << "\n" << "Good bye." << endl;

    return 0;
}