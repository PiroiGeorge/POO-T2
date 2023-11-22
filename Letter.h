#ifndef LETTER_H
#define LETTER_H

#include "GamesElements.h"
#include <vector>
#include <string>
#include <stdexcept>  // Include for std::invalid_argument

class Letter : public GameElements {
private:
	char letter;                     // The letter guessed by the player
	std::string Secret_word;         // The secret word to be guessed in the game
	std::string Partial_word;        // Representation of the secret word showing guessed letters
	std::vector<char> Tried_letters; // Letters that have been guessed so far
	int Trys;                        // Number of tries left for guessing

	// Private method to check if the guessed letter is present in the secret word
	bool GuessLetterInWord(char input);

public:
	// Default constructor - initializes a Letter object with default values
	Letter();

	// Constructor with parameters to initialize the Letter object with a specific letter, secret word, and number of tries
	Letter(char l, const std::string& secret_word, int trys);

	// Override of the virtual function from GameElements - used for polymorphic behavior
	void VirtualFunction() const override;

	// Public method to handle the guessing of a letter, now accepting a char parameter
	void GuessLetter(char input);
};

#endif // LETTER_H
