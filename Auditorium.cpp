//Ethan Newman
//EEN170000

#include "Auditorium.h"
#include "Customer.h"
#include "Order.h"
#include "Seat.h"

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>

Auditorium::Auditorium(std::string fn, int num)
{
    number  = num;
    rows    = 0;
    columns = 0;

    std::ifstream inFile(fn);
    std::string line;

    //while there is another line, add one to rows, find columns
    while (getline(inFile, line))
    {
        columns = (int) line.length();
        rows++;
    }

    //clear the file (restart from the beginning)
    inFile.clear();
    inFile.close();
    inFile.open(fn);

    //loop through and fill in the auditorium with each char from the file.
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < columns; c++) {
            inFile >> auditorium[r][c];
        }
    }
}


int Auditorium::getRows()
{
    return rows;
}
void Auditorium::setRows(int r)
{
    rows = r;
}

int Auditorium::getColumns()
{
    return columns;
}
void Auditorium::setColumns(int c)
{
    columns = c;
}



void Auditorium::printAuditorium()
{
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::cout << "   " << alphabet.substr(0, columns) << std::endl;
    //print the whole auditorium
    for (int r = 0; r < rows; r++)
    {
        std::cout << std::setw(3) << std::left << r + 1;
        for (int c = 0; c < columns; c++)
        {
            if (auditorium[r][c] != '.')
                std::cout << "#";  //print the char
            else
                std::cout << ".";
        }
        std::cout << "\n"; //new line after the row in done
    }
}

void Auditorium::writeToFile(std::string fn)
{
    std::ofstream outFile(fn);

    //loop through the 2d array
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < columns; c++)
        {
            //write the char to the file
            outFile << auditorium[r][c];
        }
        outFile << std::endl; //new line after the row in done
    }
}

bool Auditorium::isAvailable(int r, int c, int q)
{
    //loop through the seats it's checking
    for (int i = 0; i < q; i++)
    {
        //returns true if all checked are in bounds and empty
        if (auditorium[r][c + i] != '.' || c + i > columns || r > rows)
            return false;
    }
    return true;
}

void Auditorium::reserveSeats(int row, int column, int a, int c, int s, bool newOrder, Customer *current)
{
    int adult = a;
    int child = c;
    int senior = s;
    //edit 2d array
    //runs
    //total amount of ticket bough
    int total = adult + child + senior;

    //loops through and assigns a ticket to each seat
    for (int i = 0; i < total; i++)
    {
        //if there are still adults to be seated
        if (adult > 0)
        {
            auditorium[row][column + i] = 'A';
            adult--;
        }
        //if there are still children to be seated
        else if (child > 0)
        {
            auditorium[row][column + i] = 'C';
            child--;
        }
        //if there are still seniors to be seated
        else if (senior > 0)
        {
            auditorium[row][column + i] = 'S';
            senior--;
        }
    }

    adult = a;
    child = c;
    senior = s;

    std :: string alphabet  = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    //if it is a new order, create and add a new order to the customer
    if (newOrder)
    {
        //need to pass in the auditorium number as well?
        Order orderCreated(number);
        for (int i = 0; i < total; i++)
        {
            if (adult > 0)
            {
                Seat newSeat('A', row, alphabet[column + i]);
                adult--;
                orderCreated.addSeat(newSeat);
            }
            else if (child > 0)
            {
                Seat newSeat('C', row, alphabet[column + i]);
                child--;
                orderCreated.addSeat(newSeat);
            }
            else
            {
                Seat newSeat('S', row, alphabet[column + i]);
                senior--;
                orderCreated.addSeat(newSeat);
            }
        }
        current->addOrder(orderCreated);

    }
    if (!newOrder)
    {
        std::cout << "Something went wrong with adding the tickets to the order object when you reserve seats\n";
    }

    //if it's not a new order, don't - do it in the main, get the Customer and
}



