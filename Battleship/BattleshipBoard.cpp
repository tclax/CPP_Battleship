#include <iostream>
#include <tuple>
#include <vector>
#include "BattleshipBoard.h"
#include "BattleshipConstants.h"

BattleshipBoard::BattleshipBoard()
{
}

BattleshipBoard::BattleshipBoard(int pWidth, int pHeight)
{
	width = pWidth;
	height = pHeight;
}


BattleshipBoard::~BattleshipBoard()
{
}

int BattleshipBoard::GetHeight()
{
	return height;
}

int BattleshipBoard::GetWidth()
{
	return width;
}


//column + row * height
int BattleshipBoard::CalculateIndex(int row, int column)
{
	return column + row * height;
}

std::tuple<int, int> BattleshipBoard::CalculateCoordinateFromIndex(int index)
{
	int row = index / height;
	int column = index / row;
    return std::tuple<int, int>(row, column);
}


//Creates a new board set to all empty tiles.
void BattleshipBoard::CreateBoard()
{
	board = new char[width * height];

	for (int row = 0; row < width; row++)
	{
		for (int column = 0; column < height; column++)
		{
			board[CalculateIndex(row, column)] = BattleshipConstants::EmptyTile;
		}
	}
}


//Prints the board as is showing all ships, empty, hit, and miss tiles.
void BattleshipBoard::PrintBoard()
{
	std::cout << "Printing Board \n  " << std::flush;
	for (int column = 0; column < height; column++)
	{
		std::cout << column << " ";
	}
	std::cout << "\n";

	for (int row = 0; row < width; row++)
	{
		std::cout << row << " ";
		for (int column = 0; column < height; column++)
		{
			std::cout << board[CalculateIndex(row, column)] << " ";
		}
		std::cout << "\n";
	}

}


//Places all the ships on the board.
//TODO: Pass in the shipSizeArray to all for custom sizes/
void BattleshipBoard::SetupShipPlacements() 
{
	int shipSizeArray[5] = { 5, 4, 3, 3, 2 };
	for (int shipSize : shipSizeArray)
	{
		PlaceShip(shipSize);
	}
}


//Generates a random location to place a ship. Ships can be places north, south, east, or west. Ships cannot overlap. Generates a list of all valid coordindates and then randomly selects one of the coordinates and places the ships.
void BattleshipBoard::PlaceShip(int shipSize)
{
	char shipCode = BattleshipConstants::ShipTile;
	//Generate a list of all valid coordinate pairs start(x,y)  end(x,y)
	//Iterate each coordinate on the board and check in all 4 cardinal directions (north, south, east, west)
	//store coordinates as tuples
	std::vector<std::tuple<int, int>> northCoordinateVector;
	std::vector<std::tuple<int, int>> southCoordinateVector;
	std::vector<std::tuple<int, int>> westCoordinateVector;
	std::vector<std::tuple<int, int>> eastCoordinateVector;

	//loop through each coordinate and check in each direction if there is enough space and if all board values are empty to place the ship
	for (int row = 0; row < width; row++)
	{
		for (int column = 0; column < height; column++)
		{
			//skip position evaluation if its not empty.
			if (board[CalculateIndex(row, column)] == BattleshipConstants::EmptyTile) 
			{
				std::tuple<int, int> startCoordinate{ row, column };

				//check north
				bool isNorthValid = true;
				for (int index = 1; index < shipSize; index++)
				{
					if (!isNorthValid)
					{
						break;
					}
					int checkIndex = CalculateIndex(row - index, column);
					isNorthValid = checkIndex >= 0 && checkIndex < (width * height) && board[CalculateIndex(row - index, column)] == BattleshipConstants::EmptyTile;
				}
				//add north coordinate if valid
				if (isNorthValid)
				{
					northCoordinateVector.push_back(std::tuple<int, int>{std::tuple<int, int>{row, column}});
				}

				//check south
				bool isSouthValid = true;
				for (int index = 1; index < shipSize; index++)
				{
					if (!isSouthValid)
					{
						break;
					}
					int checkIndex = CalculateIndex(row + index, column);
					isSouthValid = checkIndex >= 0 && checkIndex < (width * height) && board[CalculateIndex(row + index, column)] == BattleshipConstants::EmptyTile;
				}
				//add south coordinate if valid
				if (isSouthValid)
				{
					southCoordinateVector.push_back(std::tuple<int, int>{std::tuple<int, int>{row, column}});
				}
				
				//check west
				bool isWestValid = true;
				for (int index = 1; index < shipSize; index++)
				{
					if (!isWestValid)
					{
						break;
					}
					int checkIndex = CalculateIndex(row, column - index);
					isWestValid = checkIndex >= 0 && checkIndex < (width * height) && checkIndex >= 0 + row * height && checkIndex <= width + row * height && board[CalculateIndex(row, column - index)] == BattleshipConstants::EmptyTile;
				}
				//add west coordinate if valid
				if (isWestValid)
				{
					westCoordinateVector.push_back(std::tuple<int, int>{std::tuple<int, int>{row, column}});
				}

				//check east
				bool isEastValid = true;
				for (int index = 1; index < shipSize; index++)
				{
					if (!isEastValid)
					{
						break;
					}
					int checkIndex = CalculateIndex(row, column + index);
					isEastValid = checkIndex >= 0 && checkIndex < (width * height) && checkIndex >= 0 + row * height && checkIndex <= width + row * height && board[CalculateIndex(row, column + index)] == BattleshipConstants::EmptyTile;
				}
				//add west coordinate if valid
				if (isEastValid)
				{
					eastCoordinateVector.push_back(std::tuple<int, int>{std::tuple<int, int>{row, column}});
				}
			}

		}
	}

	std::vector<char> directionVector;
	if (northCoordinateVector.size() > 0)
		directionVector.push_back('n');
	if (southCoordinateVector.size() > 0)
		directionVector.push_back('s');
	if (westCoordinateVector.size() > 0)
		directionVector.push_back('w');
	if (eastCoordinateVector.size() > 0)
		directionVector.push_back('e');


	char directionSelection = directionVector[std::rand() % directionVector.size()];

	switch (directionSelection)
	{
		int startRow;
		int startColumn;
		int position;
		case 'n':
			position = std::rand() % northCoordinateVector.size();

			startRow = std::get<0>(northCoordinateVector[position]);
			startColumn = std::get<1>(northCoordinateVector[position]);
			for (int shipIndex = 0; shipIndex < shipSize; shipIndex++)
			{
				board[CalculateIndex(startRow - shipIndex, startColumn)] = shipCode;
			}

			break;
		case 's':
			position = std::rand() % southCoordinateVector.size();

			startRow = std::get<0>(southCoordinateVector[position]);
			startColumn = std::get<1>(southCoordinateVector[position]);
			for (int shipIndex = 0; shipIndex < shipSize; shipIndex++)
			{
				board[CalculateIndex(startRow + shipIndex, startColumn)] = shipCode;
			}
			break;
		case 'w':
			position = std::rand() % westCoordinateVector.size();

			startRow = std::get<0>(westCoordinateVector[position]);
			startColumn = std::get<1>(westCoordinateVector[position]);
			for (int shipIndex = 0; shipIndex < shipSize; shipIndex++)
			{
				board[CalculateIndex(startRow, startColumn - shipIndex)] = shipCode;
			}
			break;
		case 'e':
			position = std::rand() % eastCoordinateVector.size();

			startRow = std::get<0>(eastCoordinateVector[position]);
			startColumn = std::get<1>(eastCoordinateVector[position]);
			for (int shipIndex = 0; shipIndex < shipSize; shipIndex++)
			{
				board[CalculateIndex(startRow, startColumn + shipIndex)] = shipCode;
			}
			break;
	}
}

//Returns true if the the coordinates passed in exist on the board.
bool BattleshipBoard::IsValidIndex(int row, int column)
{
	int index = CalculateIndex(row, column);
	return (index >= 0 && index < (width * height));
}

bool BattleshipBoard::IsValidIndex(int index)
{
	return (index >= 0 && index < (width * height));
}

bool BattleshipBoard::IsNorthValid(int index)
{
	return (index >= 0 && index < (width * height) && index - height >= 0);
}

bool BattleshipBoard::IsSouthValid(int index)
{
	return (index >= 0 && index < (width * height) && index + height <= (width * height));
}

bool BattleshipBoard::IsWestValid(int index)
{
	return (index >= 0 && index < (width * height) && index % height != 0);
}

bool BattleshipBoard::IsEastValid(int index)
{
	return (index >= 0 && index < (width * height) && ((index + 1)) % height != 0);
}


//Removes the current board and sets up a new board.
void BattleshipBoard::ResetBoard()
{
	delete[] board;

	CreateBoard();

	SetupShipPlacements();
}


//Prints the board as an opposing player would see the board. Only prints emptys, hits, or misses.
void BattleshipBoard::PrintMaskedBoard()
{
	std::cout << "  ";
	for (int column = 0; column < height; column++)
	{
		std::cout << column << " ";
	}
	std::cout << "\n";

	for (int row = 0; row < width; row++)
	{
		std::cout << row << " ";
		for (int column = 0; column < height; column++)
		{
			int index = CalculateIndex(row, column);
			if (board[index] == BattleshipConstants::ShipTile)
			{
				std::cout << BattleshipConstants::EmptyTile << " ";
			}
			else
			{
				std::cout << board[index] << " ";
			}
			
		}
		std::cout << "\n";
	}
}

//Submits an attack on the board. Changes the tile at the coordinate passed in to either a hit or a miss depending if the tile is a ship or empty.
void BattleshipBoard::AttackBoard(int row, int column)
{
	int index = CalculateIndex(row, column);

	if (board[index] == BattleshipConstants::ShipTile)
	{
		//std::cout << "HIT!\n";
		board[index] = BattleshipConstants::HitTile;
	}
	else
	{
		//std::cout << "Miss!\n";
		board[index] = BattleshipConstants::MissTitle;
	}
}

//Submits an attack on the board. Changes the tile at the index passed in to either a hit or a miss depending if the tile is a ship or empty.
void BattleshipBoard::AttackBoard(int index)
{
	if (board[index] == BattleshipConstants::ShipTile)
	{
		//std::cout << "HIT!\n";
		board[index] = BattleshipConstants::HitTile;
	}
	else
	{
		//std::cout << "Miss!\n";
		board[index] = BattleshipConstants::MissTitle;
	}
}

//Returns true if no ship tiles exist on the board.
bool BattleshipBoard::AreAllShipsSunk()
{
	bool allSunk = true;
	for (int row = 0; row < width; row++)
	{
		if (!allSunk)
			break;
		for (int column = 0; column < height; column++)
		{	
			if (!allSunk)
				break;
			allSunk &= board[CalculateIndex(row, column)] != BattleshipConstants::ShipTile;
		}
	}

	return allSunk;
}

//Checks that coordinated passed in if the attack to be made is valid. A valid attack is on a tile that is empty or a ship.
bool BattleshipBoard::IsAttackValid(int row, int column)
{
	int index = CalculateIndex(row, column);
	return (index >= 0 && index < (width * height) && (board[index] == BattleshipConstants::EmptyTile || board[index] == BattleshipConstants::ShipTile));
}

//Checks the index passed in if the attack to be made is valid. A valid attack is on a tile that is empty or a ship.
bool BattleshipBoard::IsAttackValid(int index)
{
	return (index >= 0 && index < (width * height) && (board[index] == BattleshipConstants::EmptyTile || board[index] == BattleshipConstants::ShipTile));
}

//Returns a list of all tiles that are either empty or a ship tile
std::vector<std::tuple<int, int>> BattleshipBoard::GetAllAvaiableCoordinates()
{
	std::vector<std::tuple<int, int>> availableCoordinates;
	for (int row = 0; row < width; row++)
	{
		for (int column = 0; column < height; column++)
		{
			int index = CalculateIndex(row, column);
			if(board[index] == BattleshipConstants::EmptyTile || board[index] == BattleshipConstants::ShipTile)
				availableCoordinates.push_back(std::tuple<int, int>(row, column));
		}
	}

	return availableCoordinates;
}

//Starts with picking a random starting point. Then moves left to right down each row to get a list of all coordinates.
std::vector<int> BattleshipBoard::GetHorizontalAttackIndices()
{
	std::vector<int> horizontalIndexList;

	int startingRow = std::rand() % width;
	int startingColumn = std::rand() % height;
	int startingIndex = CalculateIndex(startingRow, startingColumn);

	//loop from startingIndex - end
	for (int index = startingIndex; index < width * height; index++)
	{
		horizontalIndexList.push_back(index);
	}

	//loop from start to startingIndex
	for (int index = 0; index < startingIndex; index++)
	{
		horizontalIndexList.push_back(index);
	}

	return horizontalIndexList;

}

//Starts with picking a random column starting point. Then moves down down each column to get a list of all coordinates.
std::vector<int> BattleshipBoard::GetVerticalAttackIndicies()
{
	std::vector<int> verticalIndexList;

	int startingRow = 0;
	int startingColumn = std::rand() % height;
	int startingIndex = CalculateIndex(startingRow, startingColumn);

	for (int column = startingColumn; column < width; column++)
	{
		for (int index = column; index < width * height; index += height)
		{
			verticalIndexList.push_back(index);
		}
	}

	for (int column = 0; column < startingColumn; column++)
	{
		for (int index = column; index < width * height; index += height)
		{
			verticalIndexList.push_back(index);
		}
	}

	return verticalIndexList;
}

//Randomly generates a starting point.
//Divide the board into two halves diagonally.
std::vector<int> BattleshipBoard::GetDiagonalAttackIndicies()
{
	std::vector<int> diagonalCoordinateList;
	
	int startingRow = 0;
	int startingColumn = 0;
	int startingIndex = CalculateIndex(startingRow, startingColumn);

	int topHalfDiagonalLineCount = ((width + height - 1) / 2) + 1;
	int bottomHalfDiagonalLineCount = width + height - 1 - topHalfDiagonalLineCount;

	//get indices for the top half of the board
	for (int index = 0; index < topHalfDiagonalLineCount; index++)
	{
		for (int diagonalIndex = 0; diagonalIndex < index + 1; diagonalIndex++)
		{			
			diagonalCoordinateList.push_back((index) + (diagonalIndex * (width - 1)));
		}
	}

	int multiplier = 2;
	//get the indices for the bottom half of the board
	for (int index = bottomHalfDiagonalLineCount; index > 0; index--)
	{
		for (int diagonalIndex = 0; diagonalIndex < index; diagonalIndex++)
		{
			diagonalCoordinateList.push_back(((multiplier * height) - 1) + (diagonalIndex * height - diagonalIndex));
		}
		multiplier++;
	}
	
	return diagonalCoordinateList;
}

//Smart computer attack strategy.
//Starts by choosing a random attack strategy.
//When a hit is detected, the stratgy enters 'search and destroy mode'
//When in SND (Search and Destroy) mode, the attack strategy checks north, south, east, and west for another ship to hit.
int BattleshipBoard::RunBoardSimulationSearchAndDestory()
{
	int moves = 0;
	try 
	{
		//move horizontally across the board until a hit is found
	//loop from start to startingIndex
		for (int index = 0; index < height * width; index++)
		{
			if (AreAllShipsSunk())
			{
				break;
			}

			if (IsAttackValid(index))
			{
				AttackBoard(index);

				//if the board just registed a hit, enter search and destroy mode. all all neighboring cardinal directions until a miss
				if (board[index] == BattleshipConstants::HitTile)
				{
					moves++;
					bool isNorthValid = false;
					bool isSouthValid = false;
					bool isWestValid = false;
					bool isEastValid = false;

					//Check Nouth
					if (IsNorthValid(index) && (board[index - height] == BattleshipConstants::EmptyTile || board[index - height] == BattleshipConstants::ShipTile))
					{
						isNorthValid = true;
					}

					//Check South
					if (IsSouthValid(index) && (board[index + height] == BattleshipConstants::EmptyTile || board[index + height] == BattleshipConstants::ShipTile))
					{
						isSouthValid = true;
					}

					//Check West
					if (IsWestValid(index) && (board[index - 1] == BattleshipConstants::EmptyTile || board[index - 1] == BattleshipConstants::ShipTile))
					{
						isWestValid = true;
					}

					//Check East
					if (IsEastValid(index) && (board[index + 1] == BattleshipConstants::EmptyTile || board[index + 1] == BattleshipConstants::ShipTile))
					{
						isEastValid = true;
					}

					//attack all north until a miss
					int workingIndex = index - height;
					while (isNorthValid && !AreAllShipsSunk())
					{
						AttackBoard(workingIndex);
						isNorthValid = IsNorthValid(workingIndex) && board[workingIndex] == BattleshipConstants::HitTile;
						moves++;
						workingIndex = workingIndex - height;
					}

					//attack all south until a miss
					workingIndex = index + height;
					while (isSouthValid && !AreAllShipsSunk())
					{
						AttackBoard(workingIndex);
						isSouthValid = IsSouthValid(workingIndex) && board[workingIndex] == BattleshipConstants::HitTile;
						moves++;
						workingIndex = workingIndex + height;
					}

					//attack all west until a miss
					workingIndex = index - 1;
					while (isWestValid && !AreAllShipsSunk())
					{
						AttackBoard(workingIndex);
						isWestValid = IsWestValid(workingIndex) && board[workingIndex] == BattleshipConstants::HitTile;
						moves++;
						workingIndex = workingIndex - 1;
					}

					//attack all east until a miss
					workingIndex = index + 1;
					while (isEastValid && !AreAllShipsSunk())
					{
						AttackBoard(workingIndex);
						isEastValid = IsEastValid(workingIndex) && board[workingIndex] == BattleshipConstants::HitTile;
						moves++;
						workingIndex = workingIndex + 1;
					}
				}
				else
				{
					moves++;
				}
			}
		}
		
	}
	catch (std::exception ex)
	{
		std::cout << ex.what() << std::endl;
	}
	
	

	return moves;
}


