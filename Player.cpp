#include "Player.h"
#include "Hangman.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

// Define a static vector to store shared pointers to Player objects
std::vector<std::shared_ptr<Player>> Player::players;

// Constructor for Player class, initializes player's name and loads data from a file
Player::Player(const std::string& name) : playerName(name), gamesWon(0), gamesLost(0) {
	try {
		LoadDataFromFile(); // Attempt to load player data from a file
	}
	catch (const std::exception& e) {
		std::cerr << "Error loading data for player " << playerName << ": " << e.what() << std::endl;
	}
}

// Constructor for Player class with parameters for name, gamesWon, and gamesLost
Player::Player(const std::string& name, int won, int lost) : playerName(name), gamesWon(won), gamesLost(lost) {
	SaveDataToFile(); // Save player data to a file
}

// Assignment operator overload for Player class
Player& Player::operator=(const Player& other) {
	if (this != &other) {
		playerName = other.playerName;
		gamesWon = other.gamesWon;
		gamesLost = other.gamesLost;
	}
	return *this;
}

// A virtual function for Player class, just prints some information
void Player::VirtualFunction() const {
	std::cout << "This is a Player class representing the player: " << playerName << std::endl;
}

// Function to get the file path where player data is stored
std::string Player::GetFilePath() {
	return "Players_information.txt";
}

// Function to save player data to a file
void Player::SaveDataToFile() const {
	std::ofstream fileOut(GetFilePath(), std::ios::app); // Open the file in append mode
	if (fileOut.is_open()) {
		fileOut << playerName << " " << gamesWon << " " << gamesLost << std::endl; // Write player data to the file
		fileOut.close(); // Close the file
	}
	else {
		throw InvalidInputException("Error opening file (" + GetFilePath() + ") for writing!"); // Handle file open error
	}
}

// Function to load player data from a file
void Player::LoadDataFromFile() {
	std::ifstream file(GetFilePath()); // Open the file for reading
	if (file.is_open()) {
		players.clear(); // Clear the vector of players

		std::string tempPlayerName;
		int tempGamesWon, tempGamesLost;
		while (file >> tempPlayerName >> tempGamesWon >> tempGamesLost) {
			// Search for an existing player with the same name in the vector
			auto it = std::find_if(players.begin(), players.end(), [tempPlayerName](const std::shared_ptr<Player>& p) {
				return p->playerName == tempPlayerName;
				});

			if (it != players.end()) {
				// Update the existing player's data
				(*it)->gamesWon = tempGamesWon;
				(*it)->gamesLost = tempGamesLost;
			}
			else {
				// Create a new player and add it to the vector.
				players.emplace_back(std::make_shared<Player>(tempPlayerName, tempGamesWon, tempGamesLost));
			}
		}
		file.close(); // Close the file.
	}
	else {
		throw InvalidInputException("Error opening file (" + GetFilePath() + ") for reading!"); // Handle file open error
	}
}

// Function to save player-specific data to a separate file
void Player::SavePlayerDataToFile() const {
	std::ofstream fileOut(playerName + "_information.txt"); // Create a file with the player's name
	if (fileOut.is_open()) {
		fileOut << playerName << " " << gamesWon << " " << gamesLost << std::endl; // Write player data to the file
		fileOut.close(); // Close the file.
	}
	else {
		throw InvalidInputException("Error opening file (" + playerName + "_information.txt) for writing!"); // Handle file open error
	}
}

// Function to load player-specific data from a separate file
void Player::LoadPlayerDataFromFile() {
	std::ifstream file(playerName + "_information.txt"); // Open the player-specific file
	if (file.is_open()) {
		file >> playerName >> gamesWon >> gamesLost; // Read player data from the file
		file.close(); // Close the file
	}
	else {
		throw InvalidInputException("Error opening file (" + playerName + "_information.txt) for reading!"); // Handle file open error
	}
}

// Function to get the number of games won by the player
int Player::GetGamesWon() const {
	return gamesWon;
}

// Function to get the number of games lost by the player
int Player::GetGamesLost() const {
	return gamesLost;
}

// Function to increase the number of games won by the player and save the updated data
void Player::IncreaseGamesWon() {
	gamesWon++;
	SavePlayerDataToFile();
}

// Function to increase the number of games lost by the player and save the updated data
void Player::IncreaseGamesLost() {
	gamesLost++;
	SavePlayerDataToFile();
}

// Function to display player statistics
void Player::ShowPlayerStats() const {
	std::cout << "Player: " << playerName << "\nGames Won: " << gamesWon << "\nGames Lost: " << gamesLost << std::endl;
}

// Function to display statistics for all players
void Player::ShowAllPlayersStats() {
	for (const auto& player : players) {
		player->ShowPlayerStats();
		std::cout << "------------" << std::endl;
	}
}

// Function to find an existing player or add a new player if not found
Player* Player::FindOrAddPlayer(const std::string& name) {
	auto it = std::find_if(players.begin(), players.end(), [name](const std::shared_ptr<Player>& p) {
		return p->playerName == name;
		});

	if (it != players.end()) {
		return it->get(); // Return a pointer to the existing player
	}
	else {
		players.emplace_back(std::make_shared<Player>(name)); // Create a new player and add it to the vector
		return players.back().get(); // Return a pointer to the newly created player
	}
}

// Function to load data for all players from a file
void Player::LoadAllPlayersData() {
	std::ifstream file(GetFilePath()); // Open the file for reading
	if (file.is_open()) {
		players.clear(); // Clear the vector of players

		std::string tempPlayerName;
		int tempGamesWon, tempGamesLost;
		while (file >> tempPlayerName >> tempGamesWon >> tempGamesLost) {
			// Search for an existing player with the same name in the vector
			auto it = std::find_if(players.begin(), players.end(), [tempPlayerName](const std::shared_ptr<Player>& p) {
				return p->playerName == tempPlayerName;
				});

			if (it != players.end()) {
				// Update the existing player's data
				(*it)->gamesWon = tempGamesWon;
				(*it)->gamesLost = tempGamesLost;
			}
			else {
				// Create a new player and add it to the vector
				players.emplace_back(std::make_shared<Player>(tempPlayerName, tempGamesWon, tempGamesLost));
			}
		}
		file.close(); // Close the file
	}
	else {
		throw InvalidInputException("Error opening file (" + GetFilePath() + ") for reading!"); // Handle file open error
	}
}
