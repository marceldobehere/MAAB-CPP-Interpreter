#include "defaultInstance.h"
#include "terminalInstance.h"
#include "newTerminalInstance.h"

//#include "../connect4Instance/connect4Instance.h"
//#include "../../../memory/heap.h"
//#include <malloc.h>
#include "heap.h"


void DefaultInstance::DefaultFree()
{
    switch (this->instanceType)
    {
    case InstanceType::Default:
    {
        free(this);
        break;
    }
    case InstanceType::DebugTerminal:
    {
        free(this);
        break;
    }
    case InstanceType::Terminal:
    {
        ((TerminalInstance*)this)->Free();
        free(this);
        break;
    }
    case InstanceType::NewTerminal:
    {
        ((NewTerminalInstance*)this)->Free();
        free(this);
        break;
    }
    //case InstanceType::Connect4:
    //{
    //    ((Connect4Instance*)this)->Free();
    //    free(this);
    //    break;
    //}
    default:
    {
        free(this);
        break;
    }
    }
}