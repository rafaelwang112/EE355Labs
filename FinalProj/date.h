#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>

class Date{
    private:
        int month, day, year;

    public: 
        Date(std::string date);
        void print_date();
        int get_month() const;
        int get_day() const;
        int get_year() const;
};

#endif 
