#pragma once
#include "task.h"
#include "window.h"
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
    int cyclesPerCall = 100;

public:
    TaskMAAB(uint32_t codeLen, uint8_t* code, Window* window);
    void Do();
    void Free();

};

//TaskBF* NewBFTask(const char* code, Window* window);