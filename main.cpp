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

using namespace std;

void writeTableToFile(unordered_map<string, Customer>);
void displayReport(Auditorium, Auditorium, Auditorium);
int columnToIndex(char);
char indexToColumn(int);
unordered_map<string, Customer> readTable();
vector<string> separateString(string);



int main()
{

    //create the 3 theaters
    Auditorium theater1("A1.txt");
    Auditorium theater2("A2.txt");
    Auditorium theater3("A3.txt");
    //create new table by reading it in.
    unordered_map<string, Customer> table = readTable();


    //input validation
    int guesses = 0;
    bool exit1 = false;

    while (!exit1)
    {
        guesses = 0;

        //user login
        


    }














//--------------------------------samples-------------------------
    cout << "\n\n--------------------samples-------------------------\n";
    //demonstrate that table has been filled in
    cout << table.find("usah")->second.getPassword() << endl;


    //print the auditorium
    cout << "auditorium 1: " << endl;
    theater1.printAuditorium();

    //show the report
    displayReport(theater1, theater2, theater3);


    //best avaialable
    cout << "bestAvailable: " << theater1.bestAvailable(4).first + 1 << indexToColumn(theater1.bestAvailable(4).second) << endl;

    //write all of it to their files
    theater1.writeToFile("A1.txt");
    theater2.writeToFile("A2.txt");
    theater2.writeToFile("A3.txt");
    writeTableToFile(table);

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
unordered_map<string, Customer> readTable()
{
    ifstream inFile("userdb.dat");
    string line;
    unordered_map<string, Customer> table;



    while (getline(inFile, line))
    {
        vector<string> temp = separateString(line);
        Customer newCus(temp[0], temp[1]);
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

void writeTableToFile(unordered_map<string, Customer> table)
{
    ofstream outFile("userdb.dat");
    for (auto x : table)
        outFile << x.first << " " << x.second.getPassword() << endl;
}
