//Ethan Newman
//EEN170000
#include "Customer.h"
#include "Order.h"

#include <vector>
#include <string>

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
