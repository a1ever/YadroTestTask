#include <lib/ProcessGameClub.h>

#include <sstream>

#include <gtest/gtest.h>

using namespace gameclub;

TEST(ProcessGameClubTestSuite, DefaultEverythingTest) {
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
    std::string expected_result = "09:00\n"
                                  "08:48 1 client1\n"
                                  "08:48 13 NotOpenYet\n"
                                  "09:41 1 client1\n"
                                  "09:48 1 client2\n"
                                  "09:52 3 client1\n"
                                  "09:52 13 ICanWaitNoLonger!\n"
                                  "09:54 2 client1 1\n"
                                  "10:25 2 client2 2\n"
                                  "10:58 1 client3\n"
                                  "10:59 2 client3 3\n"
                                  "11:30 1 client4\n"
                                  "11:35 2 client4 2\n"
                                  "11:35 13 PlaceIsBusy\n"
                                  "11:45 3 client4\n"
                                  "12:33 4 client1\n"
                                  "12:33 12 client4 1\n"
                                  "12:43 4 client2\n"
                                  "15:52 4 client4\n"
                                  "19:00 11 client3\n"
                                  "19:00\n"
                                  "1 70 05:58\n"
                                  "2 30 02:18\n"
                                  "3 90 08:01\n";
    std::stringstream ssin;
    std::stringstream ssout;
    ssin << test_data;

    auto process = gameclub::ProcessGameClub(ssin, ssout);
    process.Run();

    ASSERT_EQ(expected_result, ssout.str());
}

TEST(ProcessGameClubTestSuite, YouShallNotPassTest) {
    std::string test_data = "0\n"
                            "09:00 19:00\n"
                            "10\n"
                            "08:48 1 client1\n"
                            "09:41 1 client1\n"
                            "09:42 1 client1\n";
    std::string expected_result = "09:00\n"
                                  "08:48 1 client1\n"
                                  "08:48 13 NotOpenYet\n"
                                  "09:41 1 client1\n"
                                  "09:42 1 client1\n"
                                  "09:42 13 YouShallNotPass\n"
                                  "19:00\n";
    std::stringstream ssin;
    std::stringstream ssout;
    ssin << test_data;

    auto process = gameclub::ProcessGameClub(ssin, ssout);
    process.Run();

    ASSERT_EQ(expected_result, ssout.str());
}

TEST(ProcessGameClubTestSuite, ClientUnknownTest) {
    std::string test_data = "1\n"
                            "09:00 19:00\n"
                            "10\n"
                            "09:41 2 client3 1\n";
    std::string expected_result = "09:00\n"
                                  "09:41 2 client3 1\n"
                                  "09:41 13 ClientUnknown\n"
                                  "19:00\n"
                                  "1 0 00:00\n";
    std::stringstream ssin;
    std::stringstream ssout;
    ssin << test_data;

    auto process = gameclub::ProcessGameClub(ssin, ssout);
    process.Run();

    ASSERT_EQ(expected_result, ssout.str());
}