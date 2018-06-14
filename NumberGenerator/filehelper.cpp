#include <vector>
#include <set>
#include <string>
#include <fstream> 


/**
Helper function for reading in map data

@param s - a string representing one line of map data.

@return - A row of chars, each of which represents the
color of a cell in a grid world.
*/
std::set <int> read_line(std::string s) {
	std::set <int> row;

	size_t pos = 0;
	std::string token;
	std::string delimiter = ",";
	int value;

	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		s.erase(0, pos + delimiter.length());

		value = std::stoi(token);
		row.insert(value);
	}
	// last item in the string
	row.insert(std::stoi(s));

	return row;
}



/**
Helper function for reading in map data

@param file_name - The filename where the map is stored.

@return - A grid of chars representing a map.
*/
std::vector < std::set <int> > read_map(std::string file_name) {
	std::ifstream infile(file_name);
	std::vector < std::set <int> > map;
	if (infile.is_open()) {

		char color;
		std::set <int> row;

		std::string line;

		while (std::getline(infile, line)) {
			row = read_line(line);
			map.push_back(row);
		}
	}
	return map;
}