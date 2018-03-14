#include <vector>
#include <string>

using namespace std;

vector<float> sense(vector<float> p, vector<string> world, float pHit, float pMiss, string Z) {
/*
q=[]
for i in range(len(p)):
hit = (Z == world[i])
q.append(p[i] * (hit * pHit + (1-hit) * pMiss))
s = sum(q)
for i in range(len(q)):
q[i] = q[i] / s
return q
*/
	vector<float> result;
	float sum = 0;

	for (int i = 0; i < p.size(); i++) {
		bool hit = (Z == world[i]);
		float value = p[i] * (hit * pHit + (1 - hit) * pMiss);
		result.push_back(value);
		sum += value;
	}

	for (int i = 0; i < p.size(); i++) {
		result[i] = result[i] / sum;
	}

	return result;
}

vector<float> move(vector<float> p, float pExact, float pOvershoot, float pUndershoot, int U) {
/*
q = []
for i in range(len(p)):
s = pExact * p[(i-U) % len(p)]
s = s + pOvershoot * p[(i-U-1) % len(p)]
s = s + pUndershoot * p[(i-U+1) % len(p)]
q.append(s)
return q*/
	vector<float> result;
	for (int i = 0; i < p.size(); i++) {
		float value = pExact * p[(i - U) % p.size()];
		value += pOvershoot * p[(i - U - 1) % p.size()];
		value += pUndershoot * p[(i - U + 1) % p.size()];
		result.push_back(value);
	}

	return result;
}