#pragma once

#include <stdint.h>
#include <stddef.h>

#include <malloc.h>

//void* malloc(size_t size);
//void free(void* address);

void* _malloc(size_t size);
void _free(void* address);

void* malloc(size_t size, const char* text);
void* _malloc(size_t size, const char* text);


inline void* operator new(size_t size) { return malloc(size); }
inline void* operator new[](size_t size) {return malloc(size); }
inline void operator delete(void* p) { free(p); }