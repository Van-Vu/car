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