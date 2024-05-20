#pragma once
#include "TimeParser.h"

#include <ctime>
#include <string>
#include <memory>

namespace gameclub {
class IEventCommand {
 protected:
  my_time time_;
 public:
  explicit IEventCommand(const my_time& time);
  IEventCommand& operator=(const IEventCommand&) = delete;
  const my_time& GetTime() const;
  virtual std::unique_ptr<IEventCommand> execute() = 0;
  virtual std::string to_string() = 0;
  virtual ~IEventCommand() = default;
};

class EventId1 : public IEventCommand {
 private:
  std::string client_;
 public:
  explicit EventId1(const my_time& time, const std::string& client) : IEventCommand(time), client_(client) {}
  std::unique_ptr<IEventCommand> execute() override;
  std::string to_string() override;
};

class EventId2 : public IEventCommand {
 private:
  std::string client_;
  uint32_t table_;
 public:
  explicit EventId2(const my_time& time, const std::string& client, uint32_t table)
      : IEventCommand(time), client_(client), table_(table) {}
  std::unique_ptr<IEventCommand> execute() override;
  std::string to_string() override;
};

class EventId3 : public IEventCommand {
 private:
  std::string client_;
 public:
  explicit EventId3(const my_time& time, const std::string& client) : IEventCommand(time), client_(client) {}
  std::unique_ptr<IEventCommand> execute() override;
  std::string to_string() override;
};

class EventId4 : public IEventCommand {
 private:
  std::string client_;
 public:
  explicit EventId4(const my_time& time, const std::string& client) : IEventCommand(time), client_(client) {}
  std::unique_ptr<IEventCommand> execute() override;

  std::string to_string() override;
};

class EventId11 : public IEventCommand {
 private:
  std::string client_;
 public:
  explicit EventId11(const my_time& time, const std::string& client) : IEventCommand(time), client_(client) {}
  std::unique_ptr<IEventCommand> execute();

  std::string to_string() override;
};

class EventId12 : public IEventCommand {
 private:
  std::string client_;
  uint32_t table_;
 public:
  explicit EventId12(const my_time& time, const std::string& client, uint32_t table)
      : IEventCommand(time), client_(client), table_(table) {}
  std::unique_ptr<IEventCommand> execute() override {
      return nullptr;
  }

  std::string to_string() override;
};

class EventId13 : public IEventCommand {
 private:
  std::string error_;
 public:
  explicit EventId13(const my_time& time, const std::string& error) : IEventCommand(time), error_(error) {}
  std::unique_ptr<IEventCommand> execute() {
      return nullptr;
  }

  std::string to_string() override;
};
}

