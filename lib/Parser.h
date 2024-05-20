#pragma once

#include <regex>
namespace gameclub {
    std::regex number_regex = std::regex(R"(^\d+$)");
    std::regex working_hours_regex = std::regex(R"(^(0[0-9]|1[0-9]|2[0-3]):[0-5][0-9]\s(0[0-9]|1[0-9]|2[0-3]):[0-5][0-9]$)");
    std::regex event_regex = std::regex(R"(^(0[0-9]|1[0-9]|2[0-3]):[0-5][0-9]\s(2\s[a-z0-9_-]+\s[0-9]+|[134]\s[a-z0-9_-]+)$)");
class Parser {

};
}
