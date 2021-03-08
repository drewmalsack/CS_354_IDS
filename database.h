#include<iostream>
#include <mysql/mysql.h>

class database
{
    public:
        MYSQL* mysql_connection_setup();
        MYSQL_RES* mysql_execute_query(MYSQL*, const char*);
        struct connection_details{
	        const char *server, *user, *password, *database;
        };
        connection_details mysql_details;

};