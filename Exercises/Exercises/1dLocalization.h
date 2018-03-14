#include <vector>
#include <string>

using namespace std;

vector<float> sense(vector<float> p, vector<string> world, float pHit, float pMiss, string Z);
vector<float> move(vector<float> p, float pExact, float pOvershoot, float pUndershoot, int U);