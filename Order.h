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


public:

    std::vector<Seat> getSeats();
    void setSeats(std::vector<Seat>);




    void addSeat(Seat);



};




#endif
