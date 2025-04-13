#include <iostream>
#include <string>
#include <fstream>
using namespace std;

/*
//comment it out to get the output for question 1
// Q1:
// Comment it out to run Q1
// Create a person class with the following attributes:
// - name (string)
// - age (int)
// function: display personinfo 
class Person {
    protected:
        string name;
        int age;
    public:
    Person(const string &name, int age)
        : name(name), age(age) {};
    void displayPersonInfo(ofstream& out) const {
        out << "Person: " << name << ", Age: " << age << endl;
    }
};

// Create a Student public inheritance class from person 
// with the following attributes:
// - Name (string)
// - Age (int)
// - studentID (int)
// - GPA (float)
class Student : public Person {
    public:
        Student(const std::string& n, int a) : Person(n, a) {}
    };


//Calling displayPersonInfo() in Student class will result in an error because it has no access
// Create a student private inheritance class from person 
class StudentPrivate : private Person {
    public:
        StudentPrivate(const std::string& n, int a) : Person(n, a) {}

        void showInfo(ofstream& out) const {
            displayPersonInfo(out);   // if we want to use the displayPersonInfo function in the private class we need to create a function
        }
        
    };
*/


// Q2:
// Creat an abstract Person class 
class Person {
    protected:
        string name;
        int age;
    public:
        Person(const string& n, int a) : name(n), age(a) {}
    
        // Pure virtual function makes Person an abstract class.
        virtual void displayInfo(ofstream& out) = 0;
        virtual void introduce(ofstream& out) = 0;
    };
    
class Student : public Person {
    int studentId;
    double gpa;
public:
    Student(const string n, int a, int id, double g)
        : Person(n, a), studentId(id), gpa(g) {}

    // Override displayInfo for Student-specific details.
    void displayInfo(ofstream& out) {
        out << "Person: " << name << ", Age: " << age 
                << ", ID: " << studentId << ", GPA: " << gpa << endl;
    }

    void introduce(ofstream& out){
        out << "I am a student. " << "My name is " << name << endl;
    }
};
    
class Teacher : public Person {
    string subject;
    int yearsOfExperience;
public:
    Teacher(const string n, int a, const string& subj, int exp)
        : Person(n, a), subject(subj), yearsOfExperience(exp) {}

    // Override displayInfo for Teacher-specific details.
    void displayInfo(ofstream& out) {
        out << "Person: " << name << ", Age: " << age 
                << ", Subject: " << subject 
                << ", Experience: " << yearsOfExperience << " years" << endl;
    }
    void introduce(ofstream& out){
        out << "I am a teacher. " << "My name is " << name << endl;
    }
};


int main() {
    ifstream infile("large_input_file.txt");
    if (!infile) {
        cout  << "Error: Unable to open input.txt" << endl;
        return 1;
    }

    int n_people;
    string line;
    infile >> n_people;

    //ofstream outfile_q1("output_q1.txt");       // Comment it out to run Q1
    ofstream outfile_q2("output_q2.txt");
    ofstream outfile_q3("output_q3.txt");

    for(int i = 0; i < n_people; i++) {
        getline(infile, line);
        string role;
        infile >> role;
        
        if (role == "Student") {
            string name;
            int age, id;
            float gpa;
            infile >> name >> age >> id >> gpa;

            /*
            // Execution for Q1 
            Student student(name, age);                     
            StudentPrivate studentPrivate(name, age);       
            
            outfile_q1 << "Public Inheritance: ";         
            student.displayPersonInfo(outfile_q1);        
            //outfile_q1 << "Private Inheritance: ";
            //studentPrivate.displayPersonInfo(outfile_q1); // Calling private inheritance will result in an error
            */

            // start for q2
            Student student(name, age, id, gpa);
            outfile_q2 << "Student: ";
            student.displayInfo(outfile_q2);

            student.introduce(outfile_q3);
        } 
        else {
            string name;
            int age;
            string subject;
            int yearsOfExperience;
            infile >> name >> age >> subject >> yearsOfExperience;
            Teacher teacher(name, age, subject, yearsOfExperience);
            
            outfile_q2 << "Teacher: ";
            teacher.displayInfo(outfile_q2);

            teacher.introduce(outfile_q3);
        }
        
    }
    
    infile.close();
    //outfile_q1.close();       //comment it out to run Q1
    
    outfile_q2.close();
    outfile_q3.close();
    
    return 0;
}
