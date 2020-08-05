#ifndef BATTLESHIPBOARD_H
#define BATTLESHIPBOARD_H

#include <iostream>
#include <tuple>
#include <vector>
#include "BattleshipConstants.h"

class BattleshipBoard
{
protected:
	int width;
	int height;
	std::string log;

	char* board;
	 
public:
	BattleshipBoard();
	BattleshipBoard(int pWidth, int pHeight);
	~BattleshipBoard();
	int GetHeight();
	int GetWidth();
	void CreateBoard();
	void PrintBoard();
	void PlaceShip(int shipSize);
	void SetupShipPlacements();
	int CalculateIndex(int row, int column);
	std::tuple<int, int> CalculateCoordinateFromIndex(int index);
	bool IsValidIndex(int row, int column);
	bool IsValidIndex(int index);
	bool IsNorthValid(int index);
	bool IsSouthValid(int index);
	bool IsWestValid(int index);
	bool IsEastValid(int index);
	void ResetBoard();
	void PrintMaskedBoard();
	void AttackBoard(int index);
	void AttackBoard(int row, int column);
	bool AreAllShipsSunk();
	bool IsAttackValid(int row, int column);
	bool IsAttackValid(int index);
	std::vector<std::tuple<int, int>> GetAllAvaiableCoordinates();
	std::vector<int> GetHorizontalAttackIndices();
	std::vector<int> GetVerticalAttackIndicies();
	std::vector<int> GetDiagonalAttackIndicies();
	int RunBoardSimulationSearchAndDestory();
};

#endif

