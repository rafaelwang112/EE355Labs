#include <iostream>
#include <fstream>

using namespace std;

// Define the structure for a node in the circular linked list
struct Node {
    int data; 
    Node* next;
    Node(int integer) : data(integer), next(nullptr){}

};

class CircularQueue {
private:
   Node* tail;
   int count = 0;

public:
    // Constructor initializes an empty queue
    CircularQueue(){
        tail = nullptr;
    }

    // Destructor to free allocated memory
    ~CircularQueue() {
        if (tail == nullptr) return;
    
        Node* current = tail->next;  
        tail->next = nullptr;        
    
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    
        tail = nullptr;
        count = 0;
    }
    
    

    // Function to check if the queue is empty
    bool isEmpty() { 
        if (count == 0)
            return true;
        return false;
    }

    // Function to check if the queue is full
    bool isFull() {
        // Max capacity = 8 elements
        if (count >= 8){
            return true;
        }
        return false;
    }

    // Function to add an element to the end of the queue (enqueue)
    void enqueue(int data) {
        if(isFull()){
            cout << "Queue is full. Cannot enqueue " << data << "." << endl;
            return;
        }
    
        Node* newNode = new Node(data);
        if(isEmpty()){
            tail = newNode;
            newNode->next = newNode;
        } else {
            newNode->next = tail->next;
            tail->next = newNode;
            tail = newNode;
        }
    
        count++;
        cout << "Enqueued: " << data << " (size: " << count << ")" << endl;
    }
    
    // Function to remove an element from the front of the queue (dequeue)
    int dequeue() {
        // If the queue is empty
        if (isEmpty()){
            cout << "Queue is empty. Cannot dequeue." << endl;
            return -1;
        }
        // cout << "Queue is empty. Cannot dequeue." << endl;
        Node* head = tail->next;
        int value = head->data;
        if (tail == head) {
            // Only one node in the queue
            delete head;
            tail = nullptr;
        } else {
            tail->next = head->next;
            delete head;
        }
        count--;
        // Output the information about the dequeued element
        cout << "Dequeued: " << value << " (size: " << count << ")" << endl;
        return value;
    }

    // Function to get the front element of the queue (peek)
    int peek() {
        // If the queue is empty
        // cout << "Queue is empty." << endl;
        if (isEmpty()){
            cout << "Queue is empty." << endl;
            return -1;
        }
        
        int value = tail->next->data;
        return value;
    }

    // Function to display the queue elements
    void display() {
      // If the queue is empty
        // cout << "Queue is empty." << endl;
        if (isEmpty()){
            cout << "Queue is empty." << endl;
            return;
        }

        cout << "Circular Queue: ";
        Node* current = tail->next;
        for(int i = 0; i < count; i++){
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "(back to head)" << endl;
    }
};

int main() {
    // Open the input file "input_part3.txt"
    ifstream infile("input_part3.txt");
    if (!infile) {
        cerr << "Error opening input_part3.txt" << "\n";
        return 1;
    }
    
    // Redirect standard input to read from the file
    cin.rdbuf(infile.rdbuf());

    int T;
    cin >> T;
    string command;
    CircularQueue cq;
    
    // Process T commands from input_part3.txt
    for (int i = 0; i < T; i++){
        cin >> command;
        if (command == "enqueue") {
            int x;
            cin >> x;
            cq.enqueue(x);
        } else if (command == "dequeue") {
            cq.dequeue();
        } else if (command == "peek") {
            int front = cq.peek();
            if(front != -1)
                cout << "Front element: " << front << "\n";
        } else if (command == "display") {
            cq.display();
        } else {
            cout << "Unknown command: " << command << "\n";
        }
    }
    
    return 0;
}