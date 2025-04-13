#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
using namespace std;

// Define the structure for a node in the linked list
struct Node {
    int data;
    Node* next;

    Node (int integer){
        data = integer;
        next = nullptr;
    }
};

// LinkedList class encapsulates the head pointer and various operations
class LinkedList {
    private:
        Node* head;
    public:
    // Constructor initializes an empty list
    LinkedList(){
        head = nullptr;
    }

    // Destructor to free allocated memory
    ~LinkedList(){
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
        Node* newNode = new Node(data);     // Create a new node with value {data}
        newNode->next = head;   // point the new node to the first element in the list 
        head = newNode;     // Have the new node be the head node 
    }

    // Function to append an element at the end of the list
    void append(int data) {
        Node* newNode = new Node(data);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        Node* lastNode = head;  // Initialize the tracker node be the head node 
        while (lastNode->next != nullptr){      // while lastNode is not the last element
            lastNode = lastNode->next;  // update the lastNode to be the Node it points to
        }
        lastNode->next = newNode;   // update the lastNode to point to the new element
    }

    // Function to insert an element at a specific position (0-indexed)
    void insert(int data, int pos) {
        int count = 0;  // have an integer to track the iteration 
        Node* newNode = new Node(data);
        Node* lastNode = head;
        
        if (pos == 0) {
            addFirst(data);
            return;
        }

        // Traverse the list to find the node before the desired position
        while (lastNode != nullptr && count < pos - 1) {
            lastNode = lastNode->next;
            count++;
        }

        if (lastNode == nullptr) {
            append(data); // Just append silently
            delete newNode; // Avoid memory leak from earlier allocation
            return;
        }        

        newNode->next = lastNode->next;
        lastNode->next = newNode;
    }

    // Function to delete the first occurrence of a node with the given value
    void deleteNode(int data) {
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }

        if (head->data == data) {
            Node* temp = head;
            head = head->next;  // Move head to the next node
            delete temp;        // Delete the old head
            return;
        }

        Node* lastNode = head;

        while (lastNode->next != nullptr && lastNode->next->data != data){
            lastNode = lastNode->next;
        }

        if(lastNode->next == nullptr){
            cout << "Value " << data << " not found in the list." << endl;
            return;
        }

        Node* temp = lastNode->next;
        lastNode->next = lastNode->next->next;  // Remove the node from the list
        delete temp;  // Delete the node
        
    }

    // Function to search for an element in the list.
    // Returns a pointer to the node if found, otherwise returns nullptr.
    Node* search(int data) {
        Node* found = nullptr;
        Node* lastNode = head;
        while (lastNode != nullptr && lastNode->data != data){
            lastNode = lastNode->next;
        }

        if (lastNode == nullptr) return found;

        found = lastNode;
        return found; 
    }

    // Function to display the linked list
    void display() {
        Node* current = head;
        cout << "Linked List: ";
        while (current != nullptr) {
            // Uncomment the line below to display the data
            // Here we assume the data have one element of type int and one element of pointer type
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "NULL" << endl;
    }

        // Function to remove and return the first element of the list
    int pop() {
        if (head == nullptr) {
            throw runtime_error("List is empty. Cannot pop.");
        }
        // 
        Node* temp = head; 
        int val = temp->data;  // Save value first
        head = head->next;     // Move head forward
        delete temp;           // Then delete the old head
        return val;
    }
};

int main(){

    // Open the input file "input.txt"
    ifstream infile("input.txt");
    if (!infile) {
        cerr << "Error opening input.txt" << "\n";
        return 1;
    }

    // Redirect cin to use the file stream, but keep cout as standard output.
    cin.rdbuf(infile.rdbuf());

    int T;
    cin >> T;
    string command;
    LinkedList list;
    
    // Process T commands from input
    for (int i = 0; i < T; i++){
        cin >> command;
        if (command == "addFirst") {
            int x;
            cin >> x;
            list.addFirst(x);
        } else if (command == "append") {
            int x;
            cin >> x;
            list.append(x);
        } else if (command == "insert") {
            int x, pos;
            cin >> x >> pos;
            list.insert(x, pos);
        } else if (command == "delete") {
            int x;
            cin >> x;
            list.deleteNode(x);
        } else if (command == "pop") {
            try {
                int popped = list.pop();
                cout << "Popped: " << popped << "\n";
            } catch (const runtime_error &e) {
                cout << e.what() << "\n";
            }
        } else if (command == "search") {
            int x;
            cin >> x;
            Node* found = list.search(x);
            cout << (found ? "Found" : "Not Found") << "\n";
        } else if (command == "display") {
            list.display();
        }
    }
    return 0;
}