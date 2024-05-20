#include "ProcessGameClub.h"
#include "GameClub.h"
#include "Parser.h"

#include <map>

gameclub::ProcessGameClub::ProcessGameClub(std::istream& in, std::ostream& out) : out(out), in(in) {}
void gameclub::ProcessGameClub::Run() {
    Parser parser;
    auto res = parser.Parse(in);
    if (!res.empty()) {
        out << res << "\n";
        return;
    }
    auto& club = gameclub::GameClub::getInstance();
    out << TimeToString(club.GetOpeningTime()) << "\n";
    auto& events = parser.GetEvents();
    while (!events.empty()) {
        auto& cur = events.front();
        out << cur->to_string() << "\n";
        // исполнить действие
        auto el = cur->execute();
        // проверить создались ли выходные команды
        if (el != nullptr) {
            out << el->to_string() << "\n";
        }
        events.pop();
    }
    GenerateClosingEvents();
    out << TimeToString(club.GetClosingTime()) << "\n";
    auto& ans = club.GetAnsTables();
    if (ans.empty()) ans.resize(club.GetTablesAmount(), {my_time{0min}, 0});
    for (int i = 0; i != ans.size(); ++i) {
        out << std::to_string(i + 1) + " " + std::to_string(ans[i].money) + " " + TimeToString(ans[i].time) << "\n";
    }
}
void gameclub::ProcessGameClub::GenerateClosingEvents() {
    auto& club = gameclub::GameClub::getInstance();
    auto& peoples_on_tables_left = club.GetClientsOnTables();
    std::map<std::string, TimeTableNum> tables(peoples_on_tables_left.begin(), peoples_on_tables_left.end());
    for (auto& [name, time_table] : tables) {
        EventId11 ev = EventId11(club.GetClosingTime(), name);
        ev.execute();
        out << ev.to_string() << "\n";
    }
}
