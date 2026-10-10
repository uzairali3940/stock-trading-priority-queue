
#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct OrderNode {
    int orderID;
    string investorName;
    string stockSymbol;
    string orderType;
    int quantity;
    int priority;
    OrderNode* next;
};

class PriorityQueue {
private:
    OrderNode* front;
    OrderNode* rear;
    int count;

public:
    PriorityQueue() {
        front = nullptr;
        rear = nullptr;
        count = 0;
    }

    // Add order according to priority
    void Add(OrderNode* order) {
        order->next = nullptr;

        if (front == nullptr) {
            front = rear = order;
        }
        else if (order->priority < front->priority) {
            order->next = front;
            front = order;
        }
        else {
            OrderNode* current = front;

            while (current->next != nullptr &&
                   current->next->priority <= order->priority) {
                current = current->next;
            }

            order->next = current->next;
            current->next = order;

            if (order->next == nullptr) {
                rear = order;
            }
        }

        count++;
    }

    // Process highest-priority order
    OrderNode* Remove() {
        if (front == nullptr) {
            return nullptr;
        }

        OrderNode* order = front;
        front = front->next;

        if (front == nullptr) {
            rear = nullptr;
        }

        order->next = nullptr;
        count--;

        return order;
    }

    bool IsEmpty() {
        return front == nullptr;
    }

    bool IsNotEmpty() {
        return front != nullptr;
    }

    // Display all pending orders
    void PrintQueue() {
        if (IsEmpty()) {
            cout << "No pending stock orders.\n";
            return;
        }

        OrderNode* current = front;

        while (current != nullptr) {
            cout << "\nOrder ID: " << current->orderID;
            cout << "\nInvestor: " << current->investorName;
            cout << "\nStock Symbol: " << current->stockSymbol;
            cout << "\nOrder Type: " << current->orderType;
            cout << "\nQuantity: " << current->quantity;
            cout << "\nPriority: " << current->priority;
            cout << "\n-----------------------------\n";

            current = current->next;
        }
    }

    ~PriorityQueue() {
        while (front != nullptr) {
            OrderNode* temp = front;
            front = front->next;
            delete temp;
        }

        rear = nullptr;
    }
};

int main() {
    PriorityQueue orders;
    int choice;
    int nextOrderID = 1;

    do {
        cout << "\n===== Stock Trading Simulator =====\n";
        cout << "1. Add Stock Order\n";
        cout << "2. Process Highest Priority Order\n";
        cout << "3. Display All Orders\n";
        cout << "4. Check Queue Status\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                OrderNode* order = new OrderNode;

                order->orderID = nextOrderID++;

                cout << "Enter Investor Name: ";
                getline(cin >> ws, order->investorName);

                cout << "Enter Stock Symbol: ";
                cin >> order->stockSymbol;

                cout << "Enter Order Type (Buy/Sell): ";
                cin >> order->orderType;

                if (order->orderType != "Buy" &&
                    order->orderType != "Sell" &&
                    order->orderType != "buy" &&
                    order->orderType != "sell") {
                    cout << "Invalid order type.\n";
                    delete order;
                    break;
                }

                cout << "Enter Quantity: ";
                cin >> order->quantity;

                if (cin.fail() || order->quantity <= 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Quantity must be a positive number.\n";
                    delete order;
                    break;
                }

                cout << "Enter Priority (1=Urgent, 2=Regular, 3=Low): ";
                cin >> order->priority;

                if (cin.fail() ||
                    order->priority < 1 ||
                    order->priority > 3) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid priority.\n";
                    delete order;
                    break;
                }

                orders.Add(order);
                cout << "Stock order added successfully!\n";
                break;
            }

            case 2: {
                OrderNode* processed = orders.Remove();

                if (processed == nullptr) {
                    cout << "No orders available to process.\n";
                }
                else {
                    cout << "\nOrder Processed Successfully!\n";
                    cout << "Order ID: " << processed->orderID << '\n';
                    cout << "Investor: " << processed->investorName << '\n';
                    cout << "Stock: " << processed->stockSymbol << '\n';
                    cout << "Type: " << processed->orderType << '\n';
                    cout << "Quantity: " << processed->quantity << '\n';
                    cout << "Priority: " << processed->priority << '\n';

                    delete processed;
                }
                break;
            }

            case 3:
                cout << "\n===== Pending Stock Orders =====\n";
                orders.PrintQueue();
                break;

            case 4:
                if (orders.IsEmpty()) {
                    cout << "Queue Status: Empty\n";
                }
                else if (orders.IsNotEmpty()) {
                    cout << "Queue Status: Not Empty\n";
                }
                break;

            case 5:
                cout << "Exiting Stock Trading Simulator.\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}

