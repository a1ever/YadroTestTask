#pragma once
#include "TimeParser.h"

#include <string>
#include <queue>
#include <unordered_map>
#include <unordered_set>
namespace gameclub {
struct TimeClient{
  my_time time{};
  std::string client{};
};
struct TimeMoney{
  my_time time{};
  uint64_t money{};
};
struct TimeTableNum{
  my_time time{};
  uint32_t table{};
};

const std::string kErrorYouShallNotPass = "YouShallNotPass";
const std::string kErrorNotOpenYet = "NotOpenYet";
const std::string kErrorPlaceIsBusy = "PlaceIsBusy";
const std::string kErrorClientUnknown = "ClientUnknown";
const std::string kErrorICanWaitNoLonger = "ICanWaitNoLonger!";

class GameClub {
 private:
  uint32_t tables_amount{};
  uint32_t hour_price{};
  my_time opening_time;
  my_time closing_time;
  std::unordered_set<std::string> clients_;
  std::unordered_map<uint32_t, TimeClient> tables_;
  std::vector<TimeMoney> ans_tables_;
  std::unordered_map<std::string, TimeTableNum> clients_on_tables_;
  std::queue<std::string> waiting_list_;
  GameClub();
 public:
  GameClub(const GameClub& obj) = delete;
  GameClub& operator=(const GameClub& obj) = delete;
  static GameClub& getInstance();
  uint32_t GetHourPrice() const;
  void SetHourPrice(uint32_t hour_price);
  const my_time& GetOpeningTime() const;
  void SetOpeningTime(const my_time& opening_time);
  const my_time& GetClosingTime() const;
  void SetClosingTime(const my_time& closing_time);
  uint32_t GetTablesAmount() const;
  void SetTablesAmount(uint32_t tables_amount);
  std::unordered_map<std::string, TimeTableNum>& GetClientsOnTables();
  std::unordered_map<uint32_t, TimeClient>& GetTables();
  std::vector<TimeMoney>& GetAnsTables();
  std::unordered_set<std::string>& GetClients();
  std::queue<std::string>& GetWaitingList();
  uint64_t CalculatePricingForMinutes(const my_time& time);
};
}

