//Ethan Newman
//EEN170000

#include "Customer.h"
#include "Auditorium.h"

#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <iomanip>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>

using namespace std;

//prototypes
void writeTableToFile(unordered_map<string, Customer*>);
void displayReport(Auditorium, Auditorium, Auditorium);
int columnToIndex(char);
char indexToColumn(int);
unordered_map<string, Customer*> readTable();
vector<string> separateString(string);



int main()
{

    //create the 3 theaters
    Auditorium theater1("A1.txt", 1);
    Auditorium theater2("A2.txt", 2);
    Auditorium theater3("A3.txt", 3);
    //create new table by reading it in.
    unordered_map<string, Customer*> table = readTable();


    //input validation
    int guesses = 0;
    bool exit1 = false;

    while (!exit1)
    {
        guesses = 1;

        //user login input
        string usernameIn;
        string passwordIn;

        cout << "Enter your username (case sensitive):\n";
        getline(cin, usernameIn);
        //valid username
        while (table.find(usernameIn) == table.end())
        {
            cout << "Invalid username, please try again:\n";
            getline(cin, usernameIn);
        }

        cout << "Enter your password (case sensitive):\n";
        getline(cin, passwordIn);


        //after three guesse it goes to the beginning
        while (table.find(usernameIn)->second->getPassword() != passwordIn && guesses != 3)
        {
            cout << "Incorrect Password. Please Try again:\n";
            getline(cin, passwordIn);
            guesses++;
        }

        bool exit2 = false;
        //skips if 3 guesses, goes back to beginning
        while (exit2 == false && guesses != 3)
        {
            //if user is admin
            if (usernameIn == "admin")
            {
                //print modified main menu
                cout << "\n1. Print Report\n2. Logout\n3. Exit\n";
                string adminMM;
                getline(cin, adminMM);

                //input validation
                while (adminMM != "1" && adminMM != "2" && adminMM != "3")
                {
                    cout << "invalid input, please try again\n";
                    getline(cin, adminMM);
                }
                //report
                if (adminMM == "1")
                    displayReport(theater1, theater2, theater3);
                //logout
                else if (adminMM == "2")
                {
                    exit1 = false;
                    exit2 = true;
                }
                //exit
                else
                {
                    theater1.writeToFile("A1.txt");
                    theater2.writeToFile("A2.txt");
                    theater3.writeToFile("A3.txt");
                    exit(0);
                }
            }

            //user is not admin
            else
            {
                //print normal main menu
                cout << "\n1. Reserve Seats\n2. View Orders\n3. Update Orders\n4. Display Receipt\n5. Log Out\n";
                string regularMM;
                getline(cin, regularMM);

                //input validation
                while (regularMM != "1" && regularMM != "2" && regularMM != "3" && regularMM != "4" && regularMM != "5")
                {
                    cout << "invalid input, please try again\n";
                    getline(cin, regularMM);
                }

                //reserve seats
                if (regularMM == "1")
                {
                    //user input
                    string audChoice;
                    cout << "\n1. Auditorium 1\n2. Auditorium 2\n3. Auditorium 3\n";
                    getline(cin, audChoice);

                    //input validation
                    while (audChoice != "1" && audChoice != "2" && audChoice != "3")
                    {
                        cout << "invalid input, please try again\n";
                        getline(cin, audChoice);
                    }

                    int rows, columns;
                    //if auditorium 1 chosen
                    if (audChoice == "1")
                    {
                        theater1.printAuditorium();
                        rows = theater1.getRows();
                        columns = theater1.getColumns();
                    }
                    else if (audChoice == "2")
                    {
                        theater2.printAuditorium();
                        rows = theater2.getRows();
                        columns = theater2.getColumns();
                    }
                    else
                    {
                        theater3.printAuditorium();
                        rows = theater3.getRows();
                        columns = theater3.getColumns();
                    }


                    //user input for row, seat, tickets
                    //input of row number, column number (seat letter), and amount of people
                    string r, c, sen, adu, chi;
                    int row, column;

                    //row input
                    cout << "Enter the row number: ";
                    getline(cin, r);
                    //input validation loop for checkAvailability
                    while (atoi(r.c_str()) > rows ||  atoi(r.c_str()) < 1 || r.find_first_not_of("0123456789") != string::npos)
                    {
                        cout << "Sorry, row does not exist. Please try input again.\n";
                        getline(cin, r);
                    }
                    row = atoi(r.c_str());


                    //seat input
                    cout << "Enter the starting seat letter: ";
                    getline(cin, c);
                    //converts seat letter to upper so it can search index in alphabet for it.
                    transform(c.begin(), c.end(), c.begin(), ::toupper);

                    //input validation loop
                    while (columnToIndex(c[0]) >= columns || (int) columnToIndex(c[0]) < 0 || c.length() > 1)
                    {
                        cout << "Sorry, seat does not exist. Please try input again.\n";
                        getline(cin, c);
                        //uppercase
                        transform(c.begin(), c.end(), c.begin(), ::toupper);
                    }
                    column = columnToIndex(c[0]);


                    //adult ticket amount input
                    cout << "Enter the number of Adult tickets: ";
                    getline(cin, adu);
                    //input validation loops
                    while (atoi(adu.c_str()) + column > columns || atoi(adu.c_str()) < 0 || adu.find_first_not_of("0123456789") != string::npos)
                    {
                        cout << "Sorry, seats do not exist in row. Please try input again.\n";
                        getline(cin, adu);
                    }
                    int adult = atoi(adu.c_str());


                    //child ticket amount input.
                    cout << "Enter the number of Child tickets: ";
                    getline(cin, chi);
                    //input validation loops
                    while (atoi(chi.c_str()) + adult + column > columns || atoi(chi.c_str()) < 0 || chi.find_first_not_of("0123456789") != string::npos)
                    {
                        cout << "Sorry, seats do not exist in row. Please try input again.\n";
                        getline(cin, chi);
                    }
                    int child = atoi(chi.c_str());


                    //senior ticket amount input
                    cout << "Enter the number of Senior tickets: ";
                    getline(cin, sen);
                    //input validation loop
                    while (atoi(sen.c_str()) + child + adult + column > columns || atoi(sen.c_str()) < 0 || sen.find_first_not_of("0123456789") != string::npos)
                    {
                        cout << "Sorry, seats do not exist in row. Please try input again.\n";
                        getline(cin, sen);
                    }
                    int senior = atoi(sen.c_str());
                    int quantity = senior + adult + child;  //makes it a little easier for checkAvailability


                    //if in theater 1
                    if (audChoice == "1")
                    {
                        if (theater1.isAvailable(row - 1, column, quantity))
                        {
                            //then reserve those seats.
                            Customer *current = table.find(usernameIn)->second;
                            theater1.reserveSeats(row - 1, column, adult, child, senior, true, current);
                            cout << "\nSeats have been reserved!\n";
                        }
                        else
                        {
                            cout << "\nSeats were not available\n";
                            //find best available
                            pair<int, int> best = theater1.bestAvailable(quantity);

                            //if it didn't change the best available
                            if (best.first == -1)
                                cout << "No best seats are available in this row.\n";
                            //bestAvailable found
                            else
                            {
                                cout << "Those seats are not open. The next best seats are ";
                                //output next best
                                for (int i = 0; i < quantity; i++)
                                    cout << best.first + 1<< indexToColumn(best.second + i) << ", ";
                                cout << "\n\n";


                                string reserveConfirmation;
                                cout << "Would you like to reserve the seats listed above? (y/n)\n";
                                getline(cin, reserveConfirmation);

                                //input validation loop for confirming the reservation of the next best seats
                                while (reserveConfirmation != "y" && reserveConfirmation != "Y" && reserveConfirmation != "N" && reserveConfirmation != "n")
                                {
                                    cout << "Sorry, input was not 'y' or 'n'. Please try input again.\n";
                                    getline(cin, reserveConfirmation);
                                }

                                if (reserveConfirmation == "Y" || reserveConfirmation == "y")
                                {
                                    Customer *current = table.find(usernameIn)->second;
                                    theater1.reserveSeats(best.first, best.second, adult, child, senior, true, current);
                                }

                            }

                        }
                    }//end of aud1
                    else if (audChoice == "2")
                    {
                        if (theater2.isAvailable(row - 1, column, quantity))
                        {
                            //then reserve those seats.
                            Customer *current = table.find(usernameIn)->second;
                            theater2.reserveSeats(row - 1, column, adult, child, senior, true, current);

                            cout << "\nSeats have been reserved!\n";
                        }
                        else
                        {
                            cout << "\nSeats were not available\n";
                            //find best available
                            pair<int, int> best = theater2.bestAvailable(quantity);

                            //if it didn't change the best available
                            if (best.first == -1)
                                cout << "No best seats are available in this row.\n";
                            //bestAvailable found
                            else
                            {
                                cout << "Those seats are not open. The next best seats are ";
                                //output next best
                                for (int i = 0; i < quantity; i++)
                                    cout << best.first + 1 << indexToColumn(best.second + i) << ", ";
                                cout << "\n\n";


                                string reserveConfirmation;
                                cout << "Would you like to reserve the seats listed above? (y/n)\n";
                                getline(cin, reserveConfirmation);

                                //input validation loop for confirming the reservation of the next best seats
                                while (reserveConfirmation != "y" && reserveConfirmation != "Y" && reserveConfirmation != "N" && reserveConfirmation != "n")
                                {
                                    cout << "Sorry, input was not 'y' or 'n'. Please try input again.\n";
                                    getline(cin, reserveConfirmation);
                                }

                                //if customer does want to reserve
                                if (reserveConfirmation == "Y" || reserveConfirmation == "y")
                                {
                                    Customer *current = table.find(usernameIn)->second;
                                    theater2.reserveSeats(best.first, best.second, adult, child, senior, true, current);
                                }
                            }

                        }
                    }//end of aud2
                    else
                    {
                        if (theater3.isAvailable(row - 1, column, quantity))
                        {
                            //then reserve those seats.
                            Customer *current = table.find(usernameIn)->second;
                            theater3.reserveSeats(row - 1, column, adult, child, senior, true, current);
                            cout << "\nSeats have been reserved!\n";
                        }
                        else
                        {
                            cout << "\nSeats were not available\n";
                            //find best available
                            pair<int, int> best = theater3.bestAvailable(quantity);

                            //if it didn't change the best available
                            if (best.first == -1)
                                cout << "No best seats are available in this row.\n";
                            //bestAvailable found
                            else
                            {
                                cout << "Those seats are not open. The next best seats are ";
                                //output next best
                                for (int i = 0; i < quantity; i++)
                                    cout << best.first + 1<< indexToColumn(best.second + i) << ", ";
                                cout << "\n\n";


                                string reserveConfirmation;
                                cout << "Would you like to reserve the seats listed above? (y/n)\n";
                                getline(cin, reserveConfirmation);

                                //input validation loop for confirming the reservation of the next best seats
                                while (reserveConfirmation != "y" && reserveConfirmation != "Y" && reserveConfirmation != "N" && reserveConfirmation != "n")
                                {
                                    cout << "Sorry, input was not 'y' or 'n'. Please try input again.\n";
                                    getline(cin, reserveConfirmation);
                                }

                                if (reserveConfirmation == "Y" || reserveConfirmation == "y")
                                {
                                    Customer *current = table.find(usernameIn)->second;
                                    theater3.reserveSeats(best.first, best.second, adult, child, senior, true, current);
                                }

                            }

                        }
                    }//end of aud3



                }
                //view orders
                else if (regularMM == "2")
                {
                    table.find(usernameIn)->second->viewOrders();
                }
                //updateOrders
                else if (regularMM == "3")
                {
                    string updateIn;
                    table.find(usernameIn)->second->viewOrders();

                    if (table.find(usernameIn)->second->getOrders().size() > 0)
                    {
                        cout << "Enter the order to be updated: \n";
                        getline(cin, updateIn);


                        //input validation
                        while (updateIn.find_first_not_of("0123456789") != string::npos || atoi(updateIn.c_str()) > (int) table.find(usernameIn)->second->getOrders().size() || atoi(updateIn.c_str()) <= 0)
                        {
                            cout << "Invalid input, please try again: \n";
                            getline(cin, updateIn);
                        }
                        int userInt = atoi(updateIn.c_str());

                        Order *chosenOrder = table.find(usernameIn)->second->getIndexPointer(userInt - 1);
                        // Order *chosenOrder = orders[userInt - 1];

                        //user input for what to do with the order (add, delete, or cancel)
                        string orderMM;
                        cout << "\n1. Add tickets to order\n2. Delete tickets from order\n3. Cancel Order\n";
                        getline(cin, orderMM);

                        while (orderMM != "1" && orderMM != "2" && orderMM != "3")
                        {
                            cout << "invalid input, please try again";
                            getline(cin, orderMM);
                        }


                        if (orderMM == "1") //add tickets
                        {
                            //reserve again
                            //already know auditorium
                            int orderAud = chosenOrder->getAuditorium();

                            int rows, columns;
                            //if auditorium 1 chosen
                            if (orderAud == 1)
                            {
                                theater1.printAuditorium();
                                rows = theater1.getRows();
                                columns = theater1.getColumns();
                            }
                            else if (orderAud == 2)
                            {
                                theater2.printAuditorium();
                                rows = theater2.getRows();
                                columns = theater2.getColumns();
                            }
                            else //3 auditorium
                            {
                                theater3.printAuditorium();
                                rows = theater3.getRows();
                                columns = theater3.getColumns();
                            }


                            //user input for row, seat, tickets
                            //input of row number, column number (seat letter), and amount of people
                            string r, c, sen, adu, chi;
                            int row, column;

                            //row input
                            cout << "Enter the row number: ";
                            getline(cin, r);
                            //input validation loop for checkAvailability
                            while (atoi(r.c_str()) > rows ||  atoi(r.c_str()) < 1 || r.find_first_not_of("0123456789") != string::npos)
                            {
                                cout << "Sorry, row does not exist. Please try input again.\n";
                                getline(cin, r);
                            }
                            row = atoi(r.c_str());


                            //seat input
                            cout << "Enter the starting seat letter: ";
                            getline(cin, c);
                            //converts seat letter to upper so it can search index in alphabet for it.
                            transform(c.begin(), c.end(), c.begin(), ::toupper);

                            //input validation loop
                            while (columnToIndex(c[0]) >= columns || (int) columnToIndex(c[0]) < 0 || c.length() > 1)
                            {
                                cout << "Sorry, seat does not exist. Please try input again.\n";
                                getline(cin, c);
                                //uppercase
                                transform(c.begin(), c.end(), c.begin(), ::toupper);
                            }
                            column = columnToIndex(c[0]);


                            //adult ticket amount input
                            cout << "Enter the number of Adult tickets: ";
                            getline(cin, adu);
                            //input validation loops
                            while (atoi(adu.c_str()) + column > columns || atoi(adu.c_str()) < 0 || adu.find_first_not_of("0123456789") != string::npos)
                            {
                                cout << "Sorry, seats do not exist in row. Please try input again.\n";
                                getline(cin, adu);
                            }
                            int adult = atoi(adu.c_str());


                            //child ticket amount input.
                            cout << "Enter the number of Child tickets: ";
                            getline(cin, chi);
                            //input validation loops
                            while (atoi(chi.c_str()) + adult + column > columns || atoi(chi.c_str()) < 0 || chi.find_first_not_of("0123456789") != string::npos)
                            {
                                cout << "Sorry, seats do not exist in row. Please try input again.\n";
                                getline(cin, chi);
                            }
                            int child = atoi(chi.c_str());


                            //senior ticket amount input
                            cout << "Enter the number of Senior tickets: ";
                            getline(cin, sen);
                            //input validation loop
                            while (atoi(sen.c_str()) + child + adult + column > columns || atoi(sen.c_str()) < 0 || sen.find_first_not_of("0123456789") != string::npos)
                            {
                                cout << "Sorry, seats do not exist in row. Please try input again.\n";
                                getline(cin, sen);
                            }
                            int senior = atoi(sen.c_str());
                            int quantity = senior + adult + child;  //makes it a little easier for checkAvailability
                            //if in theater 1
                            if (orderAud == 1)
                            {
                                if (theater1.isAvailable(row - 1, column, quantity))
                                {
                                    //then reserve those seats.
                                    theater1.reserveSeats(row - 1, column, adult, child, senior, false, chosenOrder);
                                    cout << "\nSeats have been reserved!\n";
                                }
                                else
                                {
                                    cout << "\nSeats were not available\n";
                                    //find best available
                                    pair<int, int> best = theater1.bestAvailable(quantity);

                                    //if it didn't change the best available
                                    if (best.first == -1)
                                        cout << "No best seats are available in this row.\n";
                                    //bestAvailable found
                                    else
                                    {
                                        cout << "Those seats are not open. The next best seats are ";
                                        //output next best
                                        for (int i = 0; i < quantity; i++)
                                            cout << best.first + 1 << indexToColumn(best.second + i) << ", ";
                                        cout << "\n\n";


                                        string reserveConfirmation;
                                        cout << "Would you like to reserve the seats listed above? (y/n)\n";
                                        getline(cin, reserveConfirmation);

                                        //input validation loop for confirming the reservation of the next best seats
                                        while (reserveConfirmation != "y" && reserveConfirmation != "Y" && reserveConfirmation != "N" && reserveConfirmation != "n")
                                        {
                                            cout << "Sorry, input was not 'y' or 'n'. Please try input again.\n";
                                            getline(cin, reserveConfirmation);
                                        }

                                        if (reserveConfirmation == "Y" || reserveConfirmation == "y")
                                        {
                                            theater1.reserveSeats(best.first, best.second, adult, child, senior, false, chosenOrder);
                                        }

                                    }

                                }
                            }//end of aud1
                            else if (orderAud == 2)
                            {
                                if (theater2.isAvailable(row - 1, column, quantity))
                                {
                                    //then reserve those seats.
                                    theater2.reserveSeats(row - 1, column, adult, child, senior, false, chosenOrder);
                                    cout << "\nSeats have been reserved!\n";
                                }
                                else
                                {
                                    cout << "\nSeats were not available\n";
                                    //find best available
                                    pair<int, int> best = theater2.bestAvailable(quantity);

                                    //if it didn't change the best available
                                    if (best.first == -1)
                                        cout << "No best seats are available in this row.\n";
                                    //bestAvailable found
                                    else
                                    {
                                        cout << "Those seats are not open. The next best seats are ";
                                        //output next best
                                        for (int i = 0; i < quantity; i++)
                                            cout << best.first + 1<< indexToColumn(best.second + i) << ", ";
                                        cout << "\n\n";


                                        string reserveConfirmation;
                                        cout << "Would you like to reserve the seats listed above? (y/n)\n";
                                        getline(cin, reserveConfirmation);

                                        //input validation loop for confirming the reservation of the next best seats
                                        while (reserveConfirmation != "y" && reserveConfirmation != "Y" && reserveConfirmation != "N" && reserveConfirmation != "n")
                                        {
                                            cout << "Sorry, input was not 'y' or 'n'. Please try input again.\n";
                                            getline(cin, reserveConfirmation);
                                        }

                                        if (reserveConfirmation == "Y" || reserveConfirmation == "y")
                                        {
                                            theater2.reserveSeats(best.first, best.second, adult, child, senior,false, chosenOrder);
                                        }
                                    }

                                }
                            }//end of aud2
                            else    //aud 3 is the order
                            {
                                if (theater3.isAvailable(row - 1, column, quantity))
                                {
                                    //then reserve those seats.
                                    theater3.reserveSeats(row - 1, column, adult, child, senior, false, chosenOrder);
                                    cout << "\nSeats have been reserved!\n";
                                }
                                else
                                {
                                    cout << "\nSeats were not available\n";
                                    //find best available
                                    pair<int, int> best = theater3.bestAvailable(quantity);

                                    //if it didn't change the best available
                                    if (best.first == -1)
                                        cout << "No best seats are available in this row.\n";
                                    //bestAvailable found
                                    else
                                    {
                                        cout << "Those seats are not open. The next best seats are ";
                                        //output next best
                                        for (int i = 0; i < quantity; i++)
                                            cout << best.first + 1 << indexToColumn(best.second + i) << ", ";
                                        cout << "\n\n";


                                        string reserveConfirmation;
                                        cout << "Would you like to reserve the seats listed above? (y/n)\n";
                                        getline(cin, reserveConfirmation);

                                        //input validation loop for confirming the reservation of the next best seats
                                        while (reserveConfirmation != "y" && reserveConfirmation != "Y" && reserveConfirmation != "N" && reserveConfirmation != "n")
                                        {
                                            cout << "Sorry, input was not 'y' or 'n'. Please try input again.\n";
                                            getline(cin, reserveConfirmation);
                                        }

                                        //user wants to reserve
                                        if (reserveConfirmation == "Y" || reserveConfirmation == "y")
                                        {
                                            theater3.reserveSeats(best.first, best.second, adult, child, senior, false, chosenOrder);
                                        }

                                    }

                                }
                            }//end of aud3





                        }
                        else if (orderMM == "2")    //delete Tickets from order
                        {
                            //ask fro row and seat, verify, unreserve and delete from order
                            string r, c, sen, adu, chi;
                            int row, column;
                            //search in order for the seat using the row and column given
                            //find what seat that is and hang on to it's index in the vector
                            //at the end, seats.erase(index);
                            string rowIn, columnIn;
                            cout << "enter the row to be deleted: \n";
                            getline(cin, r);


                            vector<Seat> seatsInOrder = chosenOrder->getSeats();
                            //check to see if row input is actually in order
                            bool found = false;
                            int foundIndex = 0;
                            for (int i = 0; i < (int) seatsInOrder.size(); i++)
                            {
                                if (seatsInOrder[i].getRow() == atoi(r.c_str()) - 1)
                                {
                                    foundIndex = i;
                                    found = true;
                                    break;
                                }
                            }
                            //makes sure row and column match
                            //input validation
                            while (!found)
                            {
                                cout << "Sorry, row does not exist in order. Please try input again.\n";
                                getline(cin, r);
                                for (int i = 0; i < (int) seatsInOrder.size(); i++)
                                {
                                    if (seatsInOrder[i].getRow() == atoi(r.c_str()) - 1)
                                    {
                                        foundIndex = i;
                                        found = true;
                                        break;
                                    }
                                }
                            }
                            row = atoi(r.c_str()) - 1;


                            cout << "enter the seat letter to be deleted: \n";
                            getline(cin, c);
                            //converts seat letter to upper so it can search index in alphabet for it.
                            transform(c.begin(), c.end(), c.begin(), ::toupper);

                            //input validation loop
                            //makes sure row and column match
                            found = false;
                            for (int i = 0; i < (int) seatsInOrder.size(); i++)
                            {
                                if ((seatsInOrder[i].getColumn() == c[0] && seatsInOrder[i].getRow() == row) && c.length() == 1)
                                {
                                    foundIndex = i;
                                    found = true;
                                    break;
                                }
                            }
                            //still user input
                            while (!found)
                            {
                                cout << "Sorry, seat does not exist. Please try input again.\n";
                                getline(cin, c);
                                //uppercase
                                transform(c.begin(), c.end(), c.begin(), ::toupper);
                                for (int i = 0; i < (int) seatsInOrder.size(); i++)
                                {
                                    if (seatsInOrder[i].getColumn() == c[0] && c.length() == 1)
                                    {
                                        foundIndex = i;
                                        found = true;
                                        break;
                                    }
                                }
                            }
                            column = columnToIndex(c[0]);


                            //mark the tickets as available
                            int orderAud = chosenOrder->getAuditorium();
                            if (orderAud == 1)
                                theater1.setEmpty(row, column, 1);
                            else if (orderAud == 2)
                                theater2.setEmpty(row, column, 1);
                            else
                                theater3.setEmpty(row, column, 1);

                            //delete from the order
                            chosenOrder->removeSeat(foundIndex);

                        }
                        else if (orderMM == "3")    //Cancel order
                        {
                            //unreserve all seats in order, delete the order from the vector of orders
                            vector<Seat> seatsInOrder = chosenOrder->getSeats();

                            int orderAud = chosenOrder->getAuditorium();

                            //loop through seats and unreserve
                            for (int i = 0; i < (int) seatsInOrder.size(); i++)
                            {
                                if (orderAud == 1)
                                    theater1.setEmpty(seatsInOrder[i].getRow(), seatsInOrder[i].columnToIndex(), 1);
                                else if (orderAud == 2)
                                    theater2.setEmpty(seatsInOrder[i].getRow(), seatsInOrder[i].columnToIndex(), 1);
                                else
                                    theater3.setEmpty(seatsInOrder[i].getRow(), seatsInOrder[i].columnToIndex(), 1);

                            }


                            //delete the order from the orders
                            table.find(usernameIn)->second->removeOrder(userInt - 1);
                            cout << "\nOrder cancelled\n";
                        }
                    }
                }
                //display Receipt
                else if (regularMM == "4")
                {
                    table.find(usernameIn)->second->printReciept();

                    //loop through and print the orders
                }
                else if (regularMM == "5")  //log out
                {
                    exit1 = false;
                    exit2 = true;
                }
            }
        }
    }





    return 0;
}








//converts an index to the corresponding letter of the alphabet
int columnToIndex(char column)
{
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    return (int) alphabet.find(column);
}

//converts an index to the corresponding letter of the alphabet
char indexToColumn(int index)
{
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    return alphabet[index];
}

//separates a string into a vector based on spaces
vector<string> separateString(string str)
{
    istringstream iss(str);
    vector<string> result{istream_iterator<string>{iss}, istream_iterator<string>{}};
    return result;
}

//reads in the table to the hashTable
unordered_map<string, Customer*> readTable()
{
    ifstream inFile("userdb.dat");
    string line;
    unordered_map<string, Customer*> table;



    while (getline(inFile, line))
    {
        vector<string> temp = separateString(line);
        Customer *newCus = new Customer(temp[0], temp[1]);
        table.emplace(temp[0], newCus);
    }

    return table;

}

void displayReport(Auditorium one, Auditorium two, Auditorium three)
{
    //print the first row, the header
    cout << setw(15) << left <<  "Labels";
    cout << setw(15) << left <<  "Open Seats";
    cout << setw(15) << left <<  "Reserved Seats";
    cout << setw(15) << left <<  "Adult Seats";
    cout << setw(15) << left <<  "Child Seats";
    cout << setw(15) << left <<  "Senior Seats";
    cout << setw(15) << left <<  "Ticket Sales" << endl;

    //print values for auditorium 1
    cout << setw(15) << left << "Auditorium 1";
    vector<int> oneData = one.printReport();


    //print values for auditorium 2
    cout << setw(15) << left << "Auditorium 2";
    vector<int> twoData = two.printReport();

    //print values for auditorium 3
    cout << setw(15) << left << "Auditorium 3";
    vector<int> threeData = three.printReport();


    //print values for total
    cout << setw(15) << left << "Total";

    //print the open seats, reserved, adult, child, senior values
    std::cout << std::setw(15) << std::left << oneData[0] + twoData[0] + threeData[0];
    std::cout << std::setw(15) << std::left << oneData[1] + twoData[1] + threeData[1];
    std::cout << std::setw(15) << std::left << oneData[2] + twoData[2] + threeData[2];
    std::cout << std::setw(15) << std::left << oneData[3] + twoData[3] + threeData[3];
    std::cout << std::setw(15) << std::left << oneData[4] + twoData[4] + threeData[4];

    //add up total Sales
    float totalSales = 0;
    totalSales += (float) (oneData[2] + twoData[2] + threeData[2]) * (float) 10.0;
    totalSales += (float) (oneData[3] + twoData[3] + threeData[3]) * (float) 5.0;
    totalSales += (float) (oneData[3] + twoData[3] + threeData[3]) * (float) 7.5;

    //format print of total sales
    std::cout << std::left << "$";
    printf("%.2f", totalSales);
    std:: cout << "\n";


}

void writeTableToFile(unordered_map<string, Customer*> table)
{
    ofstream outFile("userdb.dat");
    for (auto x : table)
        outFile << x.first << " " << x.second->getPassword() << endl;
}
