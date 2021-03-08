#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <stdio.h>
#include <string>
#include "sysCalls.h"


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

std::vector <std::string> sysCalls::initialHash(std::vector <std::string> fileList)
{
    char* char_arr;
    std::string str_obj;
    std::vector <std::string> hashList;
    while(fileList.size() != 0)
    {
        str_obj = "sha256sum "+fileList.back();
        char_arr = &str_obj[0];
        hashList.push_back(sysCall(char_arr));
        fileList.pop_back();
    }

    return hashList;
}

int sysCalls::reHash(std::vector <std::string> fileList)
{
    return 1;
}

std::vector <std::string> sysCalls::resourceCollect()
{
    std::string s = sysCall("vmstat 1 3");
    std::string delim = "\n";
    std::string token;
    std::vector <std::string> lines;

    auto start = 0U;
    auto end = s.find(delim);
    int i=0;
    while (end != std::string::npos)
    {
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
