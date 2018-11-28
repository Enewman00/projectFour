//Ethan Newman
//EEN170000

#ifndef AUDITORIUM_H
#define AUDITORIUM_H

#include <string>
#include <vector>

class Auditorium
{
private:
    int rows;
    int columns;
    char auditorium[30][26];




public:

    Auditorium(std::string);


    int getRows();
    void setRows(int);

    int getColumns();
    void setColumns(int);


    void printAuditorium();
    void writeToFile(std::string);
    bool isAvailable(int, int, int);
    void reserveSeats(int, int, int, int, int);
    std::vector<int> printReport();
    std::pair<int, int> bestAvailable(int);


};




#endif
