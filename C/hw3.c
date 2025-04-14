#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

// Initialize functions
char ** parse(char delim, char * word);
void pointerPrint(char ** argv);
char * checkString(char ** parsedInput, char ** path, char * input, int again);
void exec(char * pathToFile, char ** parsedInput);
int stringLength (char * string);

// Main
int main(int argc, char ** argv, char ** envp){

	// Create a string for the parsedString with "PATH" in it
	char * parseString = malloc(sizeof(char));
	for (int i = 0; envp[i] != NULL; i++) {
		if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T' && envp[i][3] == 'H') {
				parseString = envp[i];
			}
		}

	// Create it into a string list called subStrings
	char ** subStrings = malloc(sizeof(char *));
	subStrings = parse(*":", parseString);

	// Use pointerprint function to print it out
	pointerPrint(subStrings);

	// Loop it however many times you want to (until CTRL + C)
	int loop_boolean = 0;
	int again = 0;
	while (loop_boolean == 0) {
		char * input = malloc(100 * sizeof(char));
		printf("\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
		$$$$$$$$\n\n");
		printf("SUPER BASH (CTRL + C to quit) $");
		scanf("%[^\n]%*c", input); // reads input until a new line
		symbol, then the newline is discarded

		// Parses the input into ls -a -h etc..
		char ** parseInput = malloc(sizeof(char *));
		parseInput = parse(*" ", input);;

		// Function that checks the file location, grabs it and then saves it as path
		char * path = checkString(parseInput, subStrings, input, again);
		pointerPrint(parseInput);

		// Execute it
		exec(path, parseInput);

		// Put the again counter to +1
		again++;
	}
}
// Parse function that takes the full string and then parses it into a list with it's length
char ** parse(char delim, char * word) {

	// Declarations
	int count = 0;
	int listCounter = 0;
	int separateCounter = 0;
	int length = stringLength(word);

	// Null terminate the char * fullString coming in
	word[length] = '\0';

	// Create a list for the strings
	char ** parsedList = malloc(length * sizeof(char *));

	// Create a temp string as "parseSeparateStrings"
	char * parseSeparateStrings = malloc(length * sizeof(char));

	// While loop that loops until null terminated
	while (word[count] != '\0') {

		// If the current character isn't a delim add to the temp string and null terminate
		if (word[count] != delim) {
			parseSeparateStrings[separateCounter] = word[count];

		/	/ Had to null terminate because there were weird character popping up
			parseSeparateStrings[separateCounter+1] = '\0';
			separateCounter++;
		}
		// If we occur on a delim or a null, reset the temp counter and temp string, save to list
		// Had to malloc each index for better memory output
		if (word[count] == delim || word[count+1] == '\0') {
			parsedList[listCounter] = malloc((separateCounter + 10) * sizeof(char));

		// I did search how to do this up, it just adds two variables with format specifers into a single string
		sprintf(parsedList[listCounter], "%s", parseSeparateStrings);
		// Reset for the next substring
		separateCounter = 0;
		listCounter++;
		}
	count++;
	}
	// Null terminate the list
	parsedList[listCounter] = NULL;

	// Free up parse separate strings because we don't use it anymore after This
	free(parseSeparateStrings);

	// Return the list
	return parsedList;
}

	// Function that grabs the full string length delimiters included
int stringLength(char * string) {
	int count = 0;
	while(string[count] != '\0') {
		count++;
	}
	return count;
}

// Function that prints the PID, Address, Pointer Value, and the String itself
void pointerPrint(char ** path){
	for (int i = 0; path[i] != NULL; i++) {
		printf("Base[%d] Address %p Pointer Value %p String=%s\n", i, &path[i], &*path[i], path[i]);
	}
}

// Function that does the checking
char * checkString(char ** parsedInput, char ** path, char * input, int again){
	// Initialization
	int i = 0;
	char * found_path = malloc(sizeof(char));
	int result = 0;
	// Until path is null
	while (path[i] != NULL) {
		// Checks if the user is running again, (firist time it creates the concatenated string ex: bin/ls)
		if (again == 0){
			strcat(path[i], "/");
			strcat(path[i], parsedInput[0]);
		}
		// Checking the paths
		printf("Checking: %s\n", path[i]);
		// Checking it to "/bin/ls" (this is only because I could not figure out how to do execv and fork and make it so when execv is ran change that path to found_path
		result = strncmp(path[i], "/bin/ls", strlen(found_path));
		if(result == 0) {
			// Once found, make the next one null because it doesn't matter and then print found and save path
			path[i+1] = NULL;
			printf("FOUND!\n");
			found_path = path[i];
		}
	i++;
	}

	// Grabs the listLength of the parsedList pointers. -ls, -h, -a, -l etc..
	int listLength = 0;
	while (parsedInput[listLength] != NULL) {
		listLength++;
	}

	// Prints string and pointers
	printf("String: '%s'\n", input);
	printf("Number of pointers: %d\n", listLength + 1);

	// Return the path
	return found_path;
}

// Execute function
void exec(char * pathToFile, char ** parsedInput) {
int state;
if(fork() == 0) {
	execv(pathToFile, parsedInput);
	} else {
	wait(&state);
	}
}
