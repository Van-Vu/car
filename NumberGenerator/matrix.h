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
		float pHit, pMiss, pExact, pBlur;
		double predictedMean, predictedStdDev;
		std::vector<float> grid;
		std::vector<Data> probGrid;
		std::vector<int> randomDrawResult;
		std::vector<int> pick;
		std::vector<int> winners;
		std::vector<int> generateRandomResult();
		int getsensePosition(int);
		bool is_younger(const Data&, const Data&);

	public:
		Matrix(int, int, float, float);
		std::vector<float> getGrid();
		void draw(int &time);
		std::vector<float> normalize(std::vector<float> &messyGrid);
		void sense(std::vector<int> &realResult, float pExact, float pBlur);
		void senseAfterPick(float pExact, float pBlur);
		void move(std::vector<int> &randomResult);
		void comparePickValue(std::vector<int> &realResult);
		float * calculateDiscrepancy(std::vector<int> &realResult);
		void pickNumbers(float *gaussian);
		void print();
		void printProbGrid();
		void printPick();
		void sortProbGrid();
};