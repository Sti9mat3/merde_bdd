#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	char *hostname = "home_service";
	char *password = "mysql";
	char *user = "home_service";
	

	char *command = malloc(sizeof(char)*128);

	sprintf(command,"mysqldump -u %s -p%s --skip-triggers --compact --no-create-info --extended-insert=false %s > export/export.sql", user, password, hostname);

	printf("%s\n",command);
	
	system(command);
	
	free(command);
	return 0;
}
