#include <gtest/gtest.h>
#include "message_parser.h"
#include <stdexcept>

TEST(MessageParserTest, ValidLine){
    std::string line = "1,2,3";

    Point3D parsed_point = parse_point(line);
    EXPECT_DOUBLE_EQ(parsed_point.x, 1.0);
    EXPECT_DOUBLE_EQ(parsed_point.y, 2.0);
    EXPECT_DOUBLE_EQ(parsed_point.z, 3.0);
}

TEST(MessageParserTest, ThrowsOnLessThan3Input){
    std::string line = "1,2";
    EXPECT_THROW(parse_point(line), std::invalid_argument);
}

TEST(MessageParserTest, ThrowsOnInvalidInput){
    std::string line = "1,abc,2";
    EXPECT_THROW(parse_point(line), std::invalid_argument);
}

TEST(MessageParserTest, ThrowsOnInvalidStringInput){
    std::string line = "1,2,3abc";

    EXPECT_THROW(parse_point(line), std::invalid_argument);
}

TEST(MessageParserTest, AcceptsLeadingWhiteSpaces){
    std::string line = " 1, 2, 3";
    Point3D result = parse_point(line);
    EXPECT_DOUBLE_EQ(result.x, 1);
    EXPECT_DOUBLE_EQ(result.y, 2);
    EXPECT_DOUBLE_EQ(result.z, 3);
}

TEST(MessageParserTest, ThrowsOnTrailingWhiteSpace)
{
    std::string line = "1 ,2 ,3";

    EXPECT_THROW(parse_point(line), std::invalid_argument);
}

TEST(MessageParserTest, ParsesNanWithoutThrowing)
{
    Point3D p = parse_point("nan,2,3");
    EXPECT_FALSE(is_valid_point(p));
}