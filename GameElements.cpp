#include "GamesElements.h"
#include <fstream>

using namespace std;

// Static variable to keep track of the total number of GameElements instances
int GameElements::TotalInstances = 0;

// Static method to load the total number of instances from a file
void GameElements::LoadTotalInstancesFromFile() {
	ifstream file("Total_instances.txt");
	if (file.is_open()) {
		file >> TotalInstances;  // Read the total number of instances
		file.close();
	}
}

// Static method to save the total number of instances to a file
void GameElements::SaveTotalInstancesToFile() {
	ofstream file("Total_instances.txt");
	if (file.is_open()) {
		file << TotalInstances;  // Write the total number of instances
		file.close();
	}
}

// Constructor - increments the total number of instances and saves this info to a file
GameElements::GameElements() {
	TotalInstances++;
	SaveTotalInstancesToFile();
}

// Static method to get the total number of instances of GameElements
int GameElements::GetTotalInstances() {
	LoadTotalInstancesFromFile();
	return TotalInstances;
}

// Destructor - decrements the total number of instances and saves this info to a file
GameElements::~GameElements() {
	TotalInstances--;
	SaveTotalInstancesToFile();
}
