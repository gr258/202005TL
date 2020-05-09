#include "gtest/gtest.h"
#include "json/json.h"

TEST(JSONFILTER,GIVEN_BASIC_JSON_FILE_WHEN_FILTER_IS_WEIGHT_EQ_100_THEN_RETURN_ONE)
{
    Json::Value root;
    Json::Value person;
    person["name"] = "hello world";
    person["age"] = 100;
    root.append(person);

    printf("%s\n",root.toStyledString().c_str());
}


