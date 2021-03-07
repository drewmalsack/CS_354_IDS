#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include "hash.h"


std::string hash::sysCall(const char* cmd)
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

std::vector <std::string> hash::initialHash(std::vector <std::string> fileList)
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

int hash::reHash(std::vector <std::string> fileList)
{
    return 1;
}
