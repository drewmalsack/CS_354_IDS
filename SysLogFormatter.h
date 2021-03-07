#include<iostream>
#include <vector>

class SysLogFormatter
{
    public:
        SysLogFormatter();
        std::vector <std::string> outputCSV(std::vector <std::string>);
    
    private:
        std::string fileName;
};