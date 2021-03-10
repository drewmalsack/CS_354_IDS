#include <iostream>
#include <mysql/mysql.h>
#include "database.h"

// creates a connection to the database and returns it for use in query function
MYSQL* database::mysql_connection_setup(){
	MYSQL *connection = mysql_init(NULL);
	
	if(!mysql_real_connect(connection, mysql_details.server, mysql_details.user, mysql_details.password,
	mysql_details.database, 0, NULL, 0))
	{
		std::cout << "Connection Error: " << mysql_error(connection) << std::endl;
		exit(1);

		/*
		if(!mysql_details.password){
			std::cout << "Password Entered incorretly" << std::endl;
			exit(1);
		} else if(!mysql_details.user){
			std::cout << "Username not registered" << std::endl;
			exit(1);
		} else {
			std::cout << "Connection Error: " << mysql_error(connection) << std::endl;
			exit(1);
		}
		*/

		/*
		ifstream fileReader(Alert_Rules.txt, ios::in);
		int ruleNum;
		string rule;

		fileReader >> ruleNum;
		fileReader >> rule;

		string ruleAlert = new string[4];
		for(int i = 0; i = 4; i++){
		fileReader >> ruleAlert[i];
		}
		fileReader.close();
		
		if(!mysql_details.password){
			std::cout << ruleAlert[3] << std::endl;
			exit(1);
		} else if(!mysql_details.user){
			std::cout << ruleAlert[2] << std::endl;
			exit(1);
		} else {
			std::cout << "Connection Error: " << mysql_error(connection) << std::endl;
			exit(1);
		}
		
		*/
	}
	
	return connection;
}

// runs queries on the database and returns a result, will have to create another class possibly to enter data into database
MYSQL_RES* database::mysql_execute_query(MYSQL *connection, const char *sql_query){
	if (mysql_query(connection, sql_query)){
		std::cout << "MySQL Query Error: " << mysql_error(connection) << std::endl;
		exit(1);
	}

	return mysql_use_result(connection);
}


