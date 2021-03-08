/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "FileIO.h"
#include "SysLogFormatter.h"
#include "sysCalls.h"

//using namespace std;

int main(int argc, char *argv[])
{
    
    SysLogFormatter format;
    std::vector <std::string> myList;
    sysCalls table;
    /*
    if(argc == 1)
    {
        cout << "Usage details-----------------------------------------" << endl;
        cout << "Program takes up to 2+ arguments" << endl;
        cout << "First argument[required] denotes file name" << endl;
        cout << "Second argument and all additional[optional] denotes string to seach for" << endl;
    }
    else if(argc == 2)
    {
        FileIO file(argv[1]);
    
        myList = file.read(); 
    }
    else if(argc == 3)
    {
        FileIO file(argv[1]);
    
        myList = file.readLine(argv[2]);  
    }
    else
    {
        string pattern = "";
        for(int i=2; i<argc; i++)
            pattern = pattern + argv[i]+" ";
        FileIO file(argv[1]);
        cout << "Pattern to match: " << pattern << endl;
    
        myList = file.readLine(pattern);
    }
    
    format.outputCSV(myList);
    */
    FileIO file("test.txt");
    
    //myList = file.read();
    //table.initialHash(myList);
    table.resourceCollect();
    return 0;
}
