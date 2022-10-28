#pragma once
#include "task.h"
#include "window.h"
#include "TerminalInstance.h"
#include "newTerminalInstance.h"
#include <stdint.h>

class TaskMAAB : public Task
{
private:
    uint8_t* code;
    uint32_t codeLen;

    uint8_t* mem;
    uint64_t memLen;

    bool waitInput;
    Window* window;
    NewTerminalInstance* newTerm;
    TerminalInstance* dTerm;
    int cyclesPerCall = 100;

    uint64_t instrPointer = 0;
    uint32_t defCol = Colors.white;



public:

    const char* errMsg = "<NO ERRORS>";
    int errCode = 0;

    TaskMAAB(uint32_t codeLen, uint8_t* code, Window* window, TerminalInstance* newTerm);
    void Do();
    void Free();

};

//TaskBF* NewBFTask(const char* code, Window* window);