#include "SysLogFormatter.h"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

SysLogFormatter::SysLogFormatter()
{
}

//tries to format syslog files into csv's, probably isnt correct formatting for an actual csv but i dont care
vector <string> SysLogFormatter::outputCSV(vector <string> myList)
{
    vector <string> csvOutput;
    string line;
    string date;
    int first;
    string machine;
    string process;
    string message;
    string csv;

    //the function takes a vector string in the argument, this loops through it
    while(myList.size() != 0)
    {
        line = myList.back(); //takes the last element in the vector
        date = line.substr(0, 15); //takes the timestamp
        first = line.substr(16).find(" "); //c++ doesnt have a nice split function so this just holds the index after the timestamp, its finds the first space after index 16
        machine = line.substr(16, first); //gets the machine name which is usualluy something like user-virtualBox
        process = line.substr(first+16, line.substr(first+16).find(":")); //this holds our process name and ends by finding the first : after the timestamp
        message = line.substr(line.substr(first+16).find(":")); //this starts where the last code ended and grabs the rest of the line for out message
        
        csv = date + " , " + machine + " , " + process + " , " + message; //this just puts everything together with commas
        csvOutput.push_back(csv); //pushes the line to a vector
        myList.pop_back(); //deletes the line we just formatted from the first vector
    }
    return csvOutput;
    

}