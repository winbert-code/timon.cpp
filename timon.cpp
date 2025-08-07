#include <iostream>
#include <string>
#include <direct.h> 
#include <filesystem> 
#include <vector>

namespace fs = std::filesystem;
using namespace std;

// Function prototypes
void mainMenu();
void listFiles();
void createDirectory();
void changeDirectory();

int main() {
    mainMenu();
    return 0;
}

void mainMenu() {
    int choice;
    do {
        cout << "\n--- Directory Management System ---\n";
        cout << "[1] List Files\n";
        cout << "[2] Create Directory\n";
        cout << "[3] Change Directory\n";
        cout << "[4] Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                listFiles();
                break;
            case 2:
                createDirectory();
                break;
            case 3:
                changeDirectory();
                break;
            case 4:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
}

void listFiles() {
    int option;
    cout << "\n--- List Files ---\n";
    cout << "[1] List All Files\n";
    cout << "[2] List Files by Extension\n";
    cout << "[3] List Files by Pattern\n";
    cout << "Enter your choice: ";
    cin >> option;

    string extension, pattern;
    switch (option) {
        case 1:
            cout << "Listing all files in the current directory:\n";
            for (const auto& entry : fs::directory_iterator(fs::current_path())) {
                cout << entry.path().filename().string() << endl;
            }
            break;
        case 2:
            cout << "Enter file extension (e.g., .txt): ";
            cin >> extension;
            cout << "Listing files with extension " << extension << ":\n";
            for (const auto& entry : fs::directory_iterator(fs::current_path())) {
                if (entry.path().extension() == extension) {
                    cout << entry.path().filename().string() << endl;
                }
            }
            break;
        case 3:
            cout << "Enter file pattern (e.g., moha*.*): ";
            cin >> pattern;
            cout << "Listing files matching pattern " << pattern << ":\n";
            for (const auto& entry : fs::directory_iterator(fs::current_path())) {
                if (entry.path().filename().string().find(pattern) != string::npos) {
                    cout << entry.path().filename().string() << endl;
                }
            }
            break;
        default:
            cout << "Invalid option.\n";
    }
}

void createDirectory() {
    string dirName;
    cout << "Enter the name of the directory to create: ";
    cin >> dirName;

    if (!fs::exists(dirName)) {
        fs::create_directory(dirName);
        cout << "Directory '" << dirName << "' created successfully.\n";
    } else {
        cout << "Error: Directory '" << dirName << "' already exists.\n";
    }
}

void changeDirectory() {
    string newDir;
    cout << "Enter the path of the directory to change to: ";
    cin >> newDir;

    if (fs::exists(newDir) && fs::is_directory(newDir)) {
        fs::current_path(newDir);
        cout << "Changed working directory to: " << fs::current_path() << endl;
    } else {
        cout << "Error: Directory does not exist or is not a valid directory.\n";
    }
}