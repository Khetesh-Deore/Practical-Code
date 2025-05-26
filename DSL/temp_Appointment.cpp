#include <iostream>
using namespace std;

struct Appointment {
    int startTime; // using 24-hour format e.g. 9 for 9 AM
    bool booked;
    string name;
    Appointment* next;
};

// Create initial list of 1-hour slots between 9 to 17
Appointment* createSlots() {
    Appointment* head = nullptr;
    Appointment* tail = nullptr;

    for (int i = 9; i < 17; i++) {
        Appointment* newNode = new Appointment{i, false, "", nullptr};
        if (!head) head = newNode;
        else tail->next = newNode;
        tail = newNode;
    }
    return head;
}

// Display free slots
void displayFreeSlots(Appointment* head) {
    cout << "\nFree Slots:\n";
    bool anyFree = false;
    while (head) {
        if (!head->booked) {
            cout << head->startTime << ":00 - " << head->startTime + 1 << ":00\n";
            anyFree = true;
        }
        head = head->next;
    }
    if (!anyFree) cout << "No free slots available.\n";
}

// Book an appointment
void bookAppointment(Appointment* head) {
    int time;
    string name;
    cout << "\nEnter time to book (e.g., 9 for 9:00 AM): ";
    cin >> time;

    while (head) {
        if (head->startTime == time) {
            if (!head->booked) {
                cout << "Enter your name: ";
                cin.ignore();
                getline(cin, name);
                head->booked = true;
                head->name = name;
                cout << "Appointment booked successfully!\n";
                return;
            } else {
                cout << "Slot already booked!\n";
                return;
            }
        }
        head = head->next;
    }
    cout << "Invalid time slot.\n";
}

// Cancel an appointment
void cancelAppointment(Appointment* head) {
    int time;
    cout << "\nEnter time to cancel (e.g., 10 for 10:00 AM): ";
    cin >> time;

    while (head) {
        if (head->startTime == time) {
            if (head->booked) {
                head->booked = false;
                head->name = "";
                cout << "Appointment cancelled.\n";
                return;
            } else {
                cout << "This slot is not booked.\n";
                return;
            }
        }
        head = head->next;
    }
    cout << "Invalid time slot.\n";
}

// Display all appointments
void displayAppointments(Appointment* head) {
    cout << "\nAll Appointments:\n";
    while (head) {
        cout << head->startTime << ":00 - " << head->startTime + 1 << ":00 => ";
        if (head->booked)
            cout << "Booked by " << head->name << endl;
        else
            cout << "Free\n";
        head = head->next;
    }
}

// Sort by time (data swapping)
void sortByTime(Appointment* head) {
    for (Appointment* i = head; i; i = i->next) {
        for (Appointment* j = i->next; j; j = j->next) {
            if (i->startTime > j->startTime) {
                swap(i->startTime, j->startTime);
                swap(i->booked, j->booked);
                swap(i->name, j->name);
            }
        }
    }
    cout << "Sorted by time using data swapping.\n";
}

// Sort by time (pointer manipulation)
void sortByPointer(Appointment*& head) {
    if (!head || !head->next) return;

    for (Appointment* i = head; i->next; i = i->next) {
        for (Appointment* j = head; j->next; j = j->next) {
            if (j->startTime > j->next->startTime) {
                // Swap nodes
                Appointment* tmp = j->next;
                j->next = tmp->next;
                tmp->next = j;

                // Adjust head or previous node
                if (j == head)
                    head = tmp;
                else {
                    Appointment* prev = head;
                    while (prev->next != j)
                        prev = prev->next;
                    prev->next = tmp;
                }
                // Restart from beginning
                i = head;
                break;
            }
        }
    }
    cout << "Sorted by time using pointer manipulation.\n";
}

int main() {
    Appointment* head = createSlots();
    int choice;

    do {
        cout << "\n====== Appointment Management Menu ======\n";
        cout << "1. Display Free Slots\n";
        cout << "2. Book Appointment\n";
        cout << "3. Cancel Appointment\n";
        cout << "4. Display All Appointments\n";
        cout << "5. Sort by Time (Data Swapping)\n";
        cout << "6. Sort by Time (Pointer Manipulation)\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: displayFreeSlots(head); break;
            case 2: bookAppointment(head); break;
            case 3: cancelAppointment(head); break;
            case 4: displayAppointments(head); break;
            case 5: sortByTime(head); break;
            case 6: sortByPointer(head); break;
            case 0: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
