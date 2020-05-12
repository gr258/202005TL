#include "gtest/gtest.h"
#include "Game.h"

TEST(GAME, GIVEN_json_string_WHEN_GetMaxScoreAndNumber_THEN_RETURN_OK){
	Game gm;
	int MaxScore = 0, Number = 0;

	EXPECT_EQ(1, gm.GetMaxScoreAndNumber("{", MaxScore, Number));
	EXPECT_EQ(1, gm.GetMaxScoreAndNumber("1111", MaxScore, Number));

	EXPECT_EQ(0, gm.GetMaxScoreAndNumber("{\"P\":[\"123456\",\"abcdEf\"],\"C\":[3,2],\"N\":2,\"MS\":1}", MaxScore, Number));
	EXPECT_EQ(3, MaxScore);
	EXPECT_EQ(2, Number);

	EXPECT_EQ(0, gm.GetMaxScoreAndNumber("{\"P\":[\"abcdEf\"],\"C\":[2],\"N\":2,\"MS\":1}", MaxScore, Number));
	EXPECT_EQ(2, MaxScore);
	EXPECT_EQ(1, Number);
}