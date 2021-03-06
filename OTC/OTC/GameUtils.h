#pragma once

#include "Utils.h"

#define GAME_VIRTUAL_CONSOLE_INDEX 108 * 4

//All legacy functions. Docs: UnknownCheats.

class GameUtils {

protected:

    typedef void* (*CreateInterfaceEngine) (const char* interfaceName, int* code);
    typedef bool (__thiscall* ClientCMD) (const void* caller, const char* command);
    typedef void (*PrintConsoleInterface) (const char* message, ...);

    PrintConsoleInterface PrintInterface = (PrintConsoleInterface) Utils::GetFunction ("tier0.dll", "Msg");
    CreateInterfaceEngine CreateInterface = (CreateInterfaceEngine) Utils::GetFunction ("engine.dll", "CreateInterface");
    PVOID VEngineClient = CreateInterface("VEngineClient014", nullptr);
    ClientCMD ExecuteInterface = (ClientCMD) * reinterpret_cast<int*> (*reinterpret_cast<int*> (VEngineClient) + GAME_VIRTUAL_CONSOLE_INDEX);

public:

    /**
     * Print message to game console with formatting newline.
     *
     * @param message - You msg.
     * @param preNewLineCount - Count of new lines before message.
     * @param postNewLineCount - Count of new lines after message.
     **/

    void PrintToConsole (const char* message, int preNewLineCount = 0, int postNewLineCount = 1);

    /**
     * Simple sending a new line to the console.
     *
     * @param newLineCount - Lines count.
     **/

    void PrintNewLineToConsole (int newLineCount = 1);

    /**
     * Execute command to console. 
     * 
     * !WARNING! 
     * !May raise an exception in the debugger!
     * 
     * @param cmd - Command.
     **/

    void ExecuteAtConsole (const char* cmd);

};