// Created by AJ DiLeo
// For use in CS211 Fall 2023 ONLY

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS_SIZE 100

typedef struct programmingLanguages {
	int id;
	char* language;
	int year;
	char* creator;
	char* paradigm;
	double popularityIndex;

	int isDeleted; // internal field, not accessible to user
} language_t;

// step 1: create structs for the other two tables: operatingSystems
// and databases
// include internal field

typedef struct operatingSystems {
	int id;
	char* name;
	int year;
	char* developer;
	char* kernelType;
	int isDeleted;

} os_t;

typedef struct databases {
	int id;
	char* name;
	int year;
	char* type;
	char* developer;
	int isDeleted;

} db_t;


// step 2: create typedef struct for storing metadata
typedef struct metadata {
	int count;
	int nextIndex;
	int maxCount;
} meta_t;


// step 3: declare the two other arrays of structs
// programmingLanguages has been defined for you already
// TODO: add operatingSystems and databases
language_t* programmingLanguages;
os_t* operatingSystems;
db_t* databases;

// step 4: declare 3 metadata structs, one for each table
meta_t* languageMeta;
meta_t* osMeta;
meta_t* dbMeta;

// step 5: jump to L167


// This function takes the user's input and splits it by spaces
// into an array of strings, ignoring spaces that are wrapped in quotes
// There is no need to modify this code.
// You do not need to understand this code
// but you are welcome to research its application
void splitInput(char* input, char** args, int* arg_count) {
    *arg_count = 0;
    int in_quotes = 0; // Flag to track whether we are inside quotes
    char* token_start = input;

    for (char* ptr = input; *ptr != '\0'; ptr++) {
        if (*ptr == '"') {
            in_quotes = !in_quotes; // Toggle the in_quotes flag when a quote is encountered
        }

        if ((*ptr == ' ' || *ptr == '\n') && !in_quotes) {
            // If not inside quotes and a space or newline is found, consider it as a separator
            *ptr = '\0'; // Replace space or newline with null terminator
            args[(*arg_count)++] = token_start;
            token_start = ptr + 1; // Start of the next token
        }
    }

    // Add the last token (if any) after the loop
    if (*token_start != '\0') {
        // Remove leading and trailing double quotes if they exist
        if (token_start[0] == '"' && token_start[strlen(token_start) - 1] == '"') {
            token_start[strlen(token_start) - 1] = '\0'; // Remove trailing quote
            args[(*arg_count)++] = token_start + 1; // Remove leading quote
        } else {
            args[(*arg_count)++] = token_start;
        }
    }
    args[*arg_count] = NULL;
}

// step 7: implement setup function
// this function is responsible for dynamically allocating the
// particular table. Use the tables declared on L27.
void setup(char* table, int numRows) {

	if(strcmp(table, "programmingLanguages")  ==  0){
		programmingLanguages = (language_t*)calloc(numRows, sizeof(language_t));
		languageMeta = (meta_t*)malloc(sizeof(meta_t));
		languageMeta->maxCount = numRows;

	}

	else if(strcmp(table, "operatingSystems") == 0 ){
		operatingSystems = (os_t*)calloc(numRows, sizeof(os_t));
		osMeta = (meta_t*)malloc(sizeof(meta_t));
		osMeta->maxCount = numRows;

	}
	
	else if(strcmp(table, "databases") ==0){ 
		databases = (db_t*)calloc(numRows, sizeof(db_t));
		dbMeta = (meta_t*)malloc(sizeof(meta_t));
		dbMeta->maxCount = numRows;
		
	}
	else { return;}
	
	// DO NOT TOUCH THIS PRINT
	// REQUIRED FOR AUTOGRADER
	printf("setup complete\n");
}

// step 8: implement insert function
// this function is responsible for updating the corresponding
// fields of the struct located at the next available index
// make sure to use and update your metadata.

