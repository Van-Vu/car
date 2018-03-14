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

Matrix::Matrix(int initialGridSize, int initDrawSize, float hit, float miss) {
	gridSize = initialGridSize;
	drawLineSize = initDrawSize;
	pHit = hit;
	pMiss = miss;
	predictedMean = 0.;
	predictedStdDev = 1.;
	grid.assign(gridSize, 1. / gridSize);
	randomDrawResult.assign(drawLineSize, 0);
	pick.reserve(8);

	probGrid.assign(gridSize, Data());
}

std::vector<float> Matrix::getGrid() {
	return grid;
}

std::vector<int> Matrix::generateRandomResult() {
	static int new_value;
	// https://stackoverflow.com/a/20136256/1284688
	const int range_from = 1;
	const int range_to = gridSize;
	static std::random_device                  rand_dev;
	static std::mt19937                        generator(rand_dev());
	static std::uniform_int_distribution<int>  distr(range_from, range_to);

	for (int i = 0; i < randomDrawResult.size(); ++i) {
		new_value = distr(generator);

		// not duplicate
		while (std::find(randomDrawResult.begin(), randomDrawResult.end(), new_value) != randomDrawResult.end()) {
			new_value = distr(generator);
		}

		randomDrawResult[i] = new_value;
	}

	return randomDrawResult;
}

void Matrix::draw(int &times) {
	static std::vector<int> randomResult;
	for (int i = 0; i < times; i++) {
		randomResult = generateRandomResult();
		move(randomResult);
	}
}

void Matrix::move(std::vector<int> &randomResult) {
	bool isHit;

	for (int i = 0; i < grid.size(); i++) {
		if (std::find(randomResult.begin(), randomResult.end(), i + 1) != randomResult.end()) {
			isHit = true;
		}
		else {
			isHit = false;
		}

		grid[i] *= isHit * pHit + (1 - isHit) * pMiss;
	}

	grid = normalize(grid);
}

void Matrix::sense(std::vector<int> &realResult, float pExact, float pBlur) {
	int blur = 0;

	sortProbGrid();

	for (int i = 0; i < realResult.size(); i++) {
		grid[realResult[i] - 1] += pExact;
		//grid[getsensePosition(realResult[i] - 2)] += pBlur;
		//grid[getsensePosition(realResult[i])] += pBlur;
		grid[probGrid[0].number - 1] += pBlur;
		grid[probGrid[1].number - 1] += pBlur;
		grid[probGrid[2].number - 1] += pBlur;
		grid[probGrid[3].number - 1] += pBlur;
	}

	grid = normalize(grid);
}

void Matrix::senseAfterPick(float pExact, float pBlur) {
	sense(pick, pExact, pBlur);
}

float * Matrix::calculateDiscrepancy(std::vector<int> &realResult) {
	int blur = 0;
	std::vector<float> discrepancyGrid(drawLineSize, 0.);

	for (int i = 0; i < realResult.size(); i++) {
		discrepancyGrid[i] = 1. - grid[realResult[i] - 1];
	}
	
	// Bodom: need to normalize?
	//discrepancyGrid = normalize(discrepancyGrid);


	// Bodom: use functionhelper
	static float gaussian[2];

	float sum = std::accumulate(discrepancyGrid.begin(), discrepancyGrid.end(), 0.0);
	float mean = sum / discrepancyGrid.size();

	float accum = 0.0;
	std::for_each(std::begin(discrepancyGrid), std::end(discrepancyGrid), [&](const float d) {
		accum += (d - mean) * (d - mean);
	});

	gaussian[0] = mean;
	gaussian[1] = accum / discrepancyGrid.size();
	
	return gaussian;
}

void Matrix::comparePickValue(std::vector<int> &realResult) {
	if (pick.size() > 0) {
		winners.push_back(0);
		for (int i = 0; i < pick.size(); i++) {
			if (std::find(realResult.begin(), realResult.end(), pick[i]) != realResult.end()) {
				winners.back() += 1;
			}
		}
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
	
	for (int i = 0; i < drawLineSize; i++) {
		pick.push_back(probGrid[i].number);
	}

	//static int new_up = gridSize - 1;
	//static int new_low = gridSize - drawLineSize - 1;
	//for (int i = new_up; i > new_low; i--) {
	//	pick.push_back(probGrid[i].number);
	//}
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
	for (int i = 0; i < pick.size(); i++) {
		std::cout << pick[i]<< " " << "\n";
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