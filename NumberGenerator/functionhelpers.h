#ifndef FUNCTIONHELPERS_H
#define FUNCTIONHELPERS_H

#include <vector>
#include <set>

float * calculateGaussian(std::vector<float> &grid);
void calEvenNumbers(std::vector< std::vector<int> > &filecontent);
float * updateGaussian(float mean1, float var1, float mean2, float var2);
float * predictGaussian(float mean1, float var1, float mean2, float var2);
void findDuplicate(std::vector< std::vector<int> > &filecontent, std::vector< std::vector<int> > &pick);

#endif