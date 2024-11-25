// Problem 1 Made BY: Marawan Mohamed Abd El-Hamid ID: 20230557
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
using namespace std;

class LabelGen {
protected:
    string prefix;
    int currentIndex;

public:
    
    LabelGen(const string& prefix, int startIndex)
        : prefix(prefix), currentIndex(startIndex) {}


    virtual string nextLabel() {
        return prefix + " " + to_string(currentIndex++);
    }

    virtual ~LabelGen() = default;
};

class FileLabelGen : public LabelGen {
private:
    ifstream labelFile;

public:
    FileLabelGen(const string& prefix, int startIndex, const string& fileName)
        : LabelGen(prefix, startIndex) {
        labelFile.open(fileName);
        if (!labelFile.is_open()) {
            throw runtime_error("Error: Unable to open file " + fileName);
        }
    }

    string nextLabel() override {
        string caption;
        if (getline(labelFile, caption)) {
            return LabelGen::nextLabel() + " " + caption;
        } else {
            return LabelGen::nextLabel() + " (No more captions)";
        }
    }

    ~FileLabelGen() {
        if (labelFile.is_open()) {
            labelFile.close();
        }
    }
};

int main() {
    try {
        cout << "Choose the type of Label Generator:" << endl;
        cout << "1. Basic Label Generator" << endl;
        cout << "2. File-based Label Generator" << endl;
        int choice;
        cin >> choice;

        if (choice == 1) {
            // basic gen >> doesnt require a file to run
            string prefix;
            int startIndex, count;
            cout << "Enter the prefix: ";
            cin >> prefix;
            cout << "Enter the starting index: ";
            cin >> startIndex;
            cout << "Enter the number of labels to generate: ";
            cin >> count;

            LabelGen generator(prefix, startIndex);
            cout << "Generated Labels:" << endl;
            for (int i = 0; i < count; i++) {
                cout << generator.nextLabel() << endl;
            }

        } else if (choice == 2) {
            // advanced gen >> the one that takes from the file ^^
            string prefix, fileName;
            int startIndex, count;
            cout << "Enter the prefix: ";
            cin >> prefix;
            cout << "Enter the starting index: ";
            cin >> startIndex;
            cout << "Enter the file name: ";
            cin >> fileName;
            cout << "Enter the number of labels to generate: ";
            cin >> count;

            FileLabelGen generator(prefix, startIndex, fileName);
            cout << "Generated Labels with Captions:" << endl;
            for (int i = 0; i < count; i++) {
                cout << generator.nextLabel() << endl;
            }

        } else {
            cout << "Invalid choice. Please restart the program." << endl;
        }

    } catch (const exception& ex) {
        cerr << "Error: " << ex.what() << endl;
    }

    return 0;
}