#include <iostream>
using namespace std;

// Node structure
struct CLLNode {
    int data;
    CLLNode* next;

    CLLNode(int val) : data(val), next(nullptr) {}
};

// Circular Linked List class
class CircularLinkedList {
private:
    CLLNode* head;

public:
    CircularLinkedList() : head(nullptr) {}

    // Insert at the end (or create first node)
    void insert(int val) {
        CLLNode* newNode = new CLLNode(val);
        if (!head) {
            head = newNode;
            head->next = head; // Circular link
            return;
        }

        CLLNode* temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = head;
    }

    // Remove first occurrence of val
    void remove(int val) {
        if (!head) {
            cout << "List is empty.\n";
            return;
        }

        CLLNode* curr = head;
        CLLNode* prev = nullptr;

        do {
            if (curr->data == val) {
                if (curr == head) {
                    // Only one node
                    if (head->next == head) {
                        delete head;
                        head = nullptr;
                        return;
                    }
                    // More than one node
                    CLLNode* last = head;
                    while (last->next != head) {
                        last = last->next;
                    }
                    head = head->next;
                    last->next = head;
                    delete curr;
                    return;
                } else {
                    prev->next = curr->next;
                    delete curr;
                    return;
                }
            }
            prev = curr;
            curr = curr->next;
        } while (curr != head);

        cout << "Value not found.\n";
    }

    // Search for a value
    bool search(int val) {
        if (!head) return false;
        CLLNode* temp = head;

        do {
            if (temp->data == val)
                return true;
            temp = temp->next;
        } while (temp != head);

        return false;
    }

    // Print the entire list
    void printList() {
        if (!head) {
            cout << "List is empty.\n";
            return;
        }

        CLLNode* temp = head;
        cout << "Circular List: ";
        do {
            cout << temp->data << " ";
            temp = temp->next;
        } while (temp != head);
        cout << endl;
    }

    // Destructor to free memory
    ~CircularLinkedList() {
        if (!head) return;

        CLLNode* curr = head->next;
        while (curr != head) {
            CLLNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
        delete head;
    }
};

//Test case
int main() {
    CircularLinkedList cll;

    cll.insert(10);
    cll.insert(20);
    cll.insert(30);
    cll.insert(40);
    cll.printList(); 

    cout << "Search 30: " << (cll.search(30) ? "Found" : "Not Found") << endl;
    cout << "Search 50: " << (cll.search(50) ? "Found" : "Not Found") << endl;

    cll.remove(10); // Removing head
    cll.printList();

    cll.remove(30); // Removing middle
    cll.printList(); 

    cll.remove(50); 
    cll.printList();

    return 0;
}

