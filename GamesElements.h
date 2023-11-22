#ifndef GAMEELEMENTS_H
#define GAMEELEMENTS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// GameElements is a base class designed to be inherited by other game-related classes
class GameElements {
private:
	static int TotalInstances;  // Static variable to keep track of total instances of this class and its derivatives

protected:
	// Protected static method to load the total number of instances from a file
	static void LoadTotalInstancesFromFile();

	// Protected static method to save the total number of instances to a file
	static void SaveTotalInstancesToFile();

public:
	// Constructor - increases the total instance count
	GameElements();

	// Virtual destructor - decreases the total instance count, ensuring proper cleanup in derived classes
	virtual ~GameElements();

	// Pure virtual function - to be implemented in derived classes for polymorphic behavior
	virtual void VirtualFunction() const = 0;

	// Static method to get the total number of instances of GameElements
	static int GetTotalInstances();
};

#endif // GAMEELEMENTS_H
