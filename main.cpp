#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <mysql/mysql.h>
#include <time.h>
#include <cstring>
#include <sstream>
#include <string>
#include <thread>
#include "FileIO.h"
#include "SysLogFormatter.h"
#include "sysCalls.h"
#include "database.h"


//using namespace std;

void parseSysLog()
{
	/*
	* setting up variables and class instances 
	*/
	database data;
    SysLogFormatter format;
    FileIO readIn("/var/log/syslog"); //reads in lines from the syslog
    std::vector <std::string> Lines; 
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	//struct for the database connection details, replace with your login info
	data.mysql_details.server = "localhost";
	data.mysql_details.user = "andrew";
	data.mysql_details.password = "7nry6395";
	data.mysql_details.database = "IDS";

	//conn holds the connection to the database, pass to query function 
	conn = data.mysql_connection_setup();


    Lines = readIn.read(); // this returns a vector of type string that holds all the lines from the syslog

	/*
	* This giant mess is me trying to get a correctly formatted timestamp for my mysql table
	* this is mysql timestamp formatting fyi
	*/

	std::string protoDate = Lines.front().substr(0,15); //all time relavent data in the syslog is in the first 15ish line
	std::string month; //i dont give 2 shits about months after this class is over which is why i only went through may

	if(protoDate.substr(0, 3) == "Mar")
		month = "03";
	else if(protoDate.substr(0, 3) == "Apr")
		month = "04";
	else	
		month = "05";
	std::string day = protoDate.substr(4,2);
	if(day.find(" ") != std::string::npos) // the timestamp format requires 2 digits for the day
		day.replace(0, 1, "0");				//  so this if statment "should" add a 0 to the number if its below 10
	std::string times = protoDate.substr(7); //the time in hours minutes and seconds is already correctly formated so we can just take it 
	std::string date = "2021-"+month+"-"+day+" "+times; //this should end up being a correctly formatted timestamp

	
    Lines = format.outputCSV(Lines); //this formats the lines in what i guessed was proper csv formatting, it probably isnt right though
	srand(time(NULL)); //this sets a seed for random numbers
	/*
	* the next few lines just comes up with a random number between 1 and 1000 so i can get somewhat unique table names for each log
	*/
	int randNum = (rand() %1000 +1);
	std::ostringstream ostr;
	ostr << randNum;
	std::string name = "syslog"+ostr.str(); //ends up being syslog166 or something to that effect, this will be the table name that holds
	//std::cout << name << std::endl;  			the syslog lines
	
	//this next line hold the command that actually creates our table
	std::string com = "create table "+name+" (ID int not null auto_increment, Line varchar(255), primary key (ID));";
	char char_arr[com.length()+1];
	strcpy(char_arr, com.c_str());
	
	//the execut query function takes an array of type char so the last 2 lines just take the string and turn it into a char array
	//this next line executes our command and creates the table 
	data.mysql_execute_query(conn, char_arr);
	//this for loop should add all our lines from the syslog vector to the table we created

    while(Lines.size()!=0)
    {
        com = "insert into "+name+" (Line) values (\""+Lines.back()+"\");";
		char char_arr[com.length()+1];
		strcpy(char_arr, com.c_str());
		data.mysql_execute_query(conn, char_arr);
		Lines.pop_back();
    }
	//these next lines add a row to a table that holds names and timestamps of all our syslog tables so we can find them by timestamp
	//its also where i use the timestamp i tried to make with the ugly block of code above so that may be one reason im getting issues
	com = "insert into SyslogTableNames(TableName, StartTime, EndTime) values (\""+name+"\", \""+date+"\", CURRENT_TIMESTAMP());";
	char_arr[com.length()+1];
	strcpy(char_arr, com.c_str());
	data.mysql_execute_query(conn, char_arr);
	
}

void parseSysResources()
{
	database data;
    MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	sysCalls call;
	std::vector <std::string> resources;

	//struct for the database connection details, replace with your login info
	data.mysql_details.server = "localhost";
	data.mysql_details.user = "andrew";
	data.mysql_details.password = "7nry6395";
	data.mysql_details.database = "IDS";

	//conn holds the connection to the database, pass to query function 
	conn = data.mysql_connection_setup();

	srand(time(NULL)); //this sets a seed for random numbers
	/*
	* the next few lines just comes up with a random number between 1 and 1000 so i can get somewhat unique table names for each log
	*/
	int randNum = (rand() %1000 +1);
	std::ostringstream ostr;
	ostr << randNum;
	std::string name = "sysres"+ostr.str();

	std::string com = "insert into SysResourceTableNames(TableName) values (\""+name+"\");";
	char char_arr[com.length()+1];
	strcpy(char_arr, com.c_str());
	data.mysql_execute_query(conn, char_arr);

	com = "create table "+name+" (ID int not null auto_increment, Line varchar(255), primary key (ID));";
	char_arr[com.length()+1];
	strcpy(char_arr, com.c_str());
	data.mysql_execute_query(conn, char_arr);

	resources = call.resourceCollect();

	while(resources.size() !=0)
	{
		com = "insert into "+name+"(Line) values (\""+resources.back()+"\");";
		char char_arr2[com.length()+1];
		strcpy(char_arr2, com.c_str());
		data.mysql_execute_query(conn, char_arr2);
		resources.pop_back();
	}
}

int main(int argc, char *argv[])
{
    /*
	*
	* feel free to ignore everything in the main method as its all just garbage test code
	* the call to parseSysLog is at the end
	*
	*
	*
	*
	*/
    SysLogFormatter format;
    std::vector <std::string> myList;
    sysCalls table;
    database data;
    MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	//struct for the database connection details, replace with your login info
	data.mysql_details.server = "localhost";
	data.mysql_details.user = "andrew";
	data.mysql_details.password = "7nry6395";
	data.mysql_details.database = "IDS";

	//conn holds the connection to the database, pass to query function 
	conn = data.mysql_connection_setup();
	database *dataB = &data;
/*
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
    
    
   
	std::thread sysres(parseSysResources);
	parseSysLog(); 
	sysres.join();
    
    return 0;
}
