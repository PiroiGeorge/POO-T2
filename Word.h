#ifndef WORD_H
#define WORD_H

#include "GamesElements.h"  // Include the GameElements base class
#include <string>

class Word : public GameElements {
private:
	std::string secretWord;  // The secret word that needs to be guessed in the game

public:
	// Constructor that initializes the Word object with a given secret word
	Word(const std::string& secretWord);

	// Function to check if a guessed word matches the secret word
	bool GuessWord(const std::string& guessedWord) const;

	// Override of the virtual function from GameElements - used for polymorphic behavior
	void VirtualFunction() const override;
};

#endif // WORD_H
