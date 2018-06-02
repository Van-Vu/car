#include <set>
#include <vector>

struct Data
{
	int number;
	double probability;
	bool operator < (const Data& rhs) const {
		return probability < rhs.probability;
	}

	bool operator > (const Data& rhs) const {
		return probability > rhs.probability;
	}
};

class Matrix {
	private:
		int gridSize, drawLineSize;
		float stdProb, pHit, pMiss, pExact, pBlur;
		double predictedMean, predictedStdDev;
		std::vector<float> grid, beforeMoveGrid;
		std::vector<Data> probGrid;
		std::set<int> randomDrawResult, pick;

		std::set<int> generateRandomResult();
		int getsensePosition(int);
		bool is_younger(const Data&, const Data&);

	public:
		Matrix(int, int, float, float);
		std::vector<int> winners;
		std::vector<float> getGrid();
		void draw(int &time);
		std::vector<float> normalize(std::vector<float> &messyGrid);
		void sense(std::set<int> &realResult, float pExact, float pBlur);
		void senseAfterPick(float pExact, float pBlur);
		void move(std::set<int> &randomResult);
		void comparePickValue(std::set<int> &realResult);
		void retainGrid();
		void resetGrid();
		float * calculateDiff(std::set<int> &realResult);
		float * calculateResultGaussian(std::set<int> &realResult);

		void pickNumbers(float *gaussian);
		void print();
		void printProbGrid();
		void printPick();
		void sortProbGrid();
};