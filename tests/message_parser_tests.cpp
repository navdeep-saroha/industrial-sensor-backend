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
TEST(MessageParserTest, ThrowsOnMoreThan3Values)
{
    EXPECT_THROW(parse_point("1,2,3,4"), std::invalid_argument);
}

TEST(FrameTest, Oneline){
    std::string buffer = "1,2,3\n";
    std::vector<std::string> lines = extract_line(buffer);
    EXPECT_EQ(lines[0], "1,2,3");
    EXPECT_TRUE(buffer.empty());
}

TEST(FrameTest, IncompleteLineBufferNotErased)
{
    std::string buffer = "1,2,";
    std::vector<std::string> lines = extract_line(buffer);
    EXPECT_TRUE(lines.empty());
    EXPECT_EQ(buffer, "1,2,");
}

TEST(FrameTest, AppendSecondPacket){
    std::string buffer = "1,2,";
    std::vector<std::string> lines = extract_line(buffer);
    buffer += "3\n";
    lines = extract_line(buffer);
    EXPECT_TRUE(buffer.empty());
    EXPECT_EQ(lines[0], "1,2,3");
}

TEST(FrameTest, MultiLinePacket)
{
    std::string buffer = "1,2,3\n4,5,6\n7,8,9\n";
    std::vector<std::string> lines = extract_line(buffer);
    EXPECT_EQ(lines[0], "1,2,3");
    EXPECT_EQ(lines[1], "4,5,6");
    EXPECT_EQ(lines[2], "7,8,9");
    ASSERT_EQ(lines.size(),3);
    EXPECT_TRUE(buffer.empty());
}