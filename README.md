# Data-Structure-Lab2

#include <iostream>
using namespace std;

// Structure to represent a passenger
struct Node {
    int id;        // Passenger ID
    Node* next;    // Pointer to the next node

    Node(int val) {
        id = val;
        next = NULL;
    }
};

// Linked List class for managing the passenger queue
class LinkedList {
private:
    Node* head;

public:
    // Constructor
    LinkedList() {
        head = NULL;
    }

    // Insert at beginning (VIP/emergency passenger)
    void insertAtBeginning(int id) {
        Node* newNode = new Node(id);
        newNode->next = head;
        head = newNode;
    }

    // Insert at end (normal passenger)
    void insertAtEnd(int id) {
        Node* newNode = new Node(id);
        if (head == NULL) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    // Insert at specific position (special booking)
    void insertAtPosition(int id, int pos) {
        Node* newNode = new Node(id);
        if (pos <= 1 || head == NULL) {
            insertAtBeginning(id);
            return;
        }

        Node* temp = head;
        int count = 1;

        while (temp != NULL && count < pos - 1) {
            temp = temp->next;
            count++;
        }

        if (temp == NULL) {
            cout << "Position out of bounds. Adding at end.\n";
            insertAtEnd(id);
            return;
        }

        newNode->next = temp->next;
        temp->next = newNode;
    }

    // Delete from beginning (passenger boards)
    void deleteFromBeginning() {
        if (head == NULL) {
            cout << "Queue is empty.\n";
            return;
        }
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    // Print the current queue
    void printQueue() {
        if (head == NULL) {
            cout << "Queue is empty.\n";
            return;
        }
        Node* temp = head;
        while (temp != NULL) {
            cout << temp->id;
            if (temp->next != NULL) {
                cout << " -> ";
            }
            temp = temp->next;
        }
        cout << endl;
    }
};

// Main function to simulate the BRT queue scenario
int main() {
    LinkedList queue;

    // Step 1: Add 3 normal passengers
    queue.insertAtEnd(101);
    queue.insertAtEnd(102);
    queue.insertAtEnd(103);
    cout << "Initial Queue after adding passengers:\n";
    queue.printQueue();

    // Step 2: Add emergency passenger at beginning
    queue.insertAtBeginning(999);
    cout << "After adding an emergency passenger at beginning:\n";
    queue.printQueue();

    // Step 3: Add special booking passenger at position 2
    queue.insertAtPosition(555, 2);
    cout << "After inserting special booking passenger at position 2:\n";
    queue.printQueue();

    // Step 4: First passenger boards (delete from beginning)
    queue.deleteFromBeginning();
    cout << "After first passenger boards (deletion):\n";
    queue.printQueue();

    return 0;
}
