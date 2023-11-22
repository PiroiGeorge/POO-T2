#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <memory>
#include "CustomException.h"
#include "GamesElements.h"

class Player : public GameElements {
private:
	std::string playerName; // Stores the name of the player
	int gamesWon; // Stores the number of games won by the player
	int gamesLost; // Stores the number of games lost by the player
	static std::vector<std::shared_ptr<Player>> players; // Static vector to keep track of all player instances

public:
	Player(const std::string& name); // Constructor with name parameter
	Player(const std::string& name, int won, int lost); // Constructor with name, games won, and games lost parameters
	Player& operator=(const Player& other); // Assignment operator overload for copying Player objects

	void VirtualFunction() const; // A virtual function without a specific implementation
	std::string GetName() const { return playerName; } // Getter function for player name
	int GetGamesWon() const; // Getter function for the number of games won
	int GetGamesLost() const; // Getter function for the number of games lost
	void IncreaseGamesWon(); // Function to increase the number of games won
	void IncreaseGamesLost(); // Function to increase the number of games lost
	void ShowPlayerStats() const; // Function to display player statistics
	static void ShowAllPlayersStats(); // Static function to show statistics for all players.
	static void LoadAllPlayersData(); // Static function to load data for all players
	static Player* FindOrAddPlayer(const std::string& name); // Static function to find or add a player by name

	// Static function providing access to a private function by returning its result
	static std::string GetPublicFilePath() {
		return GetFilePath();
	}

private:
	static std::string GetFilePath(); // Private function to get a file path
	void SaveDataToFile() const; // Private function to save player data to a file
	void LoadDataFromFile(); // Private function to load player data from a file
	void LoadPlayerDataFromFile(); // Private function to load player-specific data from a separate file

public:
	void SavePlayerDataToFile() const; // Public function to save player-specific data to a separate file
};

#endif // PLAYER_H
