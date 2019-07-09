#include "communication.hpp"
#include "command.hpp"
#include <Arduino.h>
#include <debug.h>
#include "PinChangeInt.h"

namespace Rope
{

bool Communication::wokeFromInterrupt = false;

void Communication::initialize(const uint8_t serialPin)
{
    this->serialPin = serialPin;
    pinMode(this->serialPin, INPUT);     // set the pin to input
    digitalWrite(this->serialPin, HIGH); // use the internal pullup resistor
    
    PCintPort::attachInterrupt(this->serialPin, Communication::interrupt, CHANGE); 
}

void Communication::interrupt()
{
    Communication::wokeFromInterrupt = true;
}

void Communication::registerCommand(char character, Command::Action action)
{
    if(this->installedCommands == MAX_COMMANDS)
    {
        __debug__(Serial.print("Communication: Command limit reached"));
        
        return;
    }
    this->commands[this->installedCommands] = new Command(character,action);
    this->installedCommands++;
}

void Communication::receive()
{
    PCintPort::detachInterrupt(this->serialPin);
    
    if (Communication::wokeFromInterrupt)
    {
        Communication::wokeFromInterrupt = false;
        this->decode();
    }

    PCintPort::attachInterrupt(this->serialPin, Communication::interrupt, CHANGE);
}

void Communication::decode()
{
    Serial.println("waiting for commands... start with cmds:");
    Serial.flush();
    
    Serial.end();           // These two functions when called in sequence make clear
    Serial.begin(38400);    // the Serial buffer, preventing garbage characters

    while(!Serial.available())
    {
    }

    String message = Serial.readString();
    
    if(message.indexOf("cmds:") == -1)
    {
        return;
    }
    
    for(byte i=5; i<message.length(); i++) // 5 because commands starting after string cmds:
    {
        char character = message.charAt(i);
        this->executeCommand(character);
    }
    
}

void Communication::executeCommand(char character)
{
    for (uint8_t i = 0; i < this->installedCommands; i++)
    {
        Command *command = this->commands[i];
        
        if(command->getCharacter() == character)
        {
            command->execute();
            return;
        }
    }
}

}