//Ethan Newman
//EEN170000
#include "Customer.h"
#include "Order.h"
#include "Seat.h"

#include <vector>
#include <sstream>
#include <string>
#include <iomanip>
#include <iostream>

Customer::Customer()
{
    username = "";
    password = "";
    std::vector<Order> orders;
}

Customer::Customer(std::string u, std::string p)
{
    username = u;
    password = p;
    std::vector<Order> orders;
}

std::string Customer::getUsername()
{
    return username;
}

void Customer::setUsername(std::string u)
{
    username = u;
}

std::string Customer::getPassword()
{
    return password;
}
void Customer::setPassword(std::string p)
{
    password = p;
}

std::vector<Order> Customer::getOrders()
{
    return orders;
}

void Customer::setOrders(std::vector<Order> o)
{
    orders = o;
}


void Customer::addOrder(Order o)
{
    orders.push_back(o);
}

void Customer::viewOrders()
{
    //tell if vector is empty
    if (orders.empty())
        std::cout << "You have no orders\n\n";
    else    //otherwise, print out the Orders
    {
        //header
        std::cout << std::setw(15) << std::left << "Order Number";
        std::cout << std::setw(15) << std::left << "Auditorium";
        std::cout << std::setw(30) << std::left << "Seats";
        std::cout << std::setw(15) << std::left << "Adults";
        std::cout << std::setw(15) << std::left << "Children";
        std::cout << std::setw(15) << std::left << "Seniors";
        std::cout << "\n";

        //loop through each order
        for (int i = 0; i < (int) orders.size(); i++)
        {
            std::cout << std::setw(15) << std::left << "Number " << i + 1;
            std::cout << std::setw(15) << std::left << orders[i].getAuditorium();

            int adults   = 0;
            int children = 0;
            int seniors  = 0;
            std::ostringstream os;
            std::vector<Seat> seats= orders[i].getSeats();

            //loop through the seats in the order
            for (int j = 0; j < (int) orders[i].getSeats().size(); j++)
            {

                if (seats[j].getType() == 'A')
                    adults++;
                else if (seats[j].getType() == 'C')
                    children++;
                else if (seats[j].getType() == 'S')
                    seniors++;

                os << seats[j].getRow() << seats[j].getColumn() << ' ';
            }

            std::cout << std::setw(30) << std::left << os.str();
            std::cout << std::setw(15) << std::left << adults;
            std::cout << std::setw(15) << std::left << children;
            std::cout << std::setw(15) << std::left << seniors;
            std::cout << "\n";
        }
    }
}
