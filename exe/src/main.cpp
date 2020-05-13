#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Game.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc < 2){
		printf("Please input json filename\n");
		return 0;
	}

	ifstream fin(argv[1]);
	ostringstream sin;
	sin << fin.rdbuf();
	string strJson = sin.str();
	fin.close();
	
	Game gm;
	int MaxScore = 0, Number = 0;
	int nRet = gm.GetMaxScoreAndNumber(strJson, MaxScore, Number);
	switch (nRet){
	case FORMAT_ERROR_M:
		printf("format error\n");
		break;
	case DATA_ERROR_M:
		printf("data error\n");
		break;
	default:
		printf("%d-%d\n", MaxScore, Number);
	}

    return 0;
}