// autograder print for insufficient capacity:
// fprintf(stderr, "cannot insert due to insufficient capacity.\n");
void insert(char** args) {
	char* table = strdup(args[1]);
	printf("%s", table);
	printf("%s","\n");
	
	// DO NOT TOUCH THIS PRINT
	// REQUIRED FOR AUTOGRADER
	if(strcmp(table, "programmingLanguages")  ==  0){
		if(languageMeta->count == languageMeta->maxCount){ 
			printf("%s", "cannot insert due to insufficent space.\n");
			return;
		}
		((*(programmingLanguages+(languageMeta->nextIndex))).id) = atoi(args[2]);
		((*(programmingLanguages+(languageMeta->nextIndex))).language)= strdup(args[3]);
		programmingLanguages[languageMeta->nextIndex].year = atoi(args[4]);
		((*(programmingLanguages+languageMeta->nextIndex)).creator)=  strdup(args[5]);
		((*(programmingLanguages+languageMeta->nextIndex)).paradigm)= strdup(args[6]);
		programmingLanguages[languageMeta->nextIndex].popularityIndex = atof(args[7]);
		programmingLanguages[languageMeta->nextIndex].isDeleted = 0; 

		languageMeta->count++;
		languageMeta->nextIndex++;
	
	}

	else if(strcmp(table, "operatingSystems") == 0){
		if(osMeta.count == osMeta.maxCount){ 
			printf("%s","cannot insert due to insufficent space.\n");
			return;
		}
		operatingSystems[osMeta.nextIndex].id = atoi(args[2]);
		operatingSystems[osMeta.nextIndex].name = strdup(args[3]);
		operatingSystems[osMeta.nextIndex].year = atoi(args[4]);
		operatingSystems[osMeta.nextIndex].developer = strdup(args[5]);
		operatingSystems[osMeta.nextIndex].kernelType = strdup(args[6]);
		operatingSystems[osMeta.nextIndex].isDeleted = 0;
		osMeta.count++;
		osMeta.nextIndex++; 
	}
	
	else if(strcmp(table, "databases") == 0){ 
		if(dbMeta.count == dbMeta.maxCount){ 
			printf("%s","cannot insert due to insufficent space.\n");
			return;
		}
		databases[dbMeta.nextIndex].id = atoi(args[2]);
		databases[dbMeta.nextIndex].name = strdup(args[3]);
		databases[dbMeta.nextIndex].year = atoi(args[4]);
		databases[dbMeta.nextIndex].type = strdup(args[5]);
		databases[dbMeta.nextIndex].developer = strdup(args[6]);
		databases[dbMeta.nextIndex].isDeleted = 0;
		dbMeta.count++;
		dbMeta.nextIndex++; 
	}
	else {  printf("%s","no match.\n"); return;}

	printf("insert complete\n");
}

// step 9: implement soft delete function
// this function is responsible for marking a record as deleted
// you should be updating an internal field flag so that get will
// not display this record. 
// You should not be attempting to free/overwrite this record - it remains alloc
// with a updated field
// make use of your metadata
void delete(char* table, int id) {
	if(strcmp(table, "programmingLanguages") == 0)
	{
		for(int i = 0; i < languageMeta.count; i++)
		{
			if(programmingLanguages[i].id == id)
			{
				programmingLanguages[i].isDeleted = 1;
				break;
			}
		}
	}
	else if(strcmp(table, "operatingSystems") == 0)
	{
		for(int i = 0; i < osMeta.count; i++)
		{
			if(operatingSystems[i].id == id)
			{
				operatingSystems[i].isDeleted = 1;
				break;
			}
		}


	}
	else if(strcmp(table, "databases") == 0)
	{
		for(int i = 0; i < dbMeta.count; i++)
		{
			if(databases[i].id == id)
			{
				databases[i].isDeleted = 1;
				break;
			}
		}

	}
	else{
		return;
	}
	// DO NOT TOUCH THIS PRINT
	// REQUIRED FOR AUTOGRADER
	printf("delete complete\n");
}

