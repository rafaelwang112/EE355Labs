
#include "contact.h"
// TODO: Add needed libraries! 
#include <iostream>
#include <string>

using namespace std;

Email::Email(string type, string email_addr){
    // TODO: Complete me!
    this->type = type;
    this->email_addr = email_addr;
}


void Email::set_contact(){
    // TODO: Do not change the prompts!
	
    cout << "Enter the type of email address: ";
    cin >> this->type;
    cout << "Enter email address: ";
    cin >> this->email_addr;
}


string Email::get_contact(string style){
    // Note: We have default argument in declaration and not in definition!
    if (style=="full")
	    return "Email (" + type + "): " + email_addr;
    else 
        return email_addr;
}


void Email::print(){
    // Note: get_contact is called with default argument
	cout << get_contact() << endl;
}


Phone::Phone(string type, string num){
    // TODO: It is possible that num includes "-" or not, manage it!
    // TODO: Complete this method!
    // Note: We don't want to use C++11! stol is not valid!
    this->type = type;
    this->phone_num = "";

    for (int i = 0; i < num.length(); i++) {
        char digit = num[i];
        if (digit != '-') {
            this->phone_num += digit;
        }
    }
}


void Phone::set_contact(){
    // TODO: Complete this method
    // Use the same prompts as given!
	cout <<"Enter the type of phone number: ";
    cin >> this->type;
	cout << "Enter the phone number: ";
    cin >> this->phone_num;
}


string Phone::get_contact(string style){
    // TODO: Complete this method, get hint from Email 
    if (style=="full")
	    return "Phone (" + type + "): " + phone_num;
    else 
        return phone_num;
}


void Phone::print(){
    // Note: get_contact is called with default argument
	cout << get_contact() << endl;
}