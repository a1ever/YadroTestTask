#pragma once
#include <iostream>
namespace gameclub {

class ProcessGameClub {
 private:
  std::istream& in;
  std::ostream& out;
  void GenerateClosingEvents();
 public:
  explicit ProcessGameClub(std::istream& in, std::ostream& out);
  void Run();
};
}
