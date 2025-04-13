#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

class Book {
public:
    string bookId;
    string bookName;
    string bookAuthor;
    string yearOfPub;
    string price;
    string status;

    //build constructor 
    Book(const string& id, const string& name, const string& author,
         const string& year, const string& price, const string& stat){
            bookId = id;
            bookName = name;
            bookAuthor = author;
            yearOfPub = year;
            price
         }
}