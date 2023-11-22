#include "Word.h"

// Constructor with a string parameter - initializes the Word object with the provided secret word
Word::Word(const std::string& secretWord) : secretWord(secretWord) {}

// Function to check if a guessed word matches the secret word
bool Word::GuessWord(const std::string& guessedWord) const {
	return secretWord == guessedWord;
}

// Virtual function for demonstrating polymorphism - prints the word represented by this class
void Word::VirtualFunction() const {
	std::cout << "This is a Word class representing the word: " << secretWord << std::endl;
}
