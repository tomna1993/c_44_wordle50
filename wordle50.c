#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LIST_SIZE 1000

#define EXACT 2
#define CLOSE 1
#define WRONG 0

bool string_is_number(string text);
int string_to_int(string number_text);
string get_guess(int word_length);
int check_word(string word1, string word2, int word_length, int score[]);

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

	// Chose randomly a secret word
	srand(time(NULL));

	string secret_word = word_list[rand() % LIST_SIZE];

	printf("%s\n", secret_word);

	// Start the game's main loop
	
	// Create array to save each letter's score
	int status[wordsize];
	// Set each element to 0
	for(int i = 0; i < wordsize; i++)
	{
		status[i] = 0;
	}
	
	// Get a guess from user as string; get_guess()
	string user_guess_word = get_guess(wordsize);

	// Compare the guessed word with the secret word
	int score = check_word(user_guess_word, secret_word, wordsize, status);

	printf("Score = %i\n", score);

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

// Get string from user
string get_guess(int word_length)
{
	string user_guess;

	bool correct_user_input;	

	do
	{
		// If user input is correct it stays true; otherwise change to false and ask for new user input
		correct_user_input = true;

		// Get user input as string
		user_guess = get_string("Input a %i-letter word: ", word_length);

		// Save the length of user input
		int string_length = strlen(user_guess); 

		// Check if user's word is same length as the secret word
		if (string_length != word_length)
		{
			correct_user_input = false;
			continue;
		}
		
		// Iterate through user input characters
		for(int char_index = 0; char_index < string_length; char_index++)
		{
			// Change any uppercase letter to lowercase
			user_guess[char_index] = tolower(user_guess[char_index]);

			// If character is not alphabetic ask for a new word (user input)	
			if(!isalpha(user_guess[char_index]))
			{
				correct_user_input = false;	
				break;
			}
		}

	// If user's word correct leave the loop
	} while (correct_user_input == false);

	return user_guess;
}

int check_word(string guess_word, string secret_word, int word_length, int letter_status[])
{
	int score_sum = 0;

	// Check if some of the letters are matching in correct place
	for(int i = 0; i < word_length; i++)
	{
		if(guess_word[i] == secret_word[i])
		{
			letter_status[i] = EXACT;
		}

		score_sum += letter_status[i];
	}

	if(score_sum == (word_length * 2))
	{
		return score_sum;
	}

	int letter_close[word_length];

	for(int i = 0; i < word_length; i++)
	{
		letter_close[i] = 0;
	}

	// Check the not matching letters for CLOSE and WRONG scores
	for(int i = 0; i < word_length; i++)
	{
		// If the letter in guessed word and secret word match check the next letter
		if(letter_status[i] == 2)
		{
			continue;
		}

		// Check if guessed word's letters are in the secret word 
		for(int j = 0; j < word_length; j++)
		{
			if(guess_word[i] == secret_word[j] && letter_close[j] == 0)
			{
				letter_status[i] = CLOSE;

				score_sum += letter_status[i];

				// Mark letter to be checked once
				letter_close[j] = 1;

				break;
			}
		}
	}

	return score_sum;
}
