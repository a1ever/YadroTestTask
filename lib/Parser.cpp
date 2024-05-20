#include "Parser.h"
#include "GameClub.h"

#include <iostream>
#include <string>

namespace gameclub {
std::vector<std::string> SplitString(const std::string& str) {
    std::istringstream iss(str);

    return {std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>()};
}

std::string Parser::ParseEvent(const std::string& string) {
    std::regex event_regex = std::regex(R"(^(0[0-9]|1[0-9]|2[0-3]):[0-5][0-9]\s(2\s[a-z0-9_-]+\s[0-9]+|[134]\s[a-z0-9_-]+)$)");
    if (!std::regex_match(string, event_regex)) {
        return string;
    }

    auto in = SplitString(string);
    auto time = StringToTime(in[0]);
    if (!events_.empty()){
        auto& event = events_.back();
        if (event->GetTime() > time){
            return string;
        }
    }
    uint32_t table{};
    switch (in[1][0]) {
        case '1':
            this->events_.push(std::make_unique<EventId1>(time, in[2]));
            break;
        case '2':
            table = std::stoi(in[3]);
            if (table == 0 || table > GameClub::getInstance().GetTablesAmount()) {
                return string;
            }
            this->events_.push(std::make_unique<EventId2>(time, in[2], table));
            break;
        case '3':
            this->events_.push(std::make_unique<EventId3>(time, in[2]));
            break;
        case '4':
            this->events_.push(std::make_unique<EventId4>(time, in[2]));
            break;
    }
    return "";
}

std::string Parser::ParseHourlyPricing(const std::string& string) {
    std::regex number_regex = std::regex(R"(^\d+$)");
    if (!std::regex_match(string, number_regex)) return string;
    GameClub::getInstance().SetHourPrice(std::stoi(string));
    return "";
}

std::string Parser::ParseOpeningHours(const std::string& string) {
    std::regex working_hours_regex = std::regex(R"(^(0[0-9]|1[0-9]|2[0-3]):[0-5][0-9]\s(0[0-9]|1[0-9]|2[0-3]):[0-5][0-9]$)");
    if (!std::regex_match(string, working_hours_regex)) return string;
    auto time1 = StringToTime(string.substr(0,5)); // 0 1 2 3 4
    auto time2 = StringToTime(string.substr(5,5)); // 5 6 7 8 9
    //! Не уточнено в условии, поэтому считаю что время открытия и закрытия происходит в 1 день, и отрытие не может быть позже закрытия
    if (time2 < time1) {
        return string;
    }
    GameClub::getInstance().SetOpeningTime(time1);
    GameClub::getInstance().SetClosingTime(time2);
    return "";
}

std::string Parser::ParseTableAmount(const std::string& string) {
    std::regex number_regex = std::regex(R"(^\d+$)");
    if (!std::regex_match(string, number_regex)) return string;
    GameClub::getInstance().SetTablesAmount(std::stoi(string));
    return "";
}

std::string Parser::Parse(std::istream& in) {
    std::string s;
    std::string ans;
    if(!std::getline(in, s)) return "FAILED TO READ";
    if (!(ans = ParseTableAmount(s)).empty()) return ans;
    if(!std::getline(in, s)) return "FAILED TO READ";
    if (!(ans = ParseOpeningHours(s)).empty()) return ans;
    if(!std::getline(in, s)) return "FAILED TO READ";
    if (!(ans = ParseHourlyPricing(s)).empty()) return ans;
    while (std::getline(in, s)) {
        if (!(ans = ParseEvent(s)).empty()) return ans;
    }
    return "";
}

std::queue<std::unique_ptr<gameclub::IEventCommand>>& Parser::GetEvents() {
    return events_;
}
}