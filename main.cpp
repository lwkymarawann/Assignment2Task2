// PROBLEM 4 MADE BY: Marawan Mohamed Abd El-Hamid ID: 20230557
#include <iostream>
#include <string>
using namespace std;

template <typename T>
class Set {
private:
    T* items;
    int capacity;
    int size;

    int findItemIndex(const T& item) const {
        for (int i = 0; i < size; i++) {
            if (items[i] == item) {
                return i;
            }
        }
        return -1;
    }

public:
    Set(int capacity = 100) : capacity(capacity), size(0) {
        items = new T[capacity];
    }

    ~Set() {
        delete[] items;
    }

    void add(const T& item) {
        if (findItemIndex(item) == -1 && size < capacity) {
            items[size++] = item;
        }
    }

    void remove(const T& item) {
        int index = findItemIndex(item);
        if (index != -1) {
            for (int i = index; i < size - 1; i++) {
                items[i] = items[i + 1];
            }
            size--;
        }
    }

    int count() const {
        return size;
    }

    bool contains(const T& item) const {
        return findItemIndex(item) != -1;
    }

    T* toArray() const {
        T* result = new T[size];
        for (int i = 0; i < size; i++) {
            result[i] = items[i];
        }
        return result;
    }
};

int main() {
    int choice;
    do {
        cout << "\n#######################################\n";
        cout << "                SET MENU         \n";
        cout << "#######################################\n";
        cout << "Choose data type for the set:\n";
        cout << "1. Integers\n";
        cout << "2. Strings\n";
        cout << "3. Exit\n";
        cout << "#######################################\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cout << "_______________________________________\n";

        if (choice == 1) {
            Set<int> intSet;
            int intChoice, value;
            do {
                cout << "\n#######################################\n";
                cout << "            INTEGER SET MENU       \n";
                cout << "#######################################\n";
                cout << "1. Add an item\n";
                cout << "2. Remove an item\n";
                cout << "3. Count items\n";
                cout << "4. Check membership\n";
                cout << "5. Print all items\n";
                cout << "6. Back\n";
                cout << "#######################################\n";
                cout << "Enter your choice: ";
                cin >> intChoice;
                cout << "_______________________________________\n";

                if (intChoice == 1) {
                    cout << "Enter value to add: ";
                    cin >> value;
                    intSet.add(value);
                    cout << "*** Item added successfully! ***\n";
                } else if (intChoice == 2) {
                    cout << "Enter value to remove: ";
                    cin >> value;
                    intSet.remove(value);
                    cout << "*** Item removed successfully (if it existed)! ***\n";
                } else if (intChoice == 3) {
                    cout << "*** Number of items in the set: " << intSet.count() << " ***\n";
                } else if (intChoice == 4) {
                    cout << "Enter value to check: ";
                    cin >> value;
                    cout << "*** " << (intSet.contains(value) ? "Item exists in the set." : "Item does not exist in the set.") << " ***\n";
                } else if (intChoice == 5) {
                    int* array = intSet.toArray();
                    cout << "*** Items in the set: ";
                    for (int i = 0; i < intSet.count(); i++) {
                        cout << array[i] << " ";
                    }
                    cout << "***\n";
                    delete[] array;
                }
                cout << "_______________________________________\n";
            } while (intChoice != 6);

        } else if (choice == 2) {
            Set<string> stringSet;
            int stringChoice;
            string value;
            do {
                cout << "\n#######################################\n";
                cout << "            STRING SET MENU        \n";
                cout << "#######################################\n";
                cout << "1. Add an item\n";
                cout << "2. Remove an item\n";
                cout << "3. Count items\n";
                cout << "4. Check membership\n";
                cout << "5. Print all items\n";
                cout << "6. Back\n";
                cout << "#######################################\n";
                cout << "Enter your choice: ";
                cin >> stringChoice;
                cout << "_______________________________________\n";

                if (stringChoice == 1) {
                    cout << "Enter value to add: ";
                    cin >> value;
                    stringSet.add(value);
                    cout << "*** Item added successfully! ***\n";
                } else if (stringChoice == 2) {
                    cout << "Enter value to remove: ";
                    cin >> value;
                    stringSet.remove(value);
                    cout << "*** Item removed successfully (if it existed)! ***\n";
                } else if (stringChoice == 3) {
                    cout << "*** Number of items in the set: " << stringSet.count() << " ***\n";
                } else if (stringChoice == 4) {
                    cout << "Enter value to check: ";
                    cin >> value;
                    cout << "*** " << (stringSet.contains(value) ? "Item exists in the set." : "Item does not exist in the set.") << " ***\n";
                } else if (stringChoice == 5) {
                    string* array = stringSet.toArray();
                    cout << "*** Items in the set: ";
                    for (int i = 0; i < stringSet.count(); i++) {
                        cout << array[i] << " ";
                    }
                    cout << "***\n";
                    delete[] array;
                }
                cout << "_______________________________________\n";
            } while (stringChoice != 6);
        }
    } while (choice != 3);



    return 0;
}
