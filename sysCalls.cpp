#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <stdio.h>
#include <string>
#include "sysCalls.h"

//this function takes a bash command and returns the output, i copied it from stackoverflow so dont ask me what each line does
std::string sysCalls::sysCall(const char* cmd)
{
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

//this hashes each file from the file name given to it and returns a vector holding them
std::vector <std::string> sysCalls::initialHash(std::vector <std::string> fileList)
{
    char* char_arr;
    std::string str_obj;
    std::vector <std::string> hashList;
    while(fileList.size() != 0)
    {
        str_obj = "sha256sum "+fileList.back();
        str_obj.erase(std::remove(str_obj.begin(), str_obj.end(), '\r'), str_obj.end());
        //std::cout << str_obj << std::endl;
        char_arr = &str_obj[0]; //again the command we use, uses a char array not a string so we convert
        //std::cout << char_arr << std::endl;
        hashList.push_back(sysCall(char_arr)); //pushes the output to a vector to be returned 
        fileList.pop_back(); //deletes the last line of the original vector
    }

    return hashList;
}

//this collects resources using the vmstat command and returns a vector
std::vector <std::string> sysCalls::resourceCollect()
{
    std::string s = sysCall("vmstat 20 30"); //the numbers need to change here vmstat 20 30
    std::string delim = "\n"; //the string that is returned has line breaks 
    std::string token;         // so i use them to break the string into multiple strings
    std::vector <std::string> lines; //so i can put them seperatly into a vector

    int start = 0U;
    int end = s.find(delim);
    int i=0;
    //this loops through the returned string to split it apart and pushes it to a vector
    while (end != std::string::npos)
    {
        //i didnt think the first line of output was necesary to i ignore it
        if(i==0)
        {
            start = end + delim.length();
            end = s.find(delim, start);
            i=1;
        }  
        else{
            token = s.substr(start, end - start);
            token = token.substr(token.find_first_not_of(' '));
            start = end + delim.length();
            end = s.find(delim, start);
            size_t pos;
            while( ( pos = token.find( "  " ) )!=std::string::npos )
                token = token.replace( pos, 2, " " );
            std::replace( token.begin(), token.end(), ' ', ','); // replace all 'x' to 'y'

            lines.push_back(token);
        }
        
    }

    return lines;

}
