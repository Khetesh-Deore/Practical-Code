/*A Dictionary using Hash table: A Dictionary stores key and value pairs 
Data: Set of (key, value) pairs, Keys are mapped to values, Keys must be 
comparable, Keys must be unique.
Standard Operations: Insert(key, value), Find(key), Delete(key)
Write a menu driven C++ program to provide above standard operations
on dictionaries
Write a menu driven C++ program to provide all the functions of a
dictionary (ADT) using hashing and handle collisions using chaining.*/

#include<iostream>
#include<string>
using namespace std;

#define SIZE 19

// Structure to store key-value pairs
struct ListNode {
    int key;
    string value;
    ListNode* next;
    ListNode(int k, string v) : key(k), value(v), next(nullptr) {}
};

class hashTable {
    ListNode* ht[SIZE];  // Array of pointers to linked lists

public:
    hashTable() {
        // Initialize each bucket to NULL (empty)
        for (int i = 0; i < SIZE; i++) {
            ht[i] = nullptr;
        }
        cout << "Hash Table is initialized and empty." << endl;
    }

    int hash(int key);
    void insert(int key, string value);
    void search(int key);
    void deleteKey(int key);
    void display();
};

// Hash function: Simple modulus-based hash function
int hashTable::hash(int key) {
    return key % SIZE;
}

// Insert key-value pair into hash table using chaining
void hashTable::insert(int key, string value) {
    int index = hash(key);
    ListNode* newNode = new ListNode(key, value);
    
    // Insert at the beginning of the linked list at this index
    if (ht[index] == nullptr) {
        ht[index] = newNode;
    } else {
        ListNode* temp = ht[index];
        while (temp->next != nullptr) {
            if (temp->key == key) {  // If key already exists, update value
                temp->value = value;
                delete newNode;  // Avoid creating a duplicate node
                cout << "Updated value of key " << key << " to " << value << endl;
                return;
            }
            temp = temp->next;
        }
        // Insert at the end of the list if the key was not found
        temp->next = newNode;
    }
    cout << "Inserted (" << key << ", " << value << ") into hash table." << endl;
}

// Search for a key in the hash table
void hashTable::search(int key) {
    int index = hash(key);
    ListNode* temp = ht[index];
    while (temp != nullptr) {
        if (temp->key == key) {
            cout << "Found key " << key << " with value: " << temp->value << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Key " << key << " not found!" << endl;
}

// Delete a key-value pair from the hash table
void hashTable::deleteKey(int key) {
    int index = hash(key);
    ListNode* temp = ht[index];
    ListNode* prev = nullptr;

    while (temp != nullptr) {
        if (temp->key == key) {
            if (prev == nullptr) {
                ht[index] = temp->next;  // Deleting the first node
            } else {
                prev->next = temp->next;  // Bypass the node to delete it
            }
            delete temp;
            cout << "Key " << key << " deleted from hash table." << endl;
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    cout << "Key " << key << " not found in hash table." << endl;
}

// Display the hash table
void hashTable::display() {
    cout << "Hash Table contents: " << endl;
    for (int i = 0; i < SIZE; i++) {
        if (ht[i] != nullptr) {
            cout << "Index " << i << ": ";
            ListNode* temp = ht[i];
            while (temp != nullptr) {
                cout << "(" << temp->key << ", " << temp->value << ") ";
                temp = temp->next;
            }
            cout << endl;
        }
    }
}

// Main function
int main() {
    hashTable HT;
    int choice, key;
    string value;

    do {
        cout << "\n-----Dictionary Operations using Hash Table-----" << endl;
        cout << "1. Insert key-value pair\n";
        cout << "2. Search for a key\n";
        cout << "3. Delete a key-value pair\n";
        cout << "4. Display the Hash Table\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: // Insert key-value pair
            cout << "Enter key: ";
            cin >> key;
            cout << "Enter value: ";
            cin >> value;
            HT.insert(key, value);
            break;

        case 2: // Search for a key
            cout << "Enter key to search: ";
            cin >> key;
            HT.search(key);
            break;

        case 3: // Delete a key-value pair
            cout << "Enter key to delete: ";
            cin >> key;
            HT.deleteKey(key);
            break;

        case 4: // Display the hash table
            HT.display();
            break;

        case 5: // Exit
            cout << "Exiting..." << endl;
            break;

        default:
            cout << "Invalid choice! Please try again." << endl;
            break;
        }
    } while (choice != 5);

    return 0;
}

