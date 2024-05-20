#include <string>
#include <iostream>
#include "GameClub.h"

gameclub::GameClub::GameClub() = default;

gameclub::GameClub& gameclub::GameClub::getInstance() {
    static GameClub instance;
    return instance;
}
uint32_t gameclub::GameClub::GetTablesAmount() const {
    return tables_amount;
}
void gameclub::GameClub::SetTablesAmount(uint32_t tables_amount) {
    GameClub::tables_amount = tables_amount;
}
std::unordered_map<std::string, gameclub::TimeTableNum>& gameclub::GameClub::GetClientsOnTables() {
    return clients_on_tables_;
}
std::unordered_map<uint32_t, gameclub::TimeClient>& gameclub::GameClub::GetTables() {
    return tables_;
}
std::vector<gameclub::TimeMoney>& gameclub::GameClub::GetAnsTables() {
    return ans_tables_;
}
std::queue<std::string>& gameclub::GameClub::GetWaitingList() {
    return waiting_list_;
}
const gameclub::my_time& gameclub::GameClub::GetOpeningTime() const {
    return opening_time;
}
void gameclub::GameClub::SetOpeningTime(const my_time& opening_time) {
    GameClub::opening_time = opening_time;
}
const gameclub::my_time& gameclub::GameClub::GetClosingTime() const {
    return closing_time;
}
void gameclub::GameClub::SetClosingTime(const my_time& closing_time) {
    GameClub::closing_time = closing_time;
}
std::unordered_set<std::string>& gameclub::GameClub::GetClients() {
    return clients_;
}
uint32_t gameclub::GameClub::GetHourPrice() const {
    return hour_price;
}
void gameclub::GameClub::SetHourPrice(uint32_t hour_price) {
    GameClub::hour_price = hour_price;
}
uint64_t gameclub::GameClub::CalculatePricingForMinutes(const my_time& time) {
    auto minutes = GetMinutes(time);
    uint32_t billing_hrs = (minutes + 59) / 60;
    return billing_hrs * hour_price;
}




