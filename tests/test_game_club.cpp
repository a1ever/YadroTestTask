#include <lib/GameClub.h>

#include <sstream>

#include <gtest/gtest.h>

using namespace GameClub;

std::vector<std::string> SplitString(const std::string& str) {
    std::istringstream iss(str);

    return {std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>()};
}