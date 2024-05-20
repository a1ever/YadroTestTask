#include <lib/Parser.h>

#include <sstream>

#include <gtest/gtest.h>

using namespace gameclub;


TEST(GameClubParserTestSuite, EmptyTest) {
    std::string test_data = "";
    std::stringstream ssin;
    ssin << test_data;

    auto parser = Parser();
    std::string ans = parser.Parse(ssin);

    ASSERT_EQ("FAILED TO READ", ans);
}

TEST(GameClubParserTestSuite, FirstLineError) {
    std::string test_data = "2a";
    std::stringstream ssin;
    ssin << test_data;

    auto parser = Parser();
    std::string ans = parser.Parse(ssin);

    ASSERT_EQ("2a", ans);
}

TEST(GameClubParserTestSuite, SecondLineError) {
    std::string test_data = "3\n"
                            "09:00 19:0\n"
                            "10";
    std::stringstream ssin;
    ssin << test_data;

    auto parser = Parser();
    std::string ans = parser.Parse(ssin);

    ASSERT_EQ("09:00 19:0", ans);
}

TEST(GameClubParserTestSuite, ThrirdLineError) {
    std::string test_data = "3\n"
                            "09:00 19:00\n"
                            "1a0";
    std::stringstream ssin;
    ssin << test_data;

    auto parser = Parser();
    std::string ans = parser.Parse(ssin);

    ASSERT_EQ("1a0", ans);
}

TEST(GameClubParserTestSuite, WrongTimingEvents) {
    std::string test_data = "3\n"
                            "09:00 19:00\n"
                            "10\n"
                            "08:48 1 client1\n"
                            "09:41 1 client1\n"
                            "09:40 1 client2";
    std::stringstream ssin;
    ssin << test_data;

    auto parser = Parser();
    std::string ans = parser.Parse(ssin);

    ASSERT_EQ("09:40 1 client2", ans);
}

TEST(GameClubParserTestSuite, WrongEventsID) {
    std::string test_data = "3\n"
                            "09:00 19:00\n"
                            "10\n"
                            "08:48 0 client1\n"
                            "09:41 1 client1\n"
                            "09:40 1 client2";
    std::stringstream ssin;
    ssin << test_data;

    auto parser = Parser();
    std::string ans = parser.Parse(ssin);

    ASSERT_EQ("08:48 0 client1", ans);
}

TEST(GameClubParserTestSuite, AnyClientNameOk) {
    std::string test_data = "3\n"
                            "09:00 19:00\n"
                            "10\n"
                            "08:48 1 client1_-\n"
                            "09:41 1 client1";
    std::stringstream ssin;
    ssin << test_data;

    auto parser = Parser();
    std::string ans = parser.Parse(ssin);

    ASSERT_EQ("", ans);
}

TEST(GameClubParserTestSuite, OkTest) {
    std::string test_data = "3\n"
                            "09:00 19:00\n"
                            "10\n"
                            "08:48 1 client1\n"
                            "09:41 1 client1\n"
                            "09:48 1 client2\n"
                            "09:52 3 client1\n"
                            "09:54 2 client1 1\n"
                            "10:25 2 client2 2\n"
                            "10:58 1 client3\n"
                            "10:59 2 client3 3\n"
                            "11:30 1 client4\n"
                            "11:35 2 client4 2\n"
                            "11:45 3 client4\n"
                            "12:33 4 client1\n"
                            "12:43 4 client2\n"
                            "15:52 4 client4";
    std::stringstream ssin;
    ssin << test_data;

    auto parser = Parser();
    std::string ans = parser.Parse(ssin);

    ASSERT_EQ("", ans);
}



