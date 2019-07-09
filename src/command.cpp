#include "command.hpp"

namespace Rope
{

Command::Command(const char character, const Action action) : character(character), action(action)
{
}

void Command::execute() const
{
    this->action();
}

char Command::getCharacter() const
{
    return this->character;
}

} // namespace Rope