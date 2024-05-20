#pragma once
#include "TimeParser.h"

#include <string>
#include <queue>
#include <unordered_map>
#include <unordered_set>
namespace gameclub {
struct ClientTime{
  my_time time{};
  std::string client{};
};
struct TableTime{
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
  my_time opening_time;
  my_time closing_time;
  std::unordered_set<std::string> clients_;
  std::unordered_map<uint32_t, ClientTime> tables_;
  std::unordered_map<uint32_t, ClientTime> ans_tables_;
  std::unordered_map<std::string, TableTime> clients_on_tables_;
  std::queue<std::string> waiting_list_;
  GameClub();
 public:
  GameClub(const GameClub& obj) = delete;
  GameClub& operator=(const GameClub& obj) = delete;
  static GameClub& getInstance();

  const my_time& GetOpeningTime() const;
  void SetOpeningTime(const my_time& opening_time);
  const my_time& GetClosingTime() const;
  void SetClosingTime(const my_time& closing_time);
  uint32_t GetTablesAmount() const;
  void SetTablesAmount(uint32_t tables_amount);
  std::unordered_map<std::string, TableTime>& GetClientsOnTables();
  std::unordered_map<uint32_t, ClientTime>& GetTables();
  std::unordered_map<uint32_t, ClientTime>& GetAnsTables();
  std::unordered_set<std::string>& GetClients();
  std::queue<std::string>& GetWaitingList();
};
}

