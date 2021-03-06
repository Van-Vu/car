// NumberGenerator.cpp : Defines the entry point for the console application.
//

#include "vector"
#include <ctime>
#include <iostream>
#include "matrix.h"
#include "filehelper.h"
#include "grouping.h"
#include "functionhelpers.h"



using namespace std;

int main()
{
	std::clock_t start;
	double duration;

	start = std::clock();

	vector < set<int> > filecontent = read_map("result.csv");
	static int gridSize = 37;
	static int drawSize = 8;
	static int drawIteration = 1000;
	static float pRealExact = 0;
	static float pRealBlur = 1. / 29;
	static float pHit = 0.6;
	static float pMiss = 0.4;

	static float pPickExact = 0.1;
	static float pPickBlur = 0.9 / 29;
	
	Matrix matrix(gridSize, drawSize, pHit, pMiss);

	int lines = filecontent.size();

	for (auto it: filecontent) {
		matrix.comparePickValue(it);
		float *diffGuassian = matrix.calculateDiff(it);
		float *worldGaussian = matrix.calculateResultGaussian(it);
		//std::cout << '\n' << diffGuassian[0] << ", " << diffGuassian[1] << " - " << worldGaussian[1] << ", " << worldGaussian[1] << " - ";
		matrix.sense(it, pRealExact, pRealBlur);
		//static std::vector<float> grid = matrix.getGrid();
		//float *worldGaussian = calculateGaussian(grid);
		float *predictecGaussian = updateGaussian(worldGaussian[0], worldGaussian[1], diffGuassian[0], diffGuassian[1]);
		matrix.retainGrid();
		matrix.pickNumbers(predictecGaussian);
		//matrix.senseAfterPick(pPickExact, pPickBlur);
		matrix.resetGrid();
		matrix.draw(drawIteration);
		
	}

	//move
	//compare pick with realresult
	//calculate mean & var of discrepancy
	//sense
	//calculate mean & var of whole world
	//predict mean & var
	//pick

	//even numbers:
	//2
	//28
	//101
	//238
	//303
	//192
	//68
	//15


	//matrix.sortProbGrid();
	//matrix.printProbGrid();
	//matrix.print();

	//Grouping grouping(gridSize);
	//grouping.applyGroup(filecontent);
	//grouping.countGroup();
	//grouping.print();

	//std::vector < std::vector <int> > pick = read_map("pick.csv");
	//findDuplicate(filecontent, pick);


	//duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	//std::cout << "duration milliseconds " << 1000 * duration << '\n';

	matrix.printPick();
	getchar();
    return 0;
}

