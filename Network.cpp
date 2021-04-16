#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <stdio.h>
#include <string>
#include <chrono>
#include "Network.h"

//this function takes a bash command and returns the output, i copied it from stackoverflow so dont ask me what each line does
Network::Network()
{
}

std::string Network::TDump()
{
    std::string cmd = "tcpdump";
    std::string result;
    char buffer[1024];
    int count=0;
    /*auto start = std::chrono::system_clock::now();
    auto duration_in_seconds = std::chrono::duration<double>(start.time_since_epoch());

    double num_seconds = duration_in_seconds.count();

    FILE * pipef = popen(cmd.c_str(), "r");
    if(pipef){
        while(!feof(pipef) && num_seconds <= 600000){
            duration_in_seconds = std::chrono::duration<double>(start.time_since_epoch());

            num_seconds = duration_in_seconds.count();
            int res;
            if((res = fread(buffer, /*note order here 1, sizeof(buffer), pipef)) > 0){
                std::string block(buffer, res);
                result += block;
            }
        }
        pclose(pipef);
    }
    return result;
    */
    FILE * pipef = popen(cmd.c_str(), "r");
    if(pipef){
        while(!feof(pipef) && count<5){
            int res;
            if((res = fread(buffer, /*note order here*/ 1, sizeof(buffer), pipef)) > 0){
                std::string block(buffer, res);
                result += buffer;
                count++;
            }
        }
        pclose(pipef);
    }
    return result;
}

void Network::setStop(int temp)
{
    stop = temp;
}
