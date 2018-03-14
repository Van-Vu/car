#include <vector>

class Grouping {
	private:
		int elementInGroup;
		std::vector<int> countingGrid;
		std::vector< std::vector<int> > groupGrid;
		int getGroupNumber(int);

	public:
		Grouping(int);
		void applyGroup(std::vector< std::vector<int> >);
		void countGroup();
		void print();
};
