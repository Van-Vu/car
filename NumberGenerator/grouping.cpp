#include <iostream>
#include "grouping.h"


Grouping::Grouping(int gridSize) {
	elementInGroup = 5;
	countingGrid.assign((gridSize / elementInGroup) + 1, 0);
}

void Grouping::applyGroup(std::vector< std::vector<int> > drawResult) {
	std::vector<int> row;
	for (int i = 0; i < drawResult.size(); i++) {
		row.clear();
		for (int j = 0; j < drawResult[0].size(); j++) {
			row.push_back(getGroupNumber(drawResult[i][j]));
		}

		groupGrid.push_back(row);
	}
}

void Grouping::countGroup() {
	for (int i = 0; i < groupGrid.size(); i++) {
		for (int j = 0; j < groupGrid[0].size(); j++) {
			countingGrid[groupGrid[i][j] - 1] += 1;
		}
	}
}

int Grouping::getGroupNumber(int number) {
	if (number % elementInGroup > 0) {
		return (number / elementInGroup) + 1;
	}
	else {
		return (number / elementInGroup);
	}
	
}

void Grouping::print() {
	for (int i = 0; i < countingGrid.size(); i++) {
		std::cout << countingGrid[i] << "\n";
	}

	std::cout << std::endl;
}