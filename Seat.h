//Ethan Newman
//EEN170000

#ifndef SEAT_H
#define SEAT_H



class Seat
{
private:
    char type;
    int row;
    char column;

public:
    char getType();
    void setType(char);

    int getRow();
    void setRow(int);

    char getColumn();
    void setColumn(char);

    int columnToIndex();

};




#endif
