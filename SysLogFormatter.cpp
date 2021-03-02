#include "SysLogFormatter.h"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

SysLogFormatter::SysLogFormatter()
{
}

void SysLogFormatter::outputCSV(vector <string> myList)
{
    while(myList.size() != 0)
    {
        string line = myList.back();
        string date = line.substr(0, 15);
        int first = line.substr(16).find(" ");
        string machine = line.substr(16, first);
        string process = line.substr(first+16, line.substr(first+16).find(":"));
        
        if(line.substr(first+16).find(":")+2 != '(' || line.substr(first+16).find(":")+2 != '[')
        {
            string user = "NULL";
            string userProcess = "NULL";
            string message = line.substr(line.substr(first+16).find(":"));
        }
        
        // have to find way to fix .find loops and shorten code
        else if(line.substr(first+16).find(":")+2 == '(')
        {
            string user = line.substr(line.find('('), line.find(')');
            string userProcess = line.substr(line.find(')')+1, line.substr(line.find(')')).find(" "));
            string message = line.substr(line.substr(line.find(')')).find(" "));
        }
        else
        {
            string user = line.substr(line.substr(first+16).find(":")+2, line.substr(first+16).find(":").find(']')+2;
            string userProcess = line.substr(first+16).find(":").find(']')+2, line.substr(first+16).find(":").find(']').find(" "));
            string message = line.substr(line.substr(line.find(')')).find(" "));
        }
        
        cout << process << endl;
        myList.pop_back();
    }
    

}