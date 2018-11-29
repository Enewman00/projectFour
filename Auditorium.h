//Ethan Newman
//EEN170000

#ifndef AUDITORIUM_H
#define AUDITORIUM_H

#include "Customer.h"
#include "Order.h"

#include <string>
#include <vector>

class Auditorium
{
private:
    int rows;
    int columns;
    char auditorium[30][26];
    int number;




public:

    Auditorium(std::string, int);


    int getRows();
    void setRows(int);

    int getColumns();
    void setColumns(int);


    void printAuditorium();
    void writeToFile(std::string);
    bool isAvailable(int, int, int);
    void reserveSeats(int, int, int, int, int, bool, Customer*);
    void reserveSeats(int, int, int, int, int, bool, Order*);
    void setEmpty(int, int, int);
    std::vector<int> printReport();
    std::pair<int, int> bestAvailable(int);


};




#endif
