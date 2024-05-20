#pragma once

#include "GameClubEvents.h"
#include <regex>
#include <queue>
namespace gameclub {
class Parser {
 private:
  std::queue<std::unique_ptr<gameclub::IEventCommand>> events_;
  std::string ParseTableAmount(const std::string& string);
  std::string ParseOpeningHours(const std::string& string);
  std::string ParseHourlyPricing(const std::string& string);
  std::string ParseEvent(const std::string& string);
 public:
    std::string Parse(std::istream& in);
    std::queue<std::unique_ptr<gameclub::IEventCommand>>& GetEvents() ;
};
}
