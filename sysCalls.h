#include<iostream>
#include<vector>

class sysCalls
{
    public:
        std::vector <std::string> initialHash(std::vector <std::string>);
        int reHash(std::vector <std::string>);
        std::string sysCall(const char*);
        std::vector <std::string> resourceCollect();
};