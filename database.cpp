#include <iostream>
#include <mysql/mysql.h>

struct connection_details{
	const char *server, *user, *password, *database;
};

// creates a connection to the database and returns it for use in query function
MYSQL* mysql_connection_setup(struct connection_details mysql_details){
	MYSQL *connection = mysql_init(NULL);
	
	if(!mysql_real_connect(connection, mysql_details.server, mysql_details.user, mysql_details.password,
	mysql_details.database, 0, NULL, 0))
	{
		std::cout << "Connection Error: " << mysql_error(connection) << std::endl;
		exit(1);
	}
	
	return connection;
}

// runs queries on the database and returns a result, will have to create another class possibly to enter data into database
MYSQL_RES* mysql_execute_query(MYSQL *connection, const char *sql_query){
	if (mysql_query(connection, sql_query)){
		std::cout << "MySQL Query Error: " << mysql_error(connection) << std::endl;
		exit(1);
	}

	return mysql_use_result(connection);
}

int main(int argc, char const *argv[])
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	//struct for the database connection details, replace with your login info
	struct connection_details mysqlD;
	mysqlD.server = "localhost";
	mysqlD.user = "andrew";
	mysqlD.password = "7nry6395";
	mysqlD.database = "IDS";

	//conn holds the connection to the database, pass to query function 
	conn = mysql_connection_setup(mysqlD);

	//res being the result from the database, replace string with whatever query you want to run
	res = mysql_execute_query(conn, "select * from HASH_VALUES;");

	std::cout << "Displaying database output of HASH_VALUES: " << std::endl;

	//loops through res and couts the lines returned from the query, will change eventually to output to whatever is needed
	while((row = mysql_fetch_row(res)) != NULL)
	{
		std::cout << row[0] << "|" << row[1] << "|" << row[2] << std::endl;
	}

	//frees up memory and closes database connection
	mysql_free_result(res);
	mysql_close(conn);

	return 0;
}
