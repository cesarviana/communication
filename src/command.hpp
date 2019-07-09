#ifndef ROPE_COMMUNICATION_COMMAND_HPP
#define ROPE_COMMUNICATION_COMMAND_HPP

namespace Rope
{

class Command
{
public:
  typedef void (*Action)();

private:
  const char character;
  const Action action;

public:
  Command(const char character, const Action action);
  void execute() const;
  char getCharacter() const;
};

} // namespace Rope

#endif // ROPE_COMMUNICATION_COMMAND_HPP