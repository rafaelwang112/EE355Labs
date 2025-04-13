#include <iostream>
#include <fstream>
using namespace std;

// Define the structure for a node in the doubly linked list
struct Node {
    int value;
    Node* next;
    Node* prev;

    Node (int data){
        value = data;
        next = nullptr;
        prev = nullptr;
    }
};

class DoublyLinkedList {
private:
    // 
    Node* head;
public:
    // Constructor initializes an empty list
    DoublyLinkedList(){
        head = nullptr;
    }

    // Destructor to free allocated memory
    ~DoublyLinkedList() {
        Node* current = head;
        Node* nextNode;

        while (current != nullptr) {
            nextNode = current->next;  
            delete current;            
            current = nextNode;       
        }

        head = nullptr;
    }

    // Function to add an element at the beginning of the list
    void addFirst(int data) {
        Node* current = new Node(data);
        current->next = head;
        if (head != nullptr) {
            head->prev = current;
        }
        head = current;
    }

    // Function to append an element at the end of the list
    void append(int data) {
        Node* newNode = new Node(data);
        if (head == nullptr) {
            head = newNode;
            return;
        }

        Node* current = head;
        while (current->next != nullptr){
            current = current->next;
        }
        current->next = newNode;
        newNode->prev = current;
    }

    // Function to insert an element at a specific position (0-indexed)
    void insert(int data, int pos) {
        if (pos == 0) {
            addFirst(data);
            return;
        }
    
        Node* newNode = new Node(data);
        Node* current = head;
        int count = 0;
    
        while (current != nullptr && count < pos) {
            current = current->next;
            count++;
        }
    
        if (current != nullptr) {
            newNode->next = current;
            newNode->prev = current->prev;
    
            if (current->prev != nullptr) {
                current->prev->next = newNode;
            }
            current->prev = newNode;
        } else {
            cout << "Position out of bounds. Inserting at the end." << endl;
            delete newNode; 
            append(data);
        }
    }
    
    

    // Function to delete the node at a specific index (0-indexed)
    void deleteAtIndex(int index) {
        // if the index is Invalid or the list is empty
        // cout << "Invalid index or empty list." << endl;
        if (head == nullptr){
            cout << "Invalid index or empty list." << endl;
            return;
        }
        
        // If the index is out of bounds
        // cout << "Index out of bounds." << endl;
        if (index < 0) {
            cout << "Index out of bounds." << endl;
            return;
        }
        
        Node* current = head;
        int count = 0;
        while (current != nullptr && count < index) {
            current = current->next;
            count++;
        }

        if (current != nullptr) {
            if (current->prev != nullptr) {
                current->prev->next = current->next;
            } else {
                head = current->next; 
            }

            if (current->next != nullptr) {
                current->next->prev = current->prev;
            }

            delete current;
        } else {
            cout << "Index out of bounds." << endl;
        }
    }

    // Function to search for an element in the list.
    // Returns a pointer to the node if found, otherwise returns nullptr.
    Node* search(int data) {
        Node* current = head;
        while (current != nullptr){
            if (current->value == data){
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    // Function to check whether the doubly linked list is circular using two pointers.
    // The list is considered circular if there is a cycle in the next pointers.
    bool isCircularTwoPointer() {
        Node* slow = head;
        Node* fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
    
            if (fast == slow) {
                return true; 
            }
        }
        return false; 
    }

    // Function to display the doubly linked list
    void display() {
        Node* current = head;
        cout << "Doubly Linked List: ";
        while (current != nullptr) {
            cout << current->value << " <-> ";
            current = current->next;
        }
        cout << "NULL" << endl;
    }
    
};

int main() {
    // Open input.txt file for reading
    std::ifstream infile("input_part2.txt");
    if (!infile) {
        std::cerr << "Error opening input.txt" << "\n";
        return 1;
    }
    
    // Redirect cin to read from input.txt
    cin.rdbuf(infile.rdbuf());

    int T;
    cin >> T;
    string command;
    DoublyLinkedList dll;
    
    // Process T commands from the input file
    for (int i = 0; i < T; i++){
        cin >> command;
        if (command == "addFirst") {
            int x;
            cin >> x;
            dll.addFirst(x);
        } else if (command == "append") {
            int x;
            cin >> x;
            dll.append(x);
        } else if (command == "insert") {
            int x, pos;
            cin >> x >> pos;
            dll.insert(x, pos);
        } else if (command == "deleteAtIndex") {
            int idx;
            cin >> idx;
            dll.deleteAtIndex(idx);
        } else if (command == "search") {
            int x;
            cin >> x;
            Node* found = dll.search(x);
            cout << (found ? "Found" : "Not Found") << "\n";
        } else if (command == "display") {
            dll.display();
        } else if (command == "isCircular") {
            cout << "Is the list circular (two-pointer check)? " 
                 << (dll.isCircularTwoPointer() ? "Yes" : "No") << "\n";
        }
    }
    return 0;
}