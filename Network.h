#include<iostream>
#include<vector>

class Network
{
    public:
        Network();
        static int stop;
        void setStop(int);
        std::string TDump();
};