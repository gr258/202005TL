#include "gtest/gtest.h"
#include "PassWord.h"

TEST(PASSWORD,GIVEN_size_less_6_WHEN_Strong_THEN_RETURN_OK){
	PassWord pw;

	EXPECT_EQ(6, pw.Strong(""));
	EXPECT_EQ(5, pw.Strong("."));
	EXPECT_EQ(4, pw.Strong("a1"));
	EXPECT_EQ(3, pw.Strong("..."));

	EXPECT_EQ(3, pw.Strong("...."));
	EXPECT_EQ(2, pw.Strong(".1aA"));
	EXPECT_EQ(3, pw.Strong("....."));
	EXPECT_EQ(1, pw.Strong("Aa1.."));
}

TEST(PASSWORD, GIVEN_size_less_or_equl_20_WHEN_Strong_THEN_RETURN_OK){
	PassWord pw;

	EXPECT_EQ(0, pw.Strong("Str0ng"));
	EXPECT_EQ(1, pw.Strong("abcdEf"));
	EXPECT_EQ(2, pw.Strong("123456"));
	EXPECT_EQ(3, pw.Strong("......"));

	EXPECT_EQ(2, pw.Strong("aaaaaaa"));
	EXPECT_EQ(2, pw.Strong("AAAAAAAA"));
	EXPECT_EQ(3, pw.Strong("........."));

	EXPECT_EQ(3, pw.Strong("Aa11111111111"));
	EXPECT_EQ(4, pw.Strong("..AAAAAAAAAAAA"));
	EXPECT_EQ(6, pw.Strong("aaaaaaaaaaaaaaaaaaaa"));
}

TEST(PASSWORD, GIVEN_size_greater_20_WHEN_Strong_THEN_RETURN_OK){
	PassWord pw;

	EXPECT_EQ(1, pw.Strong("ABABABABABABABABABAb1"));
	EXPECT_EQ(2, pw.Strong("ABABABABABABABABABAB1"));
	EXPECT_EQ(7, pw.Strong("111222333444555666777"));

	EXPECT_EQ(7, pw.Strong("1112223334445556667777"));
	EXPECT_EQ(7, pw.Strong("1111111111111116667777"));
	EXPECT_EQ(8, pw.Strong("1111111111111111117777"));

	EXPECT_EQ(8,  pw.Strong("aaaaaaaaaaaaaaaaaaaaaa"));
	EXPECT_EQ(9,  pw.Strong("aaaaaaaaaaaaaaaaaaaaaaa"));
	EXPECT_EQ(10, pw.Strong("aaaaaaaaaaaaaaaaaaaaaaaa"));

	EXPECT_EQ(11, pw.Strong("aaaaaaaaaaaaaaaaaaaaaabbb"));
	EXPECT_EQ(12, pw.Strong("aaaaaaaaaaaaaaaaaaaaaabbbb"));
	EXPECT_EQ(13, pw.Strong("aaaaaaaaaaaaaaaaaaaaaaabbbb"));

	EXPECT_EQ(14, pw.Strong("aaaaaaaaaaaaaaaaaaaaaaabbbbb"));
	EXPECT_EQ(13, pw.Strong("aaaaaaaaaaaaaaaaaaaacccbbbbb"));
	EXPECT_EQ(12, pw.Strong("aaaaaaaaaaaaaaaaadddcccbbbbb"));
}
