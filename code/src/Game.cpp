#include "Game.h"
#include "PassWord.h"

//����json�������磺{"P":["123456","abcdEf"],"C":[3,2],"N":2,"MS":1}
//�����ʽΪMaxScore-Number��"�����ܻ���MS-�޸ĵ��������"
//����ֵ0:�ɹ� 1:'format error' 2:'data error'
int Game::GetMaxScoreAndNumber(string strJson, int &MaxScore, int &Number){
	int nRet = Parse(strJson);
	if (SUCCESS_M != nRet) return nRet;

	InitCostScoreMap();			//��ʼ������������뾻����ӳ����
	MaxScore = MS;				//�����ܻ��ֳ�ʼΪMS
	//ѡ�����N��������и��죬nCost��0��ʼ����¼ÿ�θ�������ɱ�
	for (Number = 0; Number < N; ++Number){
		if (GetMaxScore(MaxScore)) break;
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

	int nRet = Parse(jsonVal);
	if (SUCCESS_M != nRet) return nRet;

	if (P.size() != C.size()) return DATA_ERROR_M;

	if (MS < 0) return DATA_ERROR_M;

	return SUCCESS_M;
}

int Game::Parse(Json::Value &jsonVal){
	int nRet = SUCCESS_M;

	nRet = ParseP(jsonVal);
	if (SUCCESS_M != nRet) return nRet;

	nRet = ParseC(jsonVal);
	if (SUCCESS_M != nRet) return nRet;

	nRet = ParseN(jsonVal);
	if (SUCCESS_M != nRet) return nRet;

	nRet = ParseMS(jsonVal);
	if (SUCCESS_M != nRet) return nRet;

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

//��ʼ������������뾻����ӳ����
void Game::InitCostScoreMap(){
	ScorePool.clear();
	CostScoreMap.clear();

	PassWord pw;
	int nSize = C.size();

	for (int i = 0; i < nSize; ++i){
		int nCost = pw.Strong(P[i]);	//��ȡ���������
		int nScore = C[i] - nCost;		//��ȡ�����ľ�����

		//�޾����������Ϊ���������迼��
		if (nScore <= 0) continue;

		//����---������ ���浽ӳ������
		CostScoreMap[nCost].push_back(nScore);
	}
}

//�����Ĳ����ڳɱ������������У���ȡ�����Ǹ�����
//����0���ɹ� 1��ʧ��
int Game::GetMaxScore(int &MaxScore){
	bool bSort = false;

	//�ܻ���MaxScore���ǵ�ǰ�ɱ��������Ĳ����ڳɱ���������������������
	for (map<int, vector<int> >::iterator it = CostScoreMap.begin(); it != CostScoreMap.end(); ){
		if (it->first <= MaxScore){
			ScorePool.insert(ScorePool.end(), it->second.begin(), it->second.end());
			bSort = true;
			CostScoreMap.erase(it++);
		}
		else{
			++it;
		}
	}

	//�����Ϊ�գ���������
	if (ScorePool.size() == 0) return 1;

	//�����������
	if (bSort) sort(ScorePool.begin(), ScorePool.end());

	//��ȡ�����Ǹ����棬�ۼƵ������ܻ���MaxScore��
	vector<int>::iterator it = ScorePool.end() - 1;
	MaxScore += *it;

	//���������Ų�������Ǹ�����
	ScorePool.erase(it);

	return 0;
}