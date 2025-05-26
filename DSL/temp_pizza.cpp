#include <iostream>
using namespace std;

#define MAX 5  // maximum number of orders

class PizzaParlor {
private:
    int orders[MAX];
    int front, rear;

public:
    PizzaParlor() {
        front = rear = -1;
    }

    // Check if queue is full
    bool isFull() {
        return (front == (rear + 1) % MAX);
    }

    // Check if queue is empty
    bool isEmpty() {
        return (front == -1);
    }

    // Place order
    void placeOrder(int orderId) {
        if (isFull()) {
            cout << "Sorry! All slots are full. Can't accept more orders.\n";
            return;
        }

        if (isEmpty()) {
            front = rear = 0;
        } else {
            rear = (rear + 1) % MAX;
        }

        orders[rear] = orderId;
        cout << "Order placed successfully! Order ID: " << orderId << endl;
    }

    // Serve order
    void serveOrder() {
        if (isEmpty()) {
            cout << "No orders to serve.\n";
            return;
        }

        cout << "Serving order ID: " << orders[front] << endl;

        if (front == rear) {
            // last order
            front = rear = -1;
        } else {
            front = (front + 1) % MAX;
        }
    }

    // Display all pending orders
    void displayOrders() {
        if (isEmpty()) {
            cout << "No pending orders.\n";
            return;
        }

        cout << "Pending Orders: ";
        int i = front;
        while (true) {
            cout << orders[i] << " ";
            if (i == rear) break;
            i = (i + 1) % MAX;
        }
        cout << endl;
    }
};

int main() {
    PizzaParlor parlor;
    int choice, orderId = 1001;  // starting order ID

    do {
        cout << "\n=== Pizza Parlor Menu ===\n";
        cout << "1. Place Order\n";
        cout << "2. Serve Order\n";
        cout << "3. Display Orders\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                parlor.placeOrder(orderId++);
                break;
            case 2:
                parlor.serveOrder();
                break;
            case 3:
                parlor.displayOrders();
                break;
            case 0:
                cout << "Thank you! Visit again.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
