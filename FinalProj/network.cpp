
#include "network.h"
#include <limits>
#include "misc.h"
#include <fstream>
#include <iostream>

Network::Network(){
    head = NULL;
    tail = NULL;
    count = 0;
}


Network::Network(string fileName){
    // TODO: complete this method!
    // Implement it in one single line!
    // You may need to implement the load method before this!
    loadDB(fileName);

}

Network::~Network(){ 
}

Person* Network::search(Person* searchEntry){
    // Searches the Network for searchEntry
    // if found, returns a pointer to it, else returns NULL
    // TODO: Complete this method
    Person* traverse = head;
    if (head==nullptr){
        return nullptr;
    }
    while (traverse!=searchEntry){
        traverse = traverse->next;
        if (traverse == nullptr){
            return nullptr;
        }
    }
    return traverse;

}


Person* Network::search(string fname, string lname){
    // New == for Person, only based on fname and lname
    // if found, returns a pointer to it, else returns NULL
    // TODO: Complete this method
    // Note: two ways to implement this, 1st making a new Person with fname and lname and and using search(Person*), 2nd using fname and lname directly. 
    Person* traverse = head;
    if (head==nullptr){
        return nullptr;
    }
    while (traverse->f_name!=fname && traverse->l_name!=lname){
        traverse = traverse->next;
        if (traverse == nullptr){
            return nullptr;
        }
    }
    return traverse;
}


void Network::loadDB(string filename){
    // TODO: Complete this method
    std::ifstream file(filename);
    if (!file.is_open()) {
        cout << "Could not open the file!" << endl;
        return;
    }

    string fname, lname, bdate, email, phone; // Assuming these are the fields
    while (file >> fname >> lname >> bdate>> email >>phone) { // Adjust this based on your data format
        Person* newPerson = new Person(fname, lname, bdate, email, phone);
        push_back(newPerson); // Add person to the network
    }
    file.close();
}

void Network::saveDB(string filename){
    // TODO: Complete this method
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Could not open the file!" << endl;
        return;
    }

    Person* ptr = head;
    while (ptr != NULL) {
        file << ptr->f_name << " " << ptr->l_name << " " << ptr->birthdate << endl;
        ptr = ptr->next;
    }
    file.close();
    cout << "Network saved to " << filename << endl;
}


void Network::printDB(){
    // Leave me alone! I know how to print! 
    // Note: Notice that we don't need to update this even after adding to Personattributes
    // This is a feature of OOP, classes are supposed to take care of themselves!
    cout << "Number of people: " << count << endl;
    cout << "------------------------------" << endl;
    Person* ptr = head;
    while(ptr != NULL){
        ptr->print_person();
        cout << "------------------------------" << endl;
        ptr = ptr->next;
    }
}



void Network::push_front(Person* newEntry){
    newEntry->prev = NULL;
    newEntry->next = head;

    if (head != NULL)
        head->prev = newEntry;
    else
        tail = newEntry;
    
    head = newEntry;
    count++;
}


void Network::push_back(Person* newEntry){
    // Adds a new Person (newEntry) to the back of LL
    // TODO: Complete this method
    newEntry->next = NULL;
    newEntry->prev = tail;

    if (tail != NULL)
        tail->prev = newEntry;
    else
        head = newEntry;

    tail = newEntry;
    count++;
} 



bool Network::remove(string fname, string lname){
    // TODO: Complete this method
    Person* traverse = head;
    if (head==nullptr){
        return false;
    }
    while (traverse->f_name!=fname || traverse->l_name!=lname){
        traverse = traverse->next;
        if (traverse == nullptr){
            return false;
        }
    }
    if (traverse -> next == nullptr){ //deleting last element
        if (traverse -> prev == nullptr){ //if only one elem
            head = nullptr;
            tail = nullptr;
            delete traverse;
            return true;
        }
        ((traverse ->prev)->next) = nullptr;
        tail = traverse-> prev;
        delete traverse;
        return true;
    }
    if (traverse == head){ //for deleting head
        head = traverse -> next;
        head->prev = nullptr;
        delete traverse;
        return true;
    }
    (traverse -> prev)->next = traverse -> next;
    (traverse -> next)-> prev = traverse -> prev;
    delete traverse;
    return true;

}


void Network::showMenu(){
    // TODO: Complete this method!
    // All the prompts are given to you, 
    // You should add code before, between and after prompts!

    int opt;
    while(1){
        cout << "\033[2J\033[1;1H";
        printMe("banner"); // from misc library

        cout << "Select from below: \n";
        cout << "1. Save network database \n";
        cout << "2. Load network database \n";
        cout << "3. Add a new person \n";
        cout << "4. Remove a person \n";
        cout << "5. Print people with last name  \n";
        cout << "\nSelect an option ... ";
        
        if (cin >> opt) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Wrong option! " << endl;
            return;
        }
        
        // You may need these variables! Add more if you want!
        string fname, lname, fileName, bdate;
        cout << "\033[2J\033[1;1H";

        if (opt==1){
            // TODO: Complete me!
            cout << "Saving network database \n";
            cout << "Enter the name of the save file: ";
            // Save the network database into the file with the given name,
            // with each person saved in the format the save as printing out the person info,
            // and people are delimited similar to "networkDB.txt" format
            getline(cin, fileName);
            saveDB(fileName);
            cout << "Network saved in " << fileName << endl;
        }
        else if (opt==2){
            // TODO: Complete me!
            cout << "Loading network database \n";
            // TODO: print all the files in this same directory that have "networkDB.txt" format
            // print format: one filename one line.
            // This step just shows all the available .txt file to load.
            string filename;
            cout << "Enter the name of the load file: "; 
            cin >> filename;
            // If file with name FILENAME does not exist: 
            if (!(ifstream(filename))){
                cout << "File FILENAME does not exist!" << endl;
            }
            else{
                    // If file is loaded successfully, also print the count of people in it: 
                cout << "Network loaded from " << fileName << " with " << count << " people \n";
            }
        }
        else if (opt == 3){
            // TODO: Complete me!
            // TODO: use push_front, and not push_back 
            // Add a new Person ONLY if it does not exists!
            cout << "Adding a new person \n";

            Person* newp = new Person();

            Person* exists = search(newp);
            if (exists != NULL){
                delete newp;
            }
            else {
                push_front(newp); 
            }
        }
        else if (opt == 4){
            // TODO: Complete me!
            // if found, cout << "Remove Successful! \n";
            // if not found: cout << "Person not found! \n";
            string f_name, l_name;
            cout << "Enter a name to remove: " << endl;
            cin >> f_name >> l_name;
            bool result = remove (f_name, l_name);
            if (result){
                cout << "Remove Successful! \n";
                cout << "Removing a person \n";
                cout << "First name: " << f_name << endl;
                cout << "Last name: " << l_name << endl;
            }
            else{
                cout << "Person not found! \n";
            }
        }
        else if (opt==5){
            // TODO: Complete me!
            // print the people with the given last name
            // if not found: cout << "Person not found! \n";
            cout << "Print people with last name \n";
            cout << "Last name: ";
            string l_name;
            cin >> l_name;

            bool found = false;
            Person* traverse = head;
            while(traverse != NULL){
                if (traverse->l_name == l_name){
                    traverse->print_person();
                    found = true;
                }
                traverse = traverse->next;
            }
            if (found == false)
                cout << "Person not found! \n";

        }

        
        else
            cout << "Nothing matched!\n";
        
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\n\nPress Enter key to go back to main menu ... ";
        string temp;
        std::getline (std::cin, temp);
        cout << "\033[2J\033[1;1H";
    }
}

