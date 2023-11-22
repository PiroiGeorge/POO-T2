#include "Letter.h"
#include <cctype>
#include <iostream>

using namespace std;

// Default constructor - initializes with default values
Letter::Letter() : letter(' '), Secret_word(""), Trys(0) {}

// Constructor with parameters to initialize the Letter object with a specific letter, secret word, and number of tries
Letter::Letter(char l, const string& secret_word, int trys)
	: letter(l), Secret_word(secret_word), Trys(trys) {
	Partial_word = string(secret_word.length(), '_');
}

// Virtual function for demonstrating polymorphism - prints the letter represented by this class
void Letter::VirtualFunction() const {
	cout << "This is a Letter class representing the letter: " << letter << endl;
}

// Function to check if the guessed letter is in the secret word, updates Partial_word if found
bool Letter::GuessLetterInWord(char input) {
	bool LetterFound = false;
	char LowerLetter = tolower(input);
	for (size_t i = 0; i < Secret_word.length(); i++) {
		if (tolower(Secret_word[i]) == LowerLetter) {
			Partial_word[i] = Secret_word[i];
			LetterFound = true;
		}
	}
	return LetterFound;
}

// Function to handle the guessing of a letter, updates the number of tries and the tried letters list
void Letter::GuessLetter(char input) {
	letter = input;

	if (!isalpha(input)) {
		throw std::invalid_argument("Error! Please insert a letter.");
	}

	if (GuessLetterInWord(input)) {
		cout << "Letter " << letter << " exists in the word." << endl;
	}
	else {
		cout << "Letter " << letter << " doesn't exist in the word." << endl;
		Trys--;
	}

	Tried_letters.push_back(letter);
}
