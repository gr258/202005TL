#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include "json/json.h"

using namespace std;

#define SUCCESS_M		0
#define FORMAT_ERROR_M	1
#define DATA_ERROR_M	2

class Game{
public:
	int GetMaxScoreAndNumber(string strJson, int &MaxScore, int &Number);
private:
	int Parse(string &strJson);
	int Parse(Json::Value &jsonVal);
	int ParseP(Json::Value &jsonVal);
	int ParseC(Json::Value &jsonVal);
	int ParseMS(Json::Value &jsonVal);
	int ParseN(Json::Value &jsonVal);
	int ParseInt(Json::Value &jsonVal, string key, int &val);

	void InitCostScoreMap();
	int GetMaxScore(int &MaxScore);

	vector<string> P;
	vector<int> C;
	int N;
	int MS;

	map<int, vector<int>>	CostScoreMap;
	vector<int>				ScorePool;
};