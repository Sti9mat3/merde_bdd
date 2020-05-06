#include "liste.h"

void readExport(export_lt *export_lt){
	DIR* dir = NULL;
	struct dirent *file = NULL;
	
	dir = opendir(export_lt->dirPath);
	if(dir == NULL)
	{
		fprintf(stderr,"error dirpath");
		exit(EXIT_FAILURE);
	}
	
	seekdir(dir, export_lt->offsetDir);
	while((file = readdir(dir)) != NULL){
		export_lt->fileName = strdup(file->d_name);
		export_lt->offsetFile = 0;
		export_lt->offsetDir = telldir(dir);
		readFile(export_lt);
	}			
	
	free(file);
	closedir(dir);
	exit(EXIT_SUCCESS);
}

void readFile(export_lt *export_lt){
	FILE *file = NULL;
	char *fileName = malloc(sizeof(char)*256);
	char *insert = malloc(sizeof(char)*256);
	if(fileName == NULL && insert == NULL)
	{
		fprintf(stderr,"Allocation error");
		exit(EXIT_FAILURE);
	}
	
	strcpy(fileName, export_lt->dirPath);
	strcat(fileName, "/");
	strcat(fileName,export_lt->fileName);

	file = fopen(fileName, "r");
	printf("%s\n", fileName);
	if(file == NULL)
	{
		fprintf(stderr,"Cant open the file");
		exit(EXIT_FAILURE);
	}
	char line[1024];
	fseek(file, export_lt->offsetFile+1, SEEK_SET);
	fgetc(file);

	if(feof(file) != 0)
	{
		readExport(export_lt);
	}

	fseek(file, export_lt->offsetFile, SEEK_SET);
	while(fgets(line, sizeof(line), file) != NULL && export_lt->conflict != 1)
	{printf("toto\n");

		if(strstr(line,"INSERT INTO") != NULL)
		{printf("toto\n");
			strncpy(insert, line, strlen(line)-1);
			insert[strlen(line)-1]='\0';
			export_lt->conflict = mysql_query(export_lt->mysql, insert);
			printf("%d\n",export_lt->conflict);
			printf("%s\n", insert);
			if(!export_lt->conflict)
			{printf("toto\n");
				columnsUser_lt *columnsUser_lt = malloc(sizeof(columnsUser_lt));
				if(columnsUser_lt == NULL)
				{
					fprintf(stderr,"Allocation error");
					exit(EXIT_FAILURE);
				}
				export_lt->columnsUser_lt = columnsUser_lt;
				insertUser(insert, export_lt);
				//selectconflict
	 
			}
		}
	}
	fclose(file);
}

void insertUser(const char *insert, export_lt *export_lt)
{
	printf("insert\n");
	char *id = malloc(sizeof(char)*20);
   	char *lastName = malloc(sizeof(char)*255);
   	char *firstName = malloc(sizeof(char)*255);
   	char *email = malloc(sizeof(char)*255);
  	char *address = malloc(sizeof(char)*255);
   	char *phoneNumber = malloc(sizeof(char)*255);
	char *password = malloc(sizeof(char)*255);
    if(id == NULL || lastName == NULL || firstName == NULL || email == NULL || address == NULL || phoneNumber == NULL || password == NULL) {
        fprintf(stderr,"Allocation error\n");
        exit(EXIT_FAILURE);
    }

    id = strdup(strstr(insert,"(")+1);
    lastName  = strdup(strstr(lastName,"'")+2);
    firstName = strdup(strstr(firstName,",'")+2);
    email = strdup(strstr(email,",'")+2);
    password = strdup(strstr(password,",'")+2); // on remplace le password par password
    address = strdup(strstr(address,",'")+2);
    phoneNumber = strdup(strtok(phoneNumber,","));

    id = strdup(strtok(id,","));
    lastName = strdup(strtok(lastName,"'"));
    firstName = strdup(strtok(firstName,"'"));
    email = strdup(strtok(email,"'"));
    password = strdup(strtok(password,"'"));
    address = strdup(strtok(address,"'"));

    export_lt->columnsUser_lt->id = strdup(id);
    export_lt->columnsUser_lt->lastName = strdup(lastName);
    export_lt->columnsUser_lt->firstName = strdup(firstName);
    export_lt->columnsUser_lt->email = strdup(email);
    export_lt->columnsUser_lt->password = strdup(password);
    export_lt->columnsUser_lt->address = strdup(address);
    export_lt->columnsUser_lt->phoneNumber = strdup(phoneNumber);

    free(id);
    free(lastName);
    free(firstName);
    free(email);
    free(password);
    free(address);
    free(phoneNumber);
}
