#include "liste.h"

int	main(int argc, const char **argv)
{
	printf("hello\n");
	dbConfig_lt *dbConfig_lt = malloc(sizeof(dbConfig_lt));
	export_lt *export_lt = malloc(sizeof(export_lt));
	if(dbConfig_lt == NULL){
		fprintf(stderr, "Allocation error");
		exit(EXIT_FAILURE);
	}

	dbConfig_lt->server = SERVER;
	dbConfig_lt->username = USERNAME;
	dbConfig_lt->hostname = HOSTNAME;
	dbConfig_lt->password = PASSWORD;
	export_lt->dirPath = DIRPATH;

	MYSQL *mysql = mysql_init(NULL);
	
	if(mysql == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(mysql));
		exit(EXIT_FAILURE);
	}

	if(mysql_real_connect(mysql, dbConfig_lt->server, dbConfig_lt->username, dbConfig_lt->password, dbConfig_lt->hostname, 0, NULL, 0))
	{

		export_lt->mysql = mysql;
		readExport(export_lt);
		mysql_close(mysql);
	}else{
		fprintf(stderr, "%s\n", mysql_error(mysql));
		mysql_close(mysql);
		exit(EXIT_FAILURE);
	}
	
	
	free(dbConfig_lt);
	return EXIT_SUCCESS;
}
