#pragma once
//#include "MStack/MStackS.h"

//#include "../kernelStuff/stuff/stackmacro.h"
//#include "../kernelStuff/stuff/kernelUtil.h"
//#include "../customClasses/list.h"


//#include "../WindowStuff/WindowManager/windowManager.h"

//#include "../WindowStuff/Window/window.h"
//#include "../kernelStuff/Disk_Stuff/Disk_Interfaces/generic/genericDiskInterface.h"

//#define LIST_INCLUDE_GENERIC_DISK_INTERFACE
//#define LIST_INCLUDE_TASK
//#define LIST_INCLUDE_WINDOW
//#include "../customClasses/list.h"
//#undef LIST_INCLUDE_WINDOW
//#undef LIST_INCLUDE_TASK
//#undef LIST_INCLUDE_GENERIC_DISK_INTERFACE

#include "window.h"

struct OSData
{
    bool exit;
    bool booting;
    //KernelInfo* kernelInfo;
    //List<Window*> windows;
    //List<Task*> osTasks;
    //kernelFiles::ZIPFile* windowButtonZIP;
    //kernelFiles::ZIPFile* windowIconZIP;
    //Window* realMainWindow;
    //Window* realMainWindow2;
    Window* mainTerminalWindow;
    Window* debugTerminalWindow;
    bool showDebugterminal;
    // MStack stackArr[1000];
    // int64_t stackPointer = 0;
    bool drawBackground;
    bool enableStackTrace;
    int64_t crashCount = 0;
    int maxNonFatalCrashCount = 0;
    bool crashed = false;
    bool tempCrash = false;
    //WindowManager::WindowPointerBufferThing* windowPointerThing;

    //List<DiskInterface::GenericDiskInterface*> diskInterfaces;

};



extern OSData osData;