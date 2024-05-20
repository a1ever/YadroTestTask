#include "GameClubEvents.h"
#include "GameClub.h"

std::unique_ptr<gameclub::IEventCommand> gameclub::EventId1::execute() {
    auto& gameClub = GameClub::GameClub::getInstance();
    auto tb = gameClub.GetOpeningTime();
    auto te = gameClub.GetClosingTime();
    // если пришел не в часы работы, то генерируется ошибка
    if (time_ < tb || time_ > te) {
        return std::make_unique<EventId13>(time_, kErrorNotOpenYet);
    }
    // если клиент уже в клубе, то генерируется ошибка
    if (gameClub.GetClients().contains(client_)) {
        return std::make_unique<EventId13>(time_, kErrorYouShallNotPass);
    }
    // добавляем в список клиентов, которые внутри клуба
    gameClub.GetClients().insert(client_);
    return nullptr;
}
std::unique_ptr<gameclub::IEventCommand> gameclub::EventId2::execute() {
    auto& gameClub = GameClub::GameClub::getInstance();
    // если клиент не находится в клубе, то генерируется ошибка
    if (!gameClub.GetClients().contains(client_)) {
        return std::make_unique<EventId13>(time_, kErrorClientUnknown);
    }
    // если стол занят, то генерируется ошибка
    if (gameClub.GetTables().contains(table_)) {
        return std::make_unique<EventId13>(time_, kErrorPlaceIsBusy);
    }
    // если клиент пересаживается с какого-либо стола
    if (gameClub.GetClientsOnTables().contains(client_)) {
        gameClub.GetTables().erase(gameClub.GetClientsOnTables()[client_].table);
        gameClub.GetClientsOnTables().erase(client_);
    }

    // клиент садится за стол
    gameClub.GetTables().insert({table_, TimeClient(time_, client_)});
    gameClub.GetClientsOnTables().insert({client_, TimeTableNum(time_, table_)});
    return nullptr;
}

std::unique_ptr<gameclub::IEventCommand> gameclub::EventId3::execute() {
    auto& gameClub = GameClub::GameClub::getInstance();
    // если клиент не находится в клубе, то генерируется ошибка
    if (!gameClub.GetClients().contains(client_)) {
        return std::make_unique<EventId13>(time_, kErrorClientUnknown);
    }
    // если есть свободные столы генерируется ошибка
    if (gameClub.GetTables().size() < gameClub.GetTablesAmount()) {
        return std::make_unique<EventId13>(time_, kErrorICanWaitNoLonger);
    }
    // если клиентов больше чем столов, то клиент уходит
    if (gameClub.GetWaitingList().size() > gameClub.GetTablesAmount()) {
        gameClub.GetClients().erase(client_);
        return std::make_unique<EventId11>(time_, client_);
    }
    // добавляем клиента в лист ожидания
    gameClub.GetWaitingList().push(client_);
    return nullptr;
}

std::unique_ptr<gameclub::IEventCommand> gameclub::EventId4::execute() {
    auto& gameClub = GameClub::GameClub::getInstance();
    // если клиент не находится в клубе, то генерируется ошибка
    if (!gameClub.GetClients().contains(client_)) {
        return std::make_unique<EventId13>(time_, kErrorClientUnknown);
    }
    // когда клиент уходит, стол освобождается

    if (!gameClub.GetClientsOnTables().contains(client_)) return nullptr;

    uint32_t table_number = gameClub.GetClientsOnTables()[client_].table;
    auto from_time = gameClub.GetClientsOnTables()[client_].time;
    gameClub.GetTables().erase(table_number);
    gameClub.GetClientsOnTables().erase(client_);
    gameClub.GetClients().erase(client_);

    // считаем прибыль и занятое время
    auto time_delta = TimeDelta(from_time, time_);
    auto money = gameClub.CalculatePricingForMinutes(time_delta);
    auto& ans = gameClub.GetAnsTables();
    if (ans.empty()) ans.resize(gameClub.GetTablesAmount(), {my_time{0min}, 0});

    auto& el = ans[table_number - 1];
    auto time1 = el.time;
    el.time = TimeSum(time1, time_delta);
    el.money += money;


    // стол занимает первый клиент из списка ожидания
    if (gameClub.GetWaitingList().empty()) return nullptr;
    auto new_client = gameClub.GetWaitingList().front();
    gameClub.GetWaitingList().pop();

    gameClub.GetTables().insert({table_number, TimeClient(time_, new_client)});
    gameClub.GetClientsOnTables().insert({new_client, TimeTableNum(time_, table_number)});

    return std::make_unique<EventId12>(time_, new_client, table_number);
}

std::unique_ptr<gameclub::IEventCommand> gameclub::EventId11::execute() {
    auto& gameClub = GameClub::GameClub::getInstance();
    if (!gameClub.GetClientsOnTables().contains(client_)) return nullptr;

    uint32_t table_number = gameClub.GetClientsOnTables()[client_].table;
    auto from_time = gameClub.GetClientsOnTables()[client_].time;
    gameClub.GetTables().erase(table_number);
    gameClub.GetClientsOnTables().erase(client_);
    gameClub.GetClients().erase(client_);
    // считаем прибыль и занятое время
    auto time_delta = TimeDelta(from_time, time_);
    auto money = gameClub.CalculatePricingForMinutes(time_delta);
    auto& ans = gameClub.GetAnsTables();
    if (ans.empty()) ans.resize(gameClub.GetTablesAmount(), {my_time{0min}, 0});

    auto& el = ans[table_number - 1];
    auto time1 = el.time;
    el.time = TimeSum(time1, time_delta);
    el.money += money;

    return nullptr;
}
std::string gameclub::EventId1::to_string() {
    return TimeToString(time_) + " 1 " + client_;
}

std::string gameclub::EventId2::to_string() {
    return TimeToString(time_) + " 2 " + client_ + " " + std::to_string(table_);
}
std::string gameclub::EventId3::to_string() {
    return TimeToString(time_) + " 3 " + client_;
}

std::string gameclub::EventId4::to_string() {
    return TimeToString(time_) + " 4 " + client_;
}

std::string gameclub::EventId11::to_string() {
    return TimeToString(time_) + " 11 " + client_;
}
std::string gameclub::EventId12::to_string() {
    return TimeToString(time_) + " 12 " + client_ + " " + std::to_string(table_);
}

std::string gameclub::EventId13::to_string() {
    return TimeToString(time_) + " 13 " + error_;
}
gameclub::IEventCommand::IEventCommand(const gameclub::my_time& time) : time_(time) {}
const gameclub::my_time& gameclub::IEventCommand::GetTime() const {
    return time_;
}
