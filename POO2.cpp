// Include necessary header files
#include "Hangman.h"
#include "Player.h"
#include <iostream>
#include <algorithm>
#include <limits>

int main() {
	// Start of the game, greeting message
	std::cout << "Welcome to the Hangman game!" << std::endl;

	// Load existing player data from file
	try {
		Player::LoadAllPlayersData();
	}
	catch (const std::exception& e) {
		// Handle any exceptions thrown during data loading, e.g., InvalidInputException
		std::cerr << "Error loading player data: " << e.what() << std::endl;
	}

	int choice;
	do {
		// Main menu for the game
		std::cout << "\nMain Menu:\n1. Start the game\n2. See all game players' won and lost games\n3. Exit\nEnter your choice: ";
		std::cin >> choice;

		switch (choice) {
		case 1: {
			// Start a new game
			Hangman::ClearScreen();
			std::string playerName;
			std::cout << "Enter your name: ";
			std::cin >> playerName;

			try {
				// Find or add a new player
				Player* playerPtr = Player::FindOrAddPlayer(playerName);

				// Generate a random word and set the number of tries
				std::string secretWord = Hangman::GenerateRandomWord(); // Call GenerateRandomWord using the class name
				int tries = 6;

				// Initialize a new Hangman game
				Hangman hangman(secretWord, tries); // Create an instance of the Hangman class with a secret word and tries

				// Game loop
				while (!hangman.GameEnd()) {
					hangman.ShowGameStatus();

					char letter;
					std::cout << "Insert a letter: ";
					std::cin >> letter;

					// Player guesses a letter
					hangman.GuessLetter(tolower(letter));
					Hangman::ClearScreen(); // Call ClearScreen using the class name
				}

				// Check if the game is won or lost and update player stats
				if (hangman.GameWon()) {
					std::cout << "Congratulations, " << playerName << "! You won. The word is: " << secretWord << std::endl;
					playerPtr->IncreaseGamesWon();
				}
				else {
					std::cout << "Sorry, " << playerName << ". You lost. The correct word is: " << secretWord << std::endl;
					playerPtr->IncreaseGamesLost();
				}

				// Save player data to file
				playerPtr->SavePlayerDataToFile();
			}
			catch (const std::exception& e) {
				// Handle any exceptions thrown during gameplay
				std::cerr << "Error during the game: " << e.what() << std::endl;
			}
			break;
		}
		case 2:
			// Display all players' statistics
			Hangman::ClearScreen();
			Player::ShowAllPlayersStats();
			break;
		case 3:
			// Exiting the game
			Hangman::ClearScreen();
			std::cout << "Exiting the program. Goodbye!" << std::endl;
			{
				std::ofstream file(Player::GetPublicFilePath(), std::ios::trunc);
				if (file.is_open()) {
					file.close();
					std::cout << "Data file cleared successfully.\n";
				}
				else {
					std::cerr << "Error: Unable to clear the data file.\n";
				}
			}
			break;
		default:
			// Handling invalid menu choice
			std::cerr << "Invalid choice. Please enter a valid option." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	} while (choice != 3);

	return 0;
}
