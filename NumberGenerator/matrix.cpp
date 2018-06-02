#include <iostream>
#include <vector>
// for random generator
#include <random>
// for accumulate
#include <numeric>
// for std::begin, end
#include <iterator>
// for for_each
#include <algorithm>

#include "matrix.h"
#include "functionhelpers.h"

Matrix::Matrix(int initialGridSize, int initDrawSize, float hit, float miss) {
	gridSize = initialGridSize;
	drawLineSize = initDrawSize;
	pHit = hit;
	pMiss = miss;
	predictedMean = 0.;
	predictedStdDev = 1.;
	stdProb = 1. / gridSize;
	grid.assign(gridSize, stdProb);
	beforeMoveGrid = grid;
	probGrid.assign(gridSize, Data());
}

std::vector<float> Matrix::getGrid() {
	return grid;
}

void Matrix::retainGrid() {
	beforeMoveGrid = grid;
}

void Matrix::resetGrid() {
	grid.assign(gridSize, stdProb);
}

std::set<int> Matrix::generateRandomResult() {
	static int new_value;
	// https://stackoverflow.com/a/20136256/1284688
	const int range_from = 1;
	const int range_to = gridSize;
	static std::random_device                  rand_dev;
	static std::mt19937                        generator(rand_dev());
	static std::uniform_int_distribution<int>  distr(range_from, range_to);

	while (randomDrawResult.size() < gridSize) {
		randomDrawResult.insert(distr(generator));
	}
	return randomDrawResult;
}

void Matrix::draw(int &times) {
	static std::set<int> randomResult;
	for (int i = 0; i < times; i++) {
		randomResult = generateRandomResult();
		move(randomResult);
	}
}

void Matrix::move(std::set<int> &randomResult) {
	bool isHit;

	for (int i = 0; i < grid.size(); i++) {
		if (randomResult.count(grid[i]) != 0) {
			isHit = true;
		}
		else {
			isHit = false;
		}

		grid[i] *= isHit * pHit + (1 - isHit) * pMiss;
	}

	grid = normalize(grid);
}

void Matrix::sense(std::set<int> &realResult, float pExact, float pBlur) {
	int blur = 0;

	//sortProbGrid();

	for (int i = 0; i < gridSize; i++) {
		if (realResult.count(i) != 0) {
			grid[i] += pBlur;
		}

		//grid[realResult[i] - 1] += pExact;
		//grid[getsensePosition(realResult[i] - 2)] += pBlur;
		//grid[getsensePosition(realResult[i])] += pBlur;
		//grid[probGrid[0].number - 1] += pBlur;
		//grid[probGrid[1].number - 1] += pBlur;
		//grid[probGrid[2].number - 1] += pBlur;
		//grid[probGrid[3].number - 1] += pBlur;
	}

	grid = normalize(grid);
}

void Matrix::senseAfterPick(float pExact, float pBlur) {
	sense(pick, pExact, pBlur);
}

//float * Matrix::calculateDiff(std::vector<int> &realResult) {
//	std::vector<float> diffGrid(drawLineSize, 0.);
//
//	for (int i = 0; i < realResult.size(); i++) {
//		diffGrid[i] = std::abs(stdProb - beforeMoveGrid[realResult[i] - 1]);
//	}
//	
//	// Bodom: need to normalize?
//	//discrepancyGrid = normalize(discrepancyGrid);
//	
//	return calculateGaussian(diffGrid);
//}

float * Matrix::calculateDiff(std::set<int>& realResult)
{
	return nullptr;
}

float * Matrix::calculateResultGaussian(std::set<int> &realResult) {
	std::vector<float> resultGrid(drawLineSize, 0.);

	for (auto it: realResult) {
		resultGrid[it] = grid[it - 1];
	}
	
	return calculateGaussian(resultGrid);
}

void Matrix::comparePickValue(std::set<int> &realResult) {
	if (pick.size() > 0) {
		winners.push_back(0);
		int number = 0;
		for (int i = 0; i < pick.size(); i++) {
			number = *std::next(pick.begin(), i);
			if (realResult.count(number) != 0) {
				winners.back() += 1;
			}
		}
		std::cout << winners.back();
	}
}

void Matrix::pickNumbers(float *gaussian) {
	pick.clear();
	probGrid.clear();

	Data data;
	for (int i = 0; i < gridSize; i++) {
		data.number = i + 1;
		data.probability = abs(gaussian[0] - grid[i]);
		//data.probability = grid[i];
		probGrid.push_back(data);
	}

	std::sort(probGrid.begin(), probGrid.end(), [](const Data a, const Data b) {return a.probability > b.probability; });
	//std::sort(probGrid.begin(), probGrid.end());
	
	int count = 0;
	while (pick.size() < gridSize) {
		pick.insert(probGrid[count].number);
		count += 1;
	}
}

void Matrix::sortProbGrid() {
	Data data;
	probGrid.clear();
	
	for (int i = 0; i < gridSize; i++) {
		data.number = i+1;
		data.probability = grid[i];
		probGrid.push_back(data);
	}

	std::sort(probGrid.begin(), probGrid.end());
}

bool Matrix::is_younger(const Data& x, const Data& y) { return x.probability < y.probability; }

int Matrix::getsensePosition(int position) {
	int blur = position;
	if (position < 0) {
		blur = gridSize - 1;
	}
	else if (position >= gridSize) blur = 0;

	return blur;
}

std::vector<float> Matrix::normalize(std::vector<float> &messyGrid) {
	float sum = std::accumulate(std::begin(messyGrid), std::end(messyGrid), 0.0);

	for (int i = 0; i < messyGrid.size(); i++) {
		messyGrid[i] /= sum;
	}

	return messyGrid;
}

void Matrix::print() {
	for (int i = 0; i < grid.size(); i++) {
		std::cout << grid[i] << "\n";
	}

	std::cout << std::endl;
}

void Matrix::printProbGrid() {
	for (int i = 0; i < probGrid.size(); i++) {
		std::cout << probGrid[i].number << " " << probGrid[i].probability << "\n";
	}
	std::cout << std::endl;
}

void Matrix::printPick() {
	for (auto it: pick) {
		std::cout << it << " " << "\n";
	}
	float total = std::accumulate(winners.begin(), winners.end(), 0.);
	std::cout << "winner:" << total / winners.size() << "\n";

	int count4 = 0;
	int count5 = 0;
	int count6 = 0;
	int count7 = 0;
	int count8 = 0;
	for (int i = 0; i < winners.size(); i++) {
		if (winners[i] > 7) count8 += 1;
		else if (winners[i] > 6) count7 += 1;
		else if (winners[i] > 5) count6 += 1;
		else if ((winners[i] > 4)) count5 += 1;
		else if ((winners[i] > 3)) count4 += 1;

		//std::cout << winners[i] << " " << "\n";
	}
	std::cout << "winner count:" << "\n";
	std::cout << count8 << "\n";
	std::cout << count7 << "\n";
	std::cout << count6 << "\n";
	std::cout << count5 << "\n";
	std::cout << count4 << "\n";

	std::cout << std::endl;
}