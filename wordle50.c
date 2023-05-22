#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LIST_SIZE 1000

bool string_is_number(string text);
int string_to_int(string number_text);

int main(int argc, string argv[])
{
	// Check if user gave command line argument; if not print error message
	if(argc != 2)
	{
		printf("Usage: ./wordle50 wordsize\n");
		return 1;
	}

	string command_line_input = argv[1];

	// Check if command line argument is a number or has alphabetic letters
	if(!string_is_number(command_line_input))
	{
		printf("Error: wordsize must be either 5, 6, 7, or 8\n");
		return 1;
	}

	// Get command line argument and conver it to number
	int wordsize = string_to_int(argv[1]);

	if (wordsize < 5 || wordsize > 8)
	{
		printf("Error: wordsize must be either 5, 6, 7, or 8\n");
		return 1;
	}
	
	// Concatenate the number to the path string
	char file_name[20];
	sprintf(file_name, "./word_lists/%i.txt", wordsize);

	// Open the appropriate word list
	FILE* list_pointer = fopen(file_name, "r");

	// File cannot be opened
	if(list_pointer == NULL)
	{
		printf("Error: file not found!\n");
		return 1;
	}

	// Read words into a char array
	char word_list[LIST_SIZE][wordsize + 1];

	for(int i = 0; i < LIST_SIZE; i++)
	{
		fscanf(list_pointer, "%s", word_list[i]);
	}

	// Select the secret word randomly
	srand(time(NULL));

	string secret_word = word_list[rand() % LIST_SIZE];

	printf("%s\n", secret_word);

	// Start the game's main loop

	// Get a guess from user as string; get_guess()

	// Compare the guessed word with the secret word

	// Print informtaion
}

// Check if the string contains other characters then digits; if so return false
bool string_is_number(string text)
{
	// Iterate through the string
	for(int char_index = 0, string_length = strlen(text); char_index < string_length; char_index++)
	{
		// Check if character is not digit (0,1,2....) 
		if(!isdigit(text[char_index]))
		{
			return false;
		}
	}

	return true;
}

// Convert string number to integer
int string_to_int(string number_text)
{
	int number_int = 0;

	int power_of_ten = 1;

	for(int char_place = strlen(number_text); char_place > 0;)	
	{
		char_place--;

		number_int += (number_text[char_place] - 48) * power_of_ten;
	
		power_of_ten *= 10;
	}
	
	return number_int;
}