#include <iostream>
using namespace std;

// Node structure for doubly linked list
struct Patient {
    int patientID;
    Patient* prev;
    Patient* next;
    
    Patient(int id) {
        patientID = id;
        prev = nullptr;
        next = nullptr;
    }
};

class ERQueue {
private:
    Patient* head;
    Patient* tail;
    int length;

public:
    ERQueue() {
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    // 1. Add a new patient at the beginning of the list
    void insertAtBeginning(int patientID) {
        Patient* newPatient = new Patient(patientID);
        
        if (head == nullptr) { // Empty list
            head = newPatient;
            tail = newPatient;
        } else {
            newPatient->next = head;
            head->prev = newPatient;
            head = newPatient;
        }
        length++;
        cout << "Patient " << patientID << " added at beginning (critical)\n";
    }

    // 2. Add a new patient at the end of the list
    void insertAtEnd(int patientID) {
        Patient* newPatient = new Patient(patientID);
        
        if (tail == nullptr) { // Empty list
            head = newPatient;
            tail = newPatient;
        } else {
            tail->next = newPatient;
            newPatient->prev = tail;
            tail = newPatient;
        }
        length++;
        cout << "Patient " << patientID << " added at end (walk-in)\n";
    }

    // 3. Add a new patient at a specific position (1-based index)
    void insertAtPosition(int patientID, int position) {
        if (position < 1) {
            cout << "Invalid position! Position must be >= 1\n";
            return;
        }
        
        if (position == 1) {
            insertAtBeginning(patientID);
            return;
        }
        
        if (position > length) {
            cout << "Position " << position << " exceeds list length. Adding at end.\n";
            insertAtEnd(patientID);
            return;
        }
        
        Patient* newPatient = new Patient(patientID);
        Patient* current = head;
        
        // Traverse to the position before where we want to insert
        for (int i = 1; i < position - 1; i++) {
            current = current->next;
        }
        
        // Insert new node between current and current->next
        newPatient->next = current->next;
        newPatient->prev = current;
        
        if (current->next != nullptr) {
            current->next->prev = newPatient;
        }
        current->next = newPatient;
        
        // Update tail if inserting at the end
        if (newPatient->next == nullptr) {
            tail = newPatient;
        }
        
        length++;
        cout << "Patient " << patientID << " inserted at position " << position << "\n";
    }

    // 4. Remove a patient from the beginning of the list
    void deleteFromBeginning() {
        if (head == nullptr) {
            cout << "Queue is empty! No patient to remove.\n";
            return;
        }
        
        Patient* temp = head;
        cout << "Patient " << temp->patientID << " treated and removed from beginning\n";
        
        if (head == tail) { // Only one node
            head = nullptr;
            tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        
        delete temp;
        length--;
    }

    // Utility function to display the list from head to tail
    void displayForward() {
        if (head == nullptr) {
            cout << "ER Queue is empty!\n";
            return;
        }
        
        Patient* current = head;
        cout << "Head -> ";
        while (current != nullptr) {
            cout << "[" << current->patientID << "]";
            if (current->next != nullptr) {
                cout << " <-> ";
            }
            current = current->next;
        }
        cout << " <- Tail\n";
    }

    // Utility function to display the list from tail to head
    void displayBackward() {
        if (tail == nullptr) {
            cout << "ER Queue is empty!\n";
            return;
        }
        
        Patient* current = tail;
        cout << "Tail -> ";
        while (current != nullptr) {
            cout << "[" << current->patientID << "]";
            if (current->prev != nullptr) {
                cout << " <-> ";
            }
            current = current->prev;
        }
        cout << " <- Head\n";
    }

    // Get head patient ID
    int getHeadID() {
        return (head != nullptr) ? head->patientID : -1;
    }

    // Get tail patient ID
    int getTailID() {
        return (tail != nullptr) ? tail->patientID : -1;
    }

    // Get current length
    int getLength() {
        return length;
    }
};

// Main function for testing
int main() {
    ERQueue erQueue;
    
    // Test the operations
    erQueue.insertAtEnd(101);
    erQueue.insertAtEnd(102);
    erQueue.insertAtBeginning(200);
    erQueue.insertAtPosition(150, 2);
    erQueue.deleteFromBeginning();
    erQueue.insertAtEnd(300);
    
    cout << "\n=== Final Results ===\n";
    cout << "(a) Head patient ID: " << erQueue.getHeadID() << endl;
    cout << "(b) Tail patient ID: " << erQueue.getTailID() << endl;
    
    cout << "(c) Forward traversal: ";
    erQueue.displayForward();
    
    cout << "(d) Backward traversal: ";
    erQueue.displayBackward();
    
    return 0;
}