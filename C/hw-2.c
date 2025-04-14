#include <stdio.h>
#include <stdlib.h>

// Take in a delimiter and string
// Split the string at the delims
// Put the substrings in a char **
// Return the char **
// Do not use string.h

// Declaration
char ** parse(char, char *);
int stringLength(char *);
int checkInside(char, char *);


// Main Method
int main(int argc, char ** argv) {
	// Check if delimiter is inside of the string and return true or false as a 0 or 1
	int inside = checkInside(argv[1][0], argv[2]);
    int length = stringLength(argv[2]);

	// If there is not less or more arguements proceed with parsing
	if (argc == 3 && inside == 1) {
    	char ** subStrings = malloc(length * sizeof(char *));
		subStrings = parse(argv[1][0], argv[2]);

		// For statement that prints the substrings and lengths
		for (int i = 0; subStrings[i] != NULL; i++) {
			printf("%s\n", subStrings[i]);
		}

		// Free up every slot in subStrings
		for (int i = 0; subStrings[i] != NULL; i++) {
			free(subStrings[i]);
		}
		free(subStrings);

		// Else statement that prints if the user has too many/less arguements or just no correct delimiter
	} else {
		printf("You entered %d number of arguments or your string does not have the delimiter. \n", argc);
    	printf("Enter the correct number of arguments or the correct delimiters.");
	}
}


// Helper function that checks if the delimiter is actually inside of the string
int checkInside(char delim, char * parseString) {
	// Boolean using 0 and 1
	int inside = 0;
	int length = stringLength(parseString);

	// Null terminate the char * fullString coming in
	parseString[length] = '\0';

	// For statement that checks if the delimiter is inside the string
	for (int i = 0; parseString[i] != '\0'; i++) {
		if (parseString[i] == delim) {
			inside = 1;
		}
	}

	// Return true or false in an int
	return inside;
}


// Parse function that takes the full string and then parses it into a list with it's length
char ** parse(char delim, char * parseString) {

	// Declarations
	int count = 0;
    int listCounter = 0;
    int separateCounter = 0;
    int length = stringLength(parseString);

  	// Null terminate the char * fullString coming in
    parseString[length] = '\0';


	// Create a list for the strings
	char ** parsedList = malloc(length * sizeof(char *));

  	// Create a temp string as "parseSeparateStrings"
    char * parseSeparateStrings = malloc(length * sizeof(char));

	// While loop that loops until null terminated
	while (parseString[count] != '\0') {

		// If the current character isn't a delim add to the temp string and null terminate
		if (parseString[count] != delim) {
			parseSeparateStrings[separateCounter] = parseString[count];

			// Had to null terminate because there were weird characters popping up
			parseSeparateStrings[separateCounter+1] = '\0';
			separateCounter++;
		}

		// If we occur on a delim or a null, reset the temp counter and temp string, save to list
		// Had to malloc each index for better memory output
		if (parseString[count] == delim || parseString[count+1] == '\0') {
			parsedList[listCounter] = malloc((separateCounter + 10) * sizeof(char));

			// I did search how to do this up, it just adds two variables with format specifers into a single string
			sprintf(parsedList[listCounter], "%s Length %d", parseSeparateStrings, separateCounter);

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
