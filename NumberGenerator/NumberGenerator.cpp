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

	vector < vector <int> > filecontent = read_map("result.csv");
	static int gridSize = 37;
	static int drawSize = 8;
	static int drawIteration = 100;
	static float pRealExact = 0;
	static float pRealBlur = 0.25;
	static float pHit = 0.6;
	static float pMiss = 0.4;

	static float pPickExact = 0.3;
	static float pPickBlur = 0.35;
	
	Matrix matrix(gridSize, drawSize, pHit, pMiss);

	int lines = filecontent.size();

	for (int i = 0; i < lines; i++) {
		matrix.draw(drawIteration);
		matrix.comparePickValue(filecontent[i]);
		float *discrepancyGuassian = matrix.calculateDiscrepancy(filecontent[i]);
		matrix.sense(filecontent[i], pRealExact, pRealBlur);
		static std::vector<float> grid = matrix.getGrid();
		float *worldGaussian = calculateGaussian(grid);
		static float predictecGaussian[2];
		predictecGaussian[0] = discrepancyGuassian[0] + worldGaussian[0];
		predictecGaussian[1] = discrepancyGuassian[1] + worldGaussian[1];
		
		matrix.pickNumbers(predictecGaussian);
		//matrix.senseAfterPick(pPickExact, pPickBlur);
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

	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	std::cout << "duration milliseconds " << 1000 * duration << '\n';

	matrix.printPick();
	getchar();
    return 0;
}

