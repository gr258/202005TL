#include "gtest/gtest.h"
#include "Game.h"


#define EXPECT_EQ_GAME_SUCCESS(MS,N,EXPR)	\
	EXPECT_EQ(SUCCESS_M,(EXPR));	\
	EXPECT_EQ(MS,MaxScore);	\
	EXPECT_EQ(N,Number);

TEST(GAME, GIVEN_invalid_string_WHEN_GetMaxScoreAndNumber_THEN_RETURN_FORMAT_ERROR){
	Game gm;
	int MaxScore = 0, Number = 0;

	EXPECT_EQ(FORMAT_ERROR_M, gm.GetMaxScoreAndNumber("{", MaxScore, Number));
	EXPECT_EQ(FORMAT_ERROR_M, gm.GetMaxScoreAndNumber("1111", MaxScore, Number));
}

TEST(GAME, GIVEN_invalid_content_json_string_WHEN_GetMaxScoreAndNumber_THEN_RETURN_DATA_ERROR){
	Game gm;
	int MaxScore = 0, Number = 0;

	EXPECT_EQ(DATA_ERROR_M, gm.GetMaxScoreAndNumber("{}", MaxScore, Number));
	EXPECT_EQ(DATA_ERROR_M, gm.GetMaxScoreAndNumber("{\"P\":[\"123456\",\"abcdEf\"],\"C\":[3,2],\"N\":\"n\",\"MS\":1}", MaxScore, Number));
	EXPECT_EQ(DATA_ERROR_M, gm.GetMaxScoreAndNumber("{\"Q\":[\"123456\",\"abcdEf\"],\"C\":[3,2],\"N\":2,\"MS\":1}", MaxScore, Number));
	EXPECT_EQ(DATA_ERROR_M, gm.GetMaxScoreAndNumber("{\"P\":[\"123456\",\"abcdEf\"],\"C\":[3,2],\"N\":2,\"MS\":-1}", MaxScore, Number));
	EXPECT_EQ(DATA_ERROR_M, gm.GetMaxScoreAndNumber("{\"P\":[123456,\"abcdEf\"],\"C\":[3,2],\"N\":2,\"MS\":1}", MaxScore, Number));
	EXPECT_EQ(DATA_ERROR_M, gm.GetMaxScoreAndNumber("{\"P\":[\"123456\",\"abcdEf\"],\"C\":[3],\"N\":2,\"MS\":1}", MaxScore, Number));
}

TEST(GAME, GIVEN_valid_json_string_WHEN_GetMaxScoreAndNumber_THEN_RETURN_SUCCESS){
	Game gm;
	int MaxScore = 0, Number = 0;

	EXPECT_EQ_GAME_SUCCESS(1, 0, gm.GetMaxScoreAndNumber("{\"P\":[\"123456\"],\"C\":[3],\"N\":1,\"MS\":1}", MaxScore, Number));
	EXPECT_EQ_GAME_SUCCESS(2, 1, gm.GetMaxScoreAndNumber("{\"P\":[\"abcdEf\"],\"C\":[2],\"N\":2,\"MS\":1}", MaxScore, Number));
	EXPECT_EQ_GAME_SUCCESS(1, 0, gm.GetMaxScoreAndNumber("{\"P\":[\"abcdEf\"],\"C\":[2],\"N\":0,\"MS\":1}", MaxScore, Number));

	EXPECT_EQ_GAME_SUCCESS(3, 2, gm.GetMaxScoreAndNumber("{\"P\":[\"123456\",\"abcdEf\"],\"C\":[3,2],\"N\":2,\"MS\":1}", MaxScore, Number));
	EXPECT_EQ_GAME_SUCCESS(3, 1, gm.GetMaxScoreAndNumber("{\"P\":[\"123456\",\"abcdEf\"],\"C\":[2,3],\"N\":2,\"MS\":1}", MaxScore, Number));
	EXPECT_EQ_GAME_SUCCESS(1, 0, gm.GetMaxScoreAndNumber("{\"P\":[\"123456\",\"abcdEf\"],\"C\":[2,1],\"N\":2,\"MS\":1}", MaxScore, Number));
	EXPECT_EQ_GAME_SUCCESS(2, 1, gm.GetMaxScoreAndNumber("{\"P\":[\"123456\",\"abcdEf\"],\"C\":[2,2],\"N\":2,\"MS\":1}", MaxScore, Number));
	EXPECT_EQ_GAME_SUCCESS(2, 1, gm.GetMaxScoreAndNumber("{\"P\":[\"123456\",\"abcdEf\"],\"C\":[3,2],\"N\":1,\"MS\":1}", MaxScore, Number));
	EXPECT_EQ_GAME_SUCCESS(1, 0, gm.GetMaxScoreAndNumber("{\"P\":[\"123456\",\"abcdEf\"],\"C\":[3,2],\"N\":-1,\"MS\":1}", MaxScore, Number));

	EXPECT_EQ_GAME_SUCCESS(0, 0, gm.GetMaxScoreAndNumber("{\"P\":[\"123456\",\"abcdEf\"],\"C\":[3,2],\"N\":2,\"MS\":0}", MaxScore, Number));
	EXPECT_EQ_GAME_SUCCESS(4, 2, gm.GetMaxScoreAndNumber("{\"P\":[\"1234Ef\",\"abcdEf\"],\"C\":[3,2],\"N\":2,\"MS\":0}", MaxScore, Number));
}