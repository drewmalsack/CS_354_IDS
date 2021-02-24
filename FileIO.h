#include<iostream>

class FileIO
{
    public:
        FileIO(std::string);
        void read();
        void readLine(std::string);
    
    private:
        std::string fileName;
};