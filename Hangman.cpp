#include "Hangman.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdexcept>

using namespace std;

// Constructor with parameters to initialize the Hangman object
Hangman::Hangman(const string secret_word, int trys) {
	if (secret_word.empty()) {
		throw invalid_argument("Secret word can't be empty");
	}

	this->Secret_word = secret_word;
	this->Partial_word = string(secret_word.length(), '_');
	this->Trys = trys;

	LetterInstance = make_shared<Letter>(' ', secret_word, trys);
}

// Assignment operator overload
Hangman& Hangman::operator=(const Hangman& other) {
	if (this != &other) {
		Secret_word = other.Secret_word;
		Partial_word = other.Partial_word;
		Tried_letters = other.Tried_letters;
		Trys = other.Trys;

		LetterInstance = other.LetterInstance;
	}
	return *this;
}

// Virtual function specific to the Hangman class
void Hangman::VirtualFunction() const {
	cout << "This is a Hangman class representing the game with the word: " << Secret_word << endl;
}

// Display the current game status
void Hangman::ShowGameStatus() const {
	cout << "Word: " << Partial_word << endl;
	cout << "Letters tried: ";
	for (char letter : Tried_letters) {
		cout << letter << " ";
	}
	cout << "\nRemaining tries: " << Trys << endl;
}

// Handle the guessing of a letter
void Hangman::GuessLetter(char letter) {
	try {
		LetterInstance->GuessLetter(letter);

		if (GuessLetterInWord(letter)) {
			cout << "Letter " << letter << " exists in the word!" << endl;
		}
		else {
			cout << "Letter " << letter << " does not exist in the word." << endl;
			Trys--;
		}

		Tried_letters.push_back(letter);
	}
	catch (const invalid_argument& e) {
		// Handle invalid input 
		cerr << "Invalid input: " << e.what() << endl;
	}
}

// Check if the game is won
bool Hangman::GameWon() const {
	return Secret_word == Partial_word;
}

// Check if the game has ended (won or lost)
bool Hangman::GameEnd() const {
	return GameWon() || Trys == 0;
}

// Function to guess a letter in the word
bool Hangman::GuessLetterInWord(char letter) {
	bool found = false;
	for (size_t i = 0; i < Secret_word.length(); i++) {
		if (Secret_word[i] == letter && Partial_word[i] == '_') {
			Partial_word[i] = letter;
			found = true;
		}
	}
	return found;
}

// Generate a random word for the game
string Hangman::GenerateRandomWord() {
	// List of words for the game 
	vector<string> words = {
		"hangman", "programming", "computer", "language", "algorithm","knowledge"
	};

	// Seed the random number generator
	srand(static_cast<unsigned int>(time(nullptr)));

	// Choose a random word from the list
	int randomIndex = rand() % words.size();
	return words[randomIndex];
}

// Clear the console screen (platform-specific)
void Hangman::ClearScreen() {
	// Platform-specific code to clear the console screen
	// This code may need to be adapted for different operating systems
#ifdef _WIN32
	system("cls");
#else
	//  Linux, macOS
	system("clear");
#endif
}
