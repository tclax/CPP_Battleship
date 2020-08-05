#include <iostream>
#include <numeric>
#include <algorithm>
#include "BattleshipBoard.h"
#include <time.h>


//Computer Attack Strategy for randomly selecting an available coordinate.
void RandomAttackStrategy(int iterations)
{
	std::vector<int> movesVector;
	BattleshipBoard board(8, 8);
	board.CreateBoard();
	board.SetupShipPlacements();
	int simulationCount = iterations;
	
	int step = 1;
	int displayNext = step;
	int percent = 0;

	std::cout << "Processing " << iterations << " battleship matches..." << std::endl;

	for (int i = 0; i < simulationCount; i++)
	{
		int moves = 0;
		do
		{
			//board.PrintMaskedBoard();
			std::vector<std::tuple<int, int>> avaiableCoordinates = board.GetAllAvaiableCoordinates();
			int randomAttackIndex = std::rand() % avaiableCoordinates.size();
			int row = std::get<0>(avaiableCoordinates[randomAttackIndex]);
			int column = std::get<1>(avaiableCoordinates[randomAttackIndex]);
			board.AttackBoard(row, column);
			moves++;
		} while (!board.AreAllShipsSunk());

		//std::cout << "Board randomly completed in: " << moves << " moves.\n";
		movesVector.push_back(moves);
		board.ResetBoard();

		percent = (100 * (i + 1)) / iterations;
		if (percent >= displayNext)
		{
			std::cout << "\r" << "[" << std::string(percent / 5, (char)254u) << std::string(100 / 5 - percent / 5, ' ') << "]";
			std::cout << percent << "%" << " [Battleship Game " << i + 1 << " of " << iterations << "]";
			std::cout.flush();
			displayNext += step;
		}
	}

	std::cout << "\n";

	auto n = movesVector.size();
	float average = 0.0f;
	if (n != 0) {
		average = std::accumulate(movesVector.begin(), movesVector.end(), 0.0) / n;
	}

	std::cout << simulationCount << " simulations were completed." << std::endl;
	std::cout << "Max moves: " << *max_element(movesVector.begin(), movesVector.end()) << std::endl;
	std::cout << "Min moves: " << *min_element(movesVector.begin(), movesVector.end()) << std::endl;
	std::cout << "Average moves: " << average << std::endl;
}

//Computer Attack Strategy for randomly selecting a starting coordindate and then moving left to right across each row until all ships are sunk
void HorizontalLinearAttackStrategy(int iterations)
{
	std::vector<int> movesVector;
	BattleshipBoard board(8, 8);
	board.CreateBoard();
	board.SetupShipPlacements();
	int simulationCount = iterations;

	int step = 1;
	int displayNext = step;
	int percent = 0;

	std::cout << "Processing " << iterations << " battleship matches..." << std::endl;

	for (int i = 0; i < simulationCount; i++)
	{
		int moves = 0;
		auto horizontalCoordinates = board.GetHorizontalAttackIndices();

		//loop through all the coordinates until all the ships are sunk
		for (int index : horizontalCoordinates)
		{
			if (board.AreAllShipsSunk())
			{
				break;
			}
			board.AttackBoard(index);
			moves++;
		}

		//std::cout << "Board randomly completed in: " << moves << " moves.\n";
		movesVector.push_back(moves);
		board.ResetBoard();

		percent = (100 * (i + 1)) / iterations;
		if (percent >= displayNext)
		{
			std::cout << "\r" << "[" << std::string(percent / 5, (char)254u) << std::string(100 / 5 - percent / 5, ' ') << "]";
			std::cout << percent << "%" << " [Battleship Game " << i + 1 << " of " << iterations << "]";
			std::cout.flush();
			displayNext += step;
		}
	}

	std::cout << "\n";

	auto n = movesVector.size();
	float average = 0.0f;
	if (n != 0) {
		average = std::accumulate(movesVector.begin(), movesVector.end(), 0.0) / n;
	}

	std::cout << simulationCount << " simulations were completed." << std::endl;
	std::cout << "Max moves: " << *max_element(movesVector.begin(), movesVector.end()) << std::endl;
	std::cout << "Min moves: " << *min_element(movesVector.begin(), movesVector.end()) << std::endl;
	std::cout << "Average moves: " << average << std::endl;
}

//Computer Attack Strategy for randomly selecting a starting coordindate and then moving top to bottom across each column until all ships are sunk
void VerticalLinearAttackStrategy(int iterations)
{
	std::vector<int> movesVector;
	BattleshipBoard board(8, 8);
	board.CreateBoard();
	board.SetupShipPlacements();
	int simulationCount = iterations;

	int step = 1;
	int displayNext = step;
	int percent = 0;

	std::cout << "Processing " << iterations << " battleship matches..." << std::endl;

	for (int i = 0; i < simulationCount; i++)
	{
		int moves = 0;
		auto verticalCoordinates = board.GetVerticalAttackIndicies();

		//loop through all the coordinates until all the ships are sunk
		for (int index : verticalCoordinates)
		{
			if (board.AreAllShipsSunk())
			{
				break;
			}
			board.AttackBoard(index);
			moves++;
		}

		//std::cout << "Board randomly completed in: " << moves << " moves.\n";
		movesVector.push_back(moves);
		board.ResetBoard();

		percent = (100 * (i + 1)) / iterations;
		if (percent >= displayNext)
		{
			std::cout << "\r" << "[" << std::string(percent / 5, (char)254u) << std::string(100 / 5 - percent / 5, ' ') << "]";
			std::cout << percent << "%" << " [Battleship Game " << i + 1 << " of " << iterations << "]";
			std::cout.flush();
			displayNext += step;
		}
	}

	std::cout << "\n";

	auto n = movesVector.size();
	float average = 0.0f;
	if (n != 0) {
		average = std::accumulate(movesVector.begin(), movesVector.end(), 0.0) / n;
	}

	std::cout << simulationCount << " simulations were completed." << std::endl;
	std::cout << "Max moves: " << *max_element(movesVector.begin(), movesVector.end()) << std::endl;
	std::cout << "Min moves: " << *min_element(movesVector.begin(), movesVector.end()) << std::endl;
	std::cout << "Average moves: " << average << std::endl;
}

//Computer Attack Strategy for moving diagonally 
void DiagonalLinearAttackStrategy(int iterations)
{
	std::vector<int> movesVector;
	BattleshipBoard board(8, 8);
	board.CreateBoard();
	board.SetupShipPlacements();
	int simulationCount = iterations;

	int step = 1;
	int displayNext = step;
	int percent = 0;

	std::cout << "Processing " << iterations << " battleship matches..." << std::endl;

	for (int i = 0; i < simulationCount; i++)
	{
		int moves = 0;
		auto diagonalCoordinates = board.GetDiagonalAttackIndicies();

		//loop through all the coordinates until all the ships are sunk
		for (int index : diagonalCoordinates)
		{
			if (board.AreAllShipsSunk())
			{
				break;
			}
			board.AttackBoard(index);
			moves++;
		}

		//std::cout << "Board randomly completed in: " << moves << " moves.\n";
		movesVector.push_back(moves);
		board.ResetBoard();

		percent = (100 * (i + 1)) / iterations;
		if (percent >= displayNext)
		{
			std::cout << "\r" << "[" << std::string(percent / 5, (char)254u) << std::string(100 / 5 - percent / 5, ' ') << "]";
			std::cout << percent << "%" << " [Battleship Game " << i + 1 << " of " << iterations << "]";
			std::cout.flush();
			displayNext += step;
		}
	}

	std::cout << "\n";

	auto n = movesVector.size();
	float average = 0.0f;
	if (n != 0) {
		average = std::accumulate(movesVector.begin(), movesVector.end(), 0.0) / n;
	}

	std::cout << simulationCount << " simulations were completed." << std::endl;
	std::cout << "Max moves: " << *max_element(movesVector.begin(), movesVector.end()) << std::endl;
	std::cout << "Min moves: " << *min_element(movesVector.begin(), movesVector.end()) << std::endl;
	std::cout << "Average moves: " << average << std::endl;
}

//Computer Attack Strategy for search and destroy. Attacks a corrdinate in all directions until a miss is registered.
void SearchAndDestoryAttackStrategy(int iterations)
{
	std::vector<int> movesVector;
	BattleshipBoard board(8, 8);
	board.CreateBoard();
	board.SetupShipPlacements();
	int simulationCount = iterations;

	int step = 1;
	int displayNext = step;
	int percent = 0;

	std::cout << "Processing " << iterations << " battleship matches..." << std::endl;

	for (int i = 0; i < simulationCount; i++)
	{
		int moves = board.RunBoardSimulationSearchAndDestory();

		//std::cout << "Board randomly completed in: " << moves << " moves.\n";
		movesVector.push_back(moves);
		board.ResetBoard();

		percent = (100 * (i + 1)) / iterations;
		if (percent >= displayNext)
		{
			std::cout << "\r" << "[" << std::string(percent / 5, (char)254u) << std::string(100 / 5 - percent / 5, ' ') << "]";
			std::cout << percent << "%" << " [Battleship Game " << i + 1 << " of " << iterations << "]";
			std::cout.flush();
			displayNext += step;
		}
	}

	std::cout << "\n";

	auto n = movesVector.size();
	float average = 0.0f;
	if (n != 0) {
		average = std::accumulate(movesVector.begin(), movesVector.end(), 0.0) / n;
	}

	std::cout << simulationCount << " simulations were completed." << std::endl;
	std::cout << "Max moves: " << *max_element(movesVector.begin(), movesVector.end()) << std::endl;
	std::cout << "Min moves: " << *min_element(movesVector.begin(), movesVector.end()) << std::endl;
	std::cout << "Average moves: " << average << std::endl;
}

//Computes iterations number of games of battleship using a single strategy
void BattleshipComputerSimulation(int iterations, int simulationCode)
{
	//Randomizes 
	srand(time(NULL));

	//Runs the desired attack strategy iteration number of times
	switch (simulationCode)
	{
	case 1:
		//Simuates Battleship using the Random Attack Strategy.
		RandomAttackStrategy(iterations);
		break;
	case 2:
		//Simuates Battleship using the Horizontal Linear Attack Strategy.
		HorizontalLinearAttackStrategy(iterations);
		break;
	case 3:
		//Simuates Battleship using the Vertical Linear Attack Strategy.
		VerticalLinearAttackStrategy(iterations);
		break;
	case 4:
		//Simuates Battleship using the Diagonal Linear Attack Strategy.
		DiagonalLinearAttackStrategy(iterations);
		break;
	case 5:
		//Simuates Battleship using the Search and Destroy Attack Strategy.
		SearchAndDestoryAttackStrategy(iterations);
		break;
	case 6:
		std::cout << "Random Attack Strategy" << std::endl;
		RandomAttackStrategy(iterations);
		std::cout << "Horizontal Linear Attack Strategy" << std::endl;
		HorizontalLinearAttackStrategy(iterations);
		std::cout << "Vertical Linear Attack Strategy" << std::endl;
		VerticalLinearAttackStrategy(iterations);
		std::cout << "Diagonal Linear Attack Strategy" << std::endl;
		DiagonalLinearAttackStrategy(iterations);
		std::cout << "Search And Destory Attack Strategy" << std::endl;
		SearchAndDestoryAttackStrategy(iterations);
		break;
	}
}

int main()
{
	std::cout << "Welcome to the Battleship Simulator!" << std::endl;
	std::cout << "Select Attack Strategy" << std::endl;
	std::cout << "1. Random Coordindate" << std::endl;
	std::cout << "2. Linear Horizontal" << std::endl;
	std::cout << "3. Linear Vertical" << std::endl;
	std::cout << "4. Linear Diagonal" << std::endl;
	std::cout << "5. Search and Destroy Mode" << std::endl;
	std::cout << "6. Run Attack Stratgey Analysis" << std::endl;
	int attackStrategy;
	std::cin >> attackStrategy;
	std::cout << "Enter number of simulations to run: ";
	int iterations;
	std::cin >> iterations;

	//start the simulation
	BattleshipComputerSimulation(iterations, attackStrategy);

	return 0;
}