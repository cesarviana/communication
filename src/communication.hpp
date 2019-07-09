#ifndef ROPE_COMMUNICATION_COMMUNICATION_HPP
#define ROPE_COMMUNICATION_COMMUNICATION_HPP

#include <stdint.h>
#include "command.hpp"

namespace Rope
{

class Communication
{

public:
    static bool wokeFromInterrupt;

private:
    static constexpr uint8_t MAX_COMMANDS = 8;

    Command *commands[MAX_COMMANDS];
    uint8_t installedCommands = 0;
    
    uint8_t serialPin;

    void decode();
    void executeCommand(char character);

public:
    void registerCommand(char character, Command::Action action);
    void initialize(const uint8_t serialPin);
    void receive();
    // Static because this function is registered for interrupt
    static void interrupt();

};
};

#endif // ROPE_COMMUNICATION_COMMUNICATION_HPP