#include "maabTask.h"
//#include "../../kernelStuff/other_IO/pit/pit.h"
#include "heap.h"
//#include "../../interrupts/interrupts.h"
#include "cstrTools.h"
//#include "../../OSDATA/MStack/MStackM.h"
#include "terminalInstance.h"


TaskMAAB::TaskMAAB(uint32_t codeLen, uint8_t* code, Window* window)
{
    this->window = window;

    this->code = (uint8_t*)malloc(codeLen);
    for (int i = 0; i < codeLen; i++)
        this->code[i] = code[i];
    this->codeLen = codeLen;


    memLen = 2000000;
    this->mem = (uint8_t*)malloc(memLen);
    for (int i = 0; i < memLen; i++)
        mem[i] = 0;

    for (int i = 0; i < codeLen; i++)
        mem[i] = code[i];
    
    waitInput = false;
    done = false;
    type = TaskType::BF;


    ((TerminalInstance*)window->instance)->userlen = 0;
    ((TerminalInstance*)window->instance)->takeInput = false;
    waitInput = false;
}

void TaskMAAB::Do()
{
    


}

void TaskMAAB::Free()
{
    free((void*)code);
    free((void*)mem);
}