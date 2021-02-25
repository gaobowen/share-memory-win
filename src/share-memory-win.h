#ifndef SHARED_MEMORY_WIN_H
#define SHARED_MEMORY_WIN_H

#include <napi.h>
#include <windows.h>
#include <map>

typedef HANDLE HANDLE;

struct CachedData
{
    HANDLE openHandle;
    void* ptr;
};

static std::map<std::string, HANDLE> _shareMemoryMap; 
static std::map<std::string, CachedData> _sharedCachedData;

Napi::Value CreateShareMemory(const Napi::CallbackInfo &info);
Napi::Value ReadShareMemory(const Napi::CallbackInfo &info);
Napi::Value ReadShareMemoryFast(const Napi::CallbackInfo &info);
Napi::Value WriteShareMemory(const Napi::CallbackInfo &info);
Napi::Value WriteShareMemoryFast(const Napi::CallbackInfo &info);
Napi::Value DeleteShareMemory(const Napi::CallbackInfo &info);

#endif