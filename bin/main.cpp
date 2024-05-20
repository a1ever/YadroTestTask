#include "../lib/ProcessGameClub.h"

#include <fstream>


int main(int argc, char** argv) {
    if (argc != 2){
        return 1;
    }
    std::string test_filename = argv[1];
    std::ifstream fin(test_filename);
    auto process = gameclub::ProcessGameClub (fin, std::cout);
    process.Run();
    return 0;
}

