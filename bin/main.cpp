#include "../lib/GameClub.h"
#include "../lib/TimeParser.h"

#include <iostream>

/*
 *
 *
 *
 *
 *
 *
 *
 * */




int main() {
    try {
        std::string timeStr1 = "10:25";
        std::string timeStr2 = "12:43";
        auto t1 = gameclub::StringToTime(timeStr1);
        auto t2 = gameclub::StringToTime(timeStr2);
        auto td = gameclub::TimeDelta(t2, t1);
        std::cout << gameclub::TimeToString(td);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }

    return 0;
}

/*
int main() {
    std::cout << "Hello, World!" << std::endl;
    gameclub::gameclub& p_game_club = gameclub::gameclub::getInstance();
    gameclub::gameclub& p_game_club2 = gameclub::gameclub::getInstance();
    p_game_club.print();
    p_game_club2.print();
    return 0;
}*/
