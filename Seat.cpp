//Ethan Newman
//EEN170000

#include "Seat.h"

#include <string>

char Seat::getType()
{
    return type;
}

void Seat::setType(char t)
{
    type = t;
}

int Seat::getRow()
{
    return row;
}

void Seat::setRow(int r)
{
    row = r;
}

char Seat::getColumn()
{
    return column;
}

void Seat::setColumn(char c)
{
    column = c;
}

int Seat::columnToIndex()
{
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    return (int) alphabet.find(column);
}
