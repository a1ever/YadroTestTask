#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <chrono>

namespace gameclub{
using namespace std::chrono;
typedef time_point<system_clock, std::chrono::minutes> my_time;

my_time StringToTime(const std::string& timeStr);

my_time TimeDelta(const my_time& time1, const my_time& time2);

my_time TimeSum(const my_time& time1, const my_time& time2);

uint32_t GetMinutes(const my_time& time1);

std::string TimeToString(const my_time& time1);
}