// step 10: implement modify function
// this function is responsible for overwriting all of the contents of all
// records that match an ID.
// make use of your metadata
// !!!NOTE: The structs store pointers. Make sure to free any allocated
// memory before overwriting it!!!
void modify(char** args) {
	char* table = args[1];
	int id = atoi(args[2]);

	// DO NOT TOUCH THIS PRINT
	// REQUIRED FOR AUTOGRADER
if(strcmp(table, "programmingLanguages")  ==  0){

	for(int i = 0; i < languageMeta.count; i++)
		{
			if(programmingLanguages[i].id == id)
			{
				programmingLanguages[i].id = atoi(args[3]);
				free(programmingLanguages[i].language);
				programmingLanguages[i].language = strdup(args[4]);
				programmingLanguages[i].year = atoi(args[5]);
				free(programmingLanguages[i].creator);
				programmingLanguages[i].creator = strdup(args[6]);
				free(programmingLanguages[i].paradigm);
				programmingLanguages[i].paradigm = strdup(args[7]);
				programmingLanguages[i].popularityIndex = atof(args[8]);
				break;
			}
	}
}
	else if(strcmp(table, "operatingSystems") == 0){
		for(int i = 0; i < osMeta.count; i++){
			if(operatingSystems[i].id == id){
				operatingSystems[i].id = atoi(args[3]);
				free(operatingSystems[i].name);
				operatingSystems[i].name = strdup(args[4]);
				operatingSystems[i].year = atoi(args[5]);
				free(operatingSystems[i].developer);
				operatingSystems[i].developer = strdup(args[6]);
				free(operatingSystems[i].kernelType);
				operatingSystems[i].kernelType = strdup(args[7]);
				break;
			}
		}

	}
	
	else if(strcmp(table, "databases") == 0){ 
		for(int i = 0; i < dbMeta.count; i++){
			if(databases[i].id == id){
				databases[i].id = atoi(args[3]);
				free(databases[i].name);
				databases[i].name = strdup(args[4]);
				databases[i].year = atoi(args[5]);
				free(databases[i].type);
				databases[i].type = strdup(args[6]);
				free(databases[i].developer);
				databases[i].developer = strdup(args[7]);
				break;
			}
		}


	}
	else {  printf("%s","no match.\n"); return;}

	printf("modify complete\n");
}

// step 11: implement get function
// this function is responsible for fetching all non-deleted records
// make use of your metadata
// Make sure to follow guidelines for format in writeup
// see examples as well
// Use %lf for formatting double data type
void get(char* table) {
	
	if(strcmp(table, "programmingLanguages")  ==  0){
		printf("id,language,year,creator,paradigm,popularityIndex\n");
		for(int i = 0; i < languageMeta.count; i++)
		{
			if(programmingLanguages[i].isDeleted == 0)
			{
				printf("%d", programmingLanguages[i].id);
				printf(",");
				printf("%s",programmingLanguages[i].language);
				printf(",");
				printf("%d", programmingLanguages[i].year);
				printf(",");
				printf("%s",programmingLanguages[i].creator);
				printf(",");
				printf("%s",programmingLanguages[i].paradigm);
				printf(",");
				printf("%lf", programmingLanguages[i].popularityIndex);
				printf("\n");
			}
		}
	}

	else if(strcmp(table, "operatingSystems") == 0 ){
		printf("id,name,year,developer,kernelType\n");
		for(int i = 0; i < osMeta.count; i++)
		{
			if(operatingSystems[i].isDeleted == 0)
			{
				printf("%d", operatingSystems[i].id);
				printf(",");
				printf("%s",operatingSystems[i].name);
				printf(",");
				printf("%d", operatingSystems[i].year);
				printf(",");
				printf("%s",operatingSystems[i].developer);
				printf(",");
				printf("%s",operatingSystems[i].kernelType);
				printf("/n");
	
			}
		}
	}
	
	else if(strcmp(table, "databases") == 0){ 
		printf("id,name,year,type,developer\n");
		for(int i = 0; i < dbMeta.count; i++)
		{
			if(databases[i].isDeleted == 0)
			{
				printf("%d", databases[i].id);
				printf(",");
				printf("%s",databases[i].name);
				printf(",");
				printf("%d", databases[i].year);
				printf(",");
				printf("%s",databases[i].type);
				printf("%s",databases[i].developer);
				printf("/n");
	
			}
		}
	
	}
	else { return;}
}

// step 12: implement exit function
// this function should free all allocated memory
// Make sure to avoid memory leaks by freeing any allocated memory
// inside a struct (char*) before freeing the struct pointer
void exitProgram() {
	for(int i; i < languageMeta.maxCount; i++)
	{
		free((programmingLanguages + i)->language);
		free((programmingLanguages + i)->creator);
		free((programmingLanguages + i)->paradigm);
		free(programmingLanguages + i);
	}
	free(programmingLanguages);
	//free(languageMeta);

	for(int i; i < osMeta.maxCount; i++)
	{
		free((operatingSystems + i)->name);
		free((operatingSystems + i)->developer);
		free((operatingSystems + i)->kernelType);
		free(operatingSystems + i);
	}
	free(operatingSystems);
	//free(osMeta);

	for(int i; i < dbMeta.maxCount; i++)
	{
		free((databases + i)->name);
		free((databases + i)->type);
		free((databases + i)->developer);
		free(databases + i);
	}
	free(databases);
	//free(dbMeta);

	
}

// this code is responsible for parsing the user's
// input, and determining based on the command
// which function to send it to.
// You do not have to modify this code, but you should
// understand it.
void execute_cmd(char** args, int arg_count) {
	char* cmd = args[0];
	if (strcmp(cmd, "setup") == 0) {
		setup(args[1], atoi(args[2]));
	} else if (strcmp(cmd, "insert") == 0) {
		insert(args);
	} else if (strcmp(cmd, "delete") == 0) {
		delete(args[1], atoi(args[2]));
	} else if (strcmp(cmd, "modify") == 0) {
		modify(args);
	} else if (strcmp(cmd, "get") == 0) {
		get(args[1]);
	} else if (strcmp(cmd, "exit") == 0) {
		exitProgram();
	} else {
		printf("\n");
	}
}

// step 6: initialize the default metadata values here
// jump to L76
void initializeMetadata() {
	languageMeta.count = 0;
	languageMeta.nextIndex = 0;

	osMeta.count = 0;
	osMeta.nextIndex = 0;

	dbMeta.count = 0;
	dbMeta.nextIndex = 0;
	
}

// this code creates the interactive shell
// you do not need to modify this
// You do not need to understand this code
// but you are welcome to research its application
void cmd_loop() {
	char input[MAX_INPUT_SIZE];
    ssize_t bytes_read;
	printf("Usage: \n");
	printf("setup {table} {numRows}\n");
	printf("insert {table} {data}\n");
	printf("delete {table} {id}\n");
	printf("modify {table} {id} {data}\n");
	printf("get {table}\n\n");
	initializeMetadata();
    while (1) {
        printf("CS211> ");
		fflush(stdout);
        
        // Read user input using the read() system call
        bytes_read = read(STDIN_FILENO, input, sizeof(input));
        
        if (bytes_read == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        
        if (bytes_read == 0) {
			printf("\n");
            break;
        }
        
        // Null-terminate the input
        input[bytes_read] = '\0';

		char** args = (char**)malloc(MAX_ARGS_SIZE * sizeof(char*));
		int arg_count;

		splitInput(input, args, &arg_count);
        
        // Execute the user's command
        execute_cmd(args, arg_count);
		free(args);
    }
}


int main() {
	cmd_loop();
}