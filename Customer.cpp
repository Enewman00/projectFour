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
std::vector<Order>* Customer::getOrdersPointer()
{
    return &orders;
}

Order* Customer::getIndexPointer(int i)
{
    return &orders[i];
}

void Customer::setOrders(std::vector<Order> o)
{
    orders = o;
}


void Customer::addOrder(Order o)
{
    orders.push_back(o);
}

void Customer::removeOrder(int o)
{
    orders.erase(orders.begin() + o);
}

void Customer::viewOrders()
{
    //tell if vector is empty
    if (orders.size() == 0)
        std::cout << "You have no orders\n\n";
    else    //otherwise, print out the Orders
    {
        //header
        std::cout << "\n";
        std::cout << std::setw(7) << std::left << "Order";
        std::cout << std::setw(13) << std::left << "Auditorium";
        std::cout << std::setw(25) << std::left << "Seats";
        std::cout << std::setw(11) << std::left << "Adults";
        std::cout << std::setw(11) << std::left << "Children";
        std::cout << std::setw(11) << std::left << "Seniors" << std::endl;

        //loop through each order
        for (int i = 0; i < (int) orders.size(); i++)
        {
            std::cout << std::setw(7) << std::left << i + 1;
            std::cout << std::setw(13) << std::left << orders[i].getAuditorium();

            int adults   = 0;
            int children = 0;
            int seniors  = 0;
            std::ostringstream os;
            std::vector<Seat> seats= orders[i].getSeats();

            //loop through the seats in the order
            for (int j = 0; j < (int) orders[i].getSeats().size(); j++)
            {
                //all seats[j].getType is returning S
                if (seats[j].getType() == 'A')
                    adults++;
                else if (seats[j].getType() == 'C')
                    children++;
                else if (seats[j].getType() == 'S')
                    seniors++;

                os << seats[j].getRow() + 1 << seats[j].getColumn() << ' ';
            }

            std::cout << std::setw(25) << std::left << os.str();
            std::cout << std::setw(11) << std::left << adults;
            std::cout << std::setw(11) << std::left << children;
            std::cout << std::setw(11) << std::left << seniors;
            std::cout << "\n";
        }
        std::cout << "\n";
    }
}

void Customer::printReciept()
{
    float totalAmount = 0;
    //tell if vector is empty
    if (orders.empty())
        std::cout << "\nYou have no orders\n\n";
    else    //otherwise, print out the Orders
    {
        //header
        std::cout << "\n";
        std::cout << std::setw(7) << std::left << "Order";
        std::cout << std::setw(13) << std::left << "Auditorium";
        std::cout << std::setw(25) << std::left << "Seats";
        std::cout << std::setw(11) << std::left << "Adults";
        std::cout << std::setw(11) << std::left << "Children";
        std::cout << std::setw(11) << std::left << "Seniors";
        std::cout << std::setw(11) << std::left << "Total Amount";
        std::cout << "\n";

        //loop through each order
        for (int i = 0; i < (int) orders.size(); i++)
        {
            std::cout << std::setw(7) << std::left << i + 1;
            std::cout << std::setw(13) << std::left << orders[i].getAuditorium();

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

                os << seats[j].getRow() + 1<< seats[j].getColumn() << ' ';
            }

            std::cout << std::setw(25) << std::left << os.str();
            std::cout << std::setw(11) << std::left << adults;
            std::cout << std::setw(11) << std::left << children;
            std::cout << std::setw(11) << std::left << seniors;

            float amount = ((float) adults * (float) 10.0) + ((float) children * (float) 5.0) + ((float) seniors * (float) 7.5);
            std::cout << "$";
            printf("%.2f", amount);

            std::cout << "\n";

            totalAmount += amount;
        }

        std::cout << "\n Total Amount Spent: $";
        printf("%.2f", totalAmount);
        std:: cout << "\n\n";

    }
}
