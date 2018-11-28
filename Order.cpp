//Ethan Newman
//EEN170000

#include "Order.h"
#include "Seat.h"

#include <vector>


std::vector<Seat> Order::getSeats()
{
    return seats;
}

void Order::setSeats(std::vector<Seat> s)
{
    seats = s;
}


void Order::addSeat(Seat s)
{
    seats.push_back(s);
}