//if it's not a new order you are adding tickets to an old order. We need to be passed the order as well
void Auditorium::reserveSeats(int row, int column, int a, int c, int s, bool newOrder, Order *order)
{
    int adult = a;
    int child = c;
    int senior = s;
    //edit 2d array
    //runs
    //total amount of ticket bough
    int total = adult + child + senior;

    //loops through and assigns a ticket to each seat
    for (int i = 0; i < total; i++)
    {
        //if there are still adults to be seated
        if (adult > 0)
        {
            auditorium[row][column + i] = 'A';
            adult--;
        }
        //if there are still children to be seated
        else if (child > 0)
        {
            auditorium[row][column + i] = 'C';
            child--;
        }
        //if there are still seniors to be seated
        else if (senior > 0)
        {
            auditorium[row][column + i] = 'S';
            senior--;
        }
    }

    std :: string alphabet  = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    adult = a;
    child = c;
    senior = s;

    //if it is not a new order, create and add a new order to the customer
    if (newOrder)
    {
        std::cout << "Something went wrong with adding the tickets to the order object when you reserve seats\n";
    }
    if (!newOrder)
    {
        for (int i = 0; i < total; i++)
        {
            if (adult > 0)
            {
                Seat newSeat('A', row, alphabet[column + i]);
                adult--;
                order->addSeat(newSeat);
            }
            else if (child > 0)
            {
                Seat newSeat('C', row, alphabet[column + i]);
                child--;
                order->addSeat(newSeat);
            }
            else
            {

                Seat newSeat('S', row, alphabet[column + i]);
                senior--;
                order->addSeat(newSeat);
            }

        }
    }


}


void Auditorium::setEmpty(int row, int column, int quantity)
{
    for (int i = 0; i < quantity; i++)
        auditorium[row][column + i] = '.';
}



std::vector<int> Auditorium::printReport()
{
    int totalSeats = 0, totalSold = 0, adult = 0, child = 0, senior = 0;
    double totalSales = 0;

    //number of seats in the auditorium
    totalSeats = rows * columns;

    //loops through auditorium and adds to totals
    for (int r = 0; r < rows; r++)
    {

        for (int c = 0; c < columns; c++)
        {
            //if seat is sold
            if (auditorium[r][c] != '.')
            {
                totalSold++;

                //switch statement to see if it's a A,C, or S ticket
                switch(auditorium[r][c]) {
                    //if the ticket is a senior ticket
                    case 'S' :
                        senior++;
                        totalSales += 7.5;
                        break;
                    //if the ticket is a child ticket
                    case 'C' :
                        child++;
                        totalSales += 5;
                        break;
                    //any other ticket (adult ticket)
                    default :
                        adult++;
                        totalSales += 10;
                        break;

                }


            }

        }
    }


    std::cout << std::setw(15) << std::left << totalSeats - totalSold;
    std::cout << std::setw(15) << std::left << totalSold;
    std::cout << std::setw(15) << std::left << adult;
    std::cout << std::setw(15) << std::left << child;
    std::cout << std::setw(15) << std::left << senior;
    std::cout << std::left << "$";
    printf("%.2f", totalSales);
    std:: cout << "\n";

    std::vector<int> data{totalSeats - totalSold, totalSold, adult, child, senior};
    return data;
}




std::pair<int, int> Auditorium::bestAvailable(int customerQuantity)
{
    std :: string alphabet  = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //used to locate column
    float distance            = (float)(rows + columns);
    bool available          = true;
    std::pair<int, int> startingSeat(-1, -1); //the seat it returns

    //loop through 2d array
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < columns; c++)
        {
            available = true;
            for (int i = 0; i < customerQuantity; i++)
            {
                //if it's not available, skips this set and moves to the next one
                if (c + i > columns || auditorium[r][c + i] != '.') //if out of bounds, or is reserved
                {
                    available = false;
                    break;       //end the loop b/c it doesn't have to check the other seats.

                }
            }

            //if those seats are available
            if (available)
            {
                float columnDistance = (float) abs((c + ((customerQuantity - 1)/2)) - ((columns - 1)/2)); //distance of middle seat from the center of row
                float rowDistance    = (float) abs(r - ((rows - 1)/2));   //distance from the center row
                float totalDistance  = rowDistance + columnDistance;


                if (totalDistance == distance)  //if a tiebreaker is needed
                {
                    //distance of the previous startingSeat to the middle row
                    float prevDistance = (float) abs(startingSeat.first - (rows - 1)/2);

                    //if the distance to the center row doesn't break the tie
                    if (rowDistance == prevDistance)
                    {
                        //if the row we're on is closer to the front
                        if (r < startingSeat.first)
                        {
                            distance     = totalDistance;
                            startingSeat = std::make_pair(r, c);
                        }
                    }
                    //if current wins the tiebreaker
                    else if (rowDistance < prevDistance)
                    {
                        distance     = totalDistance;
                        startingSeat = std::make_pair(r, c);
                    }
                }
                //if current is closer then previous best
                else if (totalDistance < distance)
                {
                    distance     = totalDistance;
                    startingSeat = std::make_pair(r, c);
                }
            }
        }
    }

    return startingSeat;

}
