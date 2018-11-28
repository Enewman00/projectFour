//Ethan Newman
//EEN170000
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Order.h"

#include <vector>
#include <string>


class Customer
{
private:

    std::string username;
    std::string password;
    std::vector<Order> orders;


public:

    Customer();
    Customer(std::string, std::string);

    std::string getUsername();
    void setUsername(std::string);

    std::string getPassword();
    void setPassword(std::string);

    std::vector<Order> getOrders();
    void setOrders(std::vector<Order>);

    void addOrder(Order);
    void removeOrder(int);

    void viewOrders();
    void printReciept();

};




#endif
