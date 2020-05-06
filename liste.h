

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <my_global.h>
#include <mysql.h>

#define SERVER "localhost";
#define HOSTNAME "home_service";
#define USERNAME "root";
#define PASSWORD "mysql";
#define DIRPATH "/home/stigmate/ESGI/PA/c_bdd/export";

typedef	struct	dbConfig_st
{
	const char *server;
	const char *hostname;
	const char *username;
	const char *password;
}	dbConfig_lt;
	
typedef	struct	columnsUser_st
{
	int id;
	const char *firstName;
	const char *lastName;
	const char *email;
	const char *password;
	const char *address;
	const char *phoneNumber;
}	columnsUser_lt;

typedef	struct	export_st	
{
	const char *dirPath;
	const char *fileName;
	long offsetDir;
	long offsetFile;
	MYSQL *mysql;
	columnsUser_lt *columnsUser_lt;
	int conflict;
}	export_lt;

void readExport(export_lt *export_lt);
void readFile(export_lt *export_lt);
void insertUser(const char *insert, export_lt *export_lt);
