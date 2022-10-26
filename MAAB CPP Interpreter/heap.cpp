#include "heap.h"
//#include <malloc.h>

namespace temp
{
    //void* tMalloc(size_t size)
    //{
    //    return malloc(size);
    //}
    //void tFree(void* addr)
    //{
    //    free(addr);
    //}

};

//
//void* malloc(size_t size)
//{
//    //AddToStack();
//    void* res = temp::malloc(size);
//    //RemoveFromStack();
//    return res;
//}
//
//void free(void* address)
//{
//    //AddToStack();
//    temp::free(address);
//    //RemoveFromStack();
//}

void* malloc(size_t size, const char* text)
{
    //AddToStack();
    void* res = malloc(size);
    //RemoveFromStack();
    return res;
}


void* _malloc(size_t size)
{
    //AddToStack();
    void* res = malloc(size);
    //RemoveFromStack();
    return res;
}

void _free(void* address)
{
    //AddToStack();
    free(address);
    //RemoveFromStack();
}

void* _malloc(size_t size, const char* text)
{
    //AddToStack();
    void* res = malloc(size);
    //RemoveFromStack();
    return res;
}
