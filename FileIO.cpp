#include "FileIO.h"
#include <iostream>
#include <fstream>

using namespace std;

FileIO::FileIO(string name)
{
    fileName = name;
}

void FileIO::read()
{
     // Create a text string, which is used to output the text file
    string myText;

    // Read from the text file
    ifstream MyReadFile(fileName.c_str());

    // Use a while loop together with the getline() function to read the file line by line
    while (getline (MyReadFile, myText)) {
   
    // Output the text from the file
    std::cout << myText << endl;
    
    }

    // Close the file
    MyReadFile.close();
}

void FileIO::readLine(string pattern)
{
     // Create a text string, which is used to output the text file
    string myText;

    // Read from the text file
    ifstream MyReadFile(fileName.c_str());

    // Use a while loop together with the getline() function to read the file line by line
    while (getline (MyReadFile, myText)) {
   
    // Output the text from the file if pattern matches
    if(myText.find(pattern) != std::string::npos)
        std::cout << myText << endl;
    
    }

    // Close the file
    MyReadFile.close();
}
