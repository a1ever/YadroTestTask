#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <chrono>

namespace gameclub{
using namespace std::chrono;
typedef time_point<system_clock, std::chrono::minutes> my_time;

my_time StringToTime(const std::string& timeStr) {
    std::istringstream iss(timeStr);
    int hours, mins;
    char delimiter;
    iss >> hours >> delimiter >> mins;

    if (delimiter != ':' || iss.fail()) {
        throw std::invalid_argument("Invalid time format");
    }

    return my_time{hours * 60min + mins * 1min};
}

my_time TimeDelta(const my_time& time1, const my_time& time2) {
    if (time1 > time2) return my_time{duration_cast<std::chrono::minutes>(time1 - time2)};
    return my_time{duration_cast<std::chrono::minutes>(time2 - time1)};
}

std::string TimeToString(const my_time& time1) {
    int total_minutes = duration_cast<minutes>(time1.time_since_epoch()).count();
    int hours = total_minutes / 60;
    int minutes = total_minutes % 60;
    std::ostringstream ss;
    ss << std::setfill('0') << std::setw(2) << hours << ":"
       << std::setfill('0') << std::setw(2) << minutes;
    return ss.str();
}
}
