#include "Game.h"
#include "PassWord.h"

//输入json串，例如：{"P":["123456","abcdEf"],"C":[3,2],"N":2,"MS":1}
//输出格式为MaxScore-Number："自身总积分MS-修改的密码个数"
//返回值0:成功 1:'format error' 2:'data error'
int Game::GetMaxScoreAndNumber(string strJson, int &MaxScore, int &Number){
	int nRet = Parse(strJson);
	if (SUCCESS_M != nRet) return nRet;

	MaxScore = MS;				//自身总积分初始为MS
	Number = 0;					//修改的密码个数初始为0
	InitCostScoreArrary();		//初始化改造的消耗与净收益二维数组
	
	//选择最多N个密码进行改造，nCost从0开始，记录每次改造的最大成本
	for (int nCost = 0; Number < N; ++Number){
		if (GetMaxScore(nCost, MaxScore)) break;
	}

	return SUCCESS_M;
}

int Game::Parse(string &strJson){
	Json::Value jsonVal;
	Json::Reader *pJsonParser = new Json::Reader();
	bool bSucc = pJsonParser->parse(strJson, jsonVal);
	delete pJsonParser;

	if (!bSucc || !jsonVal.isObject()){
		return FORMAT_ERROR_M;
	}

	int nRet = SUCCESS_M;
	
	nRet = ParseP(jsonVal);
	if (SUCCESS_M != nRet) return nRet;

	nRet = ParseC(jsonVal);
	if (SUCCESS_M != nRet) return nRet;

	nRet = ParseN(jsonVal);
	if (SUCCESS_M != nRet) return nRet;

	nRet = ParseMS(jsonVal);
	if (SUCCESS_M != nRet) return nRet;

	if (P.size() != C.size()) return DATA_ERROR_M;

	if (MS < 0) return DATA_ERROR_M;

	return SUCCESS_M;
}

int Game::ParseP(Json::Value &jsonVal){
	P.clear();

	if (!jsonVal.isMember("P")) return DATA_ERROR_M;

	if (!jsonVal["P"].isArray()) return DATA_ERROR_M;

	int nSize = jsonVal["P"].size();
	
	for (int i = 0; i < nSize; ++i){
		if (!jsonVal["P"][i].isString()) return DATA_ERROR_M;

		P.push_back(jsonVal["P"][i].asString());
	}
	return SUCCESS_M;
}

int Game::ParseC(Json::Value &jsonVal){
	C.clear();

	if (!jsonVal.isMember("C")) return DATA_ERROR_M;

	if (!jsonVal["C"].isArray()) return DATA_ERROR_M;

	int nSize = jsonVal["C"].size();
	
	for (int i = 0; i < nSize; ++i){
		if (!jsonVal["C"][i].isInt()) return DATA_ERROR_M;

		C.push_back(jsonVal["C"][i].asInt());
	}
	return SUCCESS_M;
}

int Game::ParseN(Json::Value &jsonVal){
	return ParseInt(jsonVal, "N", N);
}

int Game::ParseMS(Json::Value &jsonVal){
	return ParseInt(jsonVal, "MS", MS);
}

int Game::ParseInt(Json::Value &jsonVal, string key, int &val){
	if (!jsonVal.isMember(key)) return DATA_ERROR_M;

	if (!jsonVal[key].isInt()) return DATA_ERROR_M;

	val = jsonVal[key].asInt();
	return SUCCESS_M;
}

//初始化改造的消耗与净收益二维数组
void Game::InitCostScoreArrary(){
	ScorePool.clear();
	CostScoreArrary.clear();
	//消耗---净收益 映射数组，按消耗（改造成本）进行分组，由于改造单个密码的消耗不大于MAX_LEN_M，因此数组大小为MAX_LEN_M
	CostScoreArrary.resize(MAX_LEN_M);
	PassWord pw;
	int nSize = C.size();

	for (int i = 0; i < nSize; ++i){
		int nCost = pw.Strong(P[i]);	//获取改造的消耗
		int nScore = C[i] - nCost;		//获取改造后的净收益

		//无净收益或净收益为负数，不予考虑
		if (nScore <= 0) continue;

		//异常保护
		if (nCost < 0 || nCost >= MAX_LEN_M) continue;

		//消耗---净收益 保存到映射数组
		CostScoreArrary[nCost].push_back(nScore);
	}
}

//从消耗不大于成本的所有收益中，获取最大的那个收益
int Game::GetMaxScore(int &nCost, int &MaxScore){
	bool bSort = false;

	//总积分MaxScore即是当前成本，将消耗不大于成本的所有收益放入收益池中
	for (; nCost <= MaxScore && nCost < MAX_LEN_M; ++nCost){
		if (CostScoreArrary[nCost].size() == 0)	continue;

		ScorePool.insert(ScorePool.end(), CostScoreArrary[nCost].begin(), CostScoreArrary[nCost].end());
		bSort = true;
	}

	//收益池为空，结束处理
	if (ScorePool.size() == 0) return 1;

	//对收益池排序，获取最大的那个收益，累计到自身总积分MaxScore中
	if (bSort) sort(ScorePool.begin(), ScorePool.end());

	vector<int>::iterator it = ScorePool.end() - 1;
	MaxScore += *it;

	//从收益池中挪出最大的那个收益
	ScorePool.erase(it);

	return 0;
}