//Ethan Newman
//EEN170000

#ifndef ORDER_H
#define ORDER_H

#include "Seat.h"

#include <vector>


class Order
{
private:
    std::vector<Seat> seats;
    int auditorium;


public:
    Order(int);

    int getAuditorium();
    void setAuditorium(int a);

    std::vector<Seat> getSeats();
    void setSeats(std::vector<Seat>);




    void addSeat(Seat);
    void removeSeat(int);



};




#endif
