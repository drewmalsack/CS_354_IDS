#include "SysLogFormatter.h"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

SysLogFormatter::SysLogFormatter()
{
}

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
    while(myList.size() != 0)
    {
        line = myList.back();
        date = line.substr(0, 15);
        first = line.substr(16).find(" ");
        machine = line.substr(16, first);
        process = line.substr(first+16, line.substr(first+16).find(":"));
        message = line.substr(line.substr(first+16).find(":"));
        
        csv = date + " , " + machine + " , " + process + " , " + message;
        csvOutput.push_back(csv);
        myList.pop_back();
    }
    return csvOutput;
    

}