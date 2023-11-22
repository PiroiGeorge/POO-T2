#ifndef HANGMAN_H
#define HANGMAN_H

#include <string>
#include <vector>
#include <memory>
#include "Letter.h"

class Hangman {
private:
	std::string Secret_word;
	std::string Partial_word;
	std::vector<char> Tried_letters;
	int Trys;
	std::shared_ptr<Letter> LetterInstance;

public:
	// Constructor with parameters to initialize the Hangman object
	Hangman(const std::string secret_word, int trys);

	// Assignment operator overload
	Hangman& operator=(const Hangman& other);

	// Virtual function specific to the Hangman class
	void VirtualFunction() const;

	// Display the current game status
	void ShowGameStatus() const;

	// Handle the guessing of a letter
	void GuessLetter(char letter);

	// Check if the game is won
	bool GameWon() const;

	// Check if the game has ended (won or lost)
	bool GameEnd() const;

	// Function to guess a letter in the word
	bool GuessLetterInWord(char letter);

	// Generate a random word for the game
	static std::string GenerateRandomWord();

	// Clear the console screen (platform-specific)
	static void ClearScreen();
};

#endif // HANGMAN_H
