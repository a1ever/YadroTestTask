#include "TimeParser.h"

namespace gameclub{
using namespace std::chrono;
typedef time_point<system_clock, std::chrono::minutes> my_time;

my_time StringToTime(const std::string& timeStr) {
    std::istringstream iss(timeStr);
    int32_t hours, mins;
    char delimiter;
    iss >> hours >> delimiter >> mins;

    return my_time{hours * 60min + mins * 1min};
}

my_time TimeDelta(const my_time& time1, const my_time& time2) {
    if (time1 > time2) return my_time{duration_cast<std::chrono::minutes>(time1 - time2)};
    return my_time{duration_cast<std::chrono::minutes>(time2 - time1)};
}

my_time TimeSum(const my_time& time1, const my_time& time2) {
    int32_t total_minutes1 = duration_cast<minutes>(time1.time_since_epoch()).count();
    int32_t total_minutes2 = duration_cast<minutes>(time2.time_since_epoch()).count();
    return my_time{(total_minutes1+total_minutes2)*1min};
}

uint32_t GetMinutes(const my_time& time1) {
    return duration_cast<minutes>(time1.time_since_epoch()).count();
}

std::string TimeToString(const my_time& time1) {
    int32_t total_minutes = duration_cast<minutes>(time1.time_since_epoch()).count();
    int32_t hours = total_minutes / 60;
    int32_t minutes = total_minutes % 60;
    std::ostringstream ss;
    ss << std::setfill('0') << std::setw(2) << hours << ":"
       << std::setfill('0') << std::setw(2) << minutes;
    return ss.str();
}
}
