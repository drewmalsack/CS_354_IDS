#include<iostream>
#include <vector>

class SysLogFormatter
{
    public:
        SysLogFormatter();
        void outputCSV(std::vector <std::string>);
    
    private:
        std::string fileName;
};