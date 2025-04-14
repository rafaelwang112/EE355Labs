#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>
#include <map>

class Date{
    private:
        int month, day, year;

    public: 
        Date(string date){};
        void print_date();
};

#endif 