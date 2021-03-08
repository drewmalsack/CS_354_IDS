/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <mysql/mysql.h>
#include <time.h>
#include <cstring>
#include <sstream>
#include <string>
#include "FileIO.h"
#include "SysLogFormatter.h"
#include "sysCalls.h"
#include "database.h"


//using namespace std;

void parseSysLog()
{
    SysLogFormatter format;
    database data;
    FileIO readIn("/var/log/syslog");
    std::vector <std::string> Lines;
    MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
    data.mysql_details.server = "localhost";
	data.mysql_details.user = "andrew";
	data.mysql_details.password = "7nry6395";
	data.mysql_details.database = "IDS";
	conn = data.mysql_connection_setup();

    Lines = readIn.read();

	std::string protoDate = Lines.back().substr(0,14);
	std::string month;
	if(protoDate.substr(0, 2) == "Mar")
		month = "03";
	else if(protoDate.substr(0, 2) == "Apr")
		month = "04";
	else	
		month = "05";
	std::string day = protoDate.substr(4,5);
	if(day.find(" ") != std::string::npos)
		day.replace(day.find(" "), day.find(" "), "0");
	std::string times = protoDate.substr(7);
	std::string date = "2021-"+month+"-"+day+" "+times;

    Lines = format.outputCSV(Lines);
	srand(time(NULL));
	int randNum = (rand() %1000 +1);
	std::ostringstream ostr;
	ostr << randNum;
	std::string name = "syslog"+ostr.str();
	//std::cout << name << std::endl;
	
	std::string com = "create table "+name+" (ID int not null auto_increment, Line varchar(255), primary key (ID));";
	char char_arr[com.length()+1];
	strcpy(char_arr, com.c_str());
	
	data.mysql_execute_query(conn, char_arr);
	
    for(std::vector<std::string>::iterator t = Lines.begin(); t< Lines.end()-1; t++)
    {
        com = "insert into "+ name+" (Line) values ("+*t+");";
		std::cout << *t << std::endl;
		//strcpy(char_arr, com.c_str());
		//data.mysql_execute_query(conn, char_arr);
    }
	com = "insert into SyslogTableNames(TableName, StartTime, EndTime) values ("+name+", "+date+", CURRENT_TIMESTAMP());";
	strcpy(char_arr, com.c_str());
	data.mysql_execute_query(conn, char_arr);
	
}

int main(int argc, char *argv[])
{
    
    SysLogFormatter format;
    std::vector <std::string> myList;
    sysCalls table;
    database data;
    MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
/*
	//struct for the database connection details, replace with your login info
	data.mysql_details.server = "localhost";
	data.mysql_details.user = "andrew";
	data.mysql_details.password = "7nry6395";
	data.mysql_details.database = "IDS";

	//conn holds the connection to the database, pass to query function 
	conn = data.mysql_connection_setup();

	//res being the result from the database, replace string with whatever query you want to run
	res = data.mysql_execute_query(conn, "select * from FileHash;");

	std::cout << "Displaying database output of HASH_VALUES: " << std::endl;

	//loops through res and couts the lines returned from the query, will change eventually to output to whatever is needed
	while((row = mysql_fetch_row(res)) != NULL)
	{
		std::cout << row[0] << "|" << row[1] << "|" << row[2] << std::endl;
	}

	//frees up memory and closes database connection
	mysql_free_result(res);
	mysql_close(conn);
    */
    
    
    parseSysLog();
    
    return 0;
}
