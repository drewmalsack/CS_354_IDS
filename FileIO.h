#include<iostream>
#include<vector>

class FileIO
{
    public:
        FileIO(std::string);
        std::vector <std::string> read();
        std::vector <std::string> readLine(std::string);
    
    private:
        std::string fileName;
        std::vector <std::string> lineList; 
};