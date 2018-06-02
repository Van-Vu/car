#include <iostream>
#include <numeric>
#include <iterator>
#include <algorithm>
#include "functionhelpers.h"

float * calculateGaussian(std::vector<float> &grid) {
	static float gaussian[2];

	float sum = std::accumulate(grid.begin(), grid.end(), 0.0);
	float mean = sum / grid.size();

	float accum = 0.0;
	std::for_each(std::begin(grid), std::end(grid), [&](const float d) {
		accum += (d - mean) * (d - mean);
	});

	gaussian[0] = mean;
	gaussian[1] = accum / grid.size();

	return gaussian;
}

float * updateGaussian(float mean1, float var1, float mean2, float var2) {
	float new_gaussian[2];
	new_gaussian[0] = float(var2 * mean1 + var1 * mean2) / (var1 + var2);
	new_gaussian[1] = 1. / (1. / var1 + 1. / var2);

	return new_gaussian;
}

float * predictGaussian(float mean1, float var1, float mean2, float var2) {
	float new_gaussian[2];
	new_gaussian[0] = mean1 + mean2;
	new_gaussian[1] = var1 + var2;

	return new_gaussian;
}

void calEvenNumbers(std::vector< std::vector<int> > &filecontent) {
	int even = 0;
	std::vector<int> evenGrid(8, 0);

	int lines = filecontent.size();
	for (int i = 0; i < lines; i++) {
		even = 0;
		std::vector<int> result = filecontent[i];
		for (int j = 0; j < 8; j++) {
			if (result[j] % 2 == 0) even += 1;
		}
		evenGrid[even] += 1;
	}

	for (int i = 0; i < 8; i++) {
		std::cout << evenGrid[i] << '\n';
	}
}

void findDuplicate(std::vector< std::vector<int> > &filecontent, std::vector< std::vector<int> > &pick) {
	static int count = 0;
	for (int i = 0; i < pick.size(); i++) {
		for (int j = 0; j < filecontent.size(); j++) {
			// not duplicate
			count = 0;
			for (int k = 0; k < pick[0].size(); k++) {
				if (std::find(filecontent[j].begin(), filecontent[j].end(), pick[i][k]) != filecontent[j].end()) {
					count += 1;
				}
			}
			//std::cout << i << ", " << j << ": " << count << '\n';
			if (count > 7) std::cout << j << "DUPLICATE" << '\n';
		}
	}
}