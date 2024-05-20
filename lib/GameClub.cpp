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
std::unordered_map<std::string, gameclub::TableTime>& gameclub::GameClub::GetClientsOnTables() {
    return clients_on_tables_;
}
std::unordered_map<uint32_t, gameclub::ClientTime>& gameclub::GameClub::GetTables() {
    return tables_;
}
std::unordered_map<uint32_t, gameclub::ClientTime>& gameclub::GameClub::GetAnsTables() {
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




