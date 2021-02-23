#ifndef SHARED_MEMORY_WIN_H
#define SHARED_MEMORY_WIN_H

#include <napi.h>
#include <windows.h>
#include <map>

typedef HANDLE HANDLE;

static std::map<std::string, HANDLE> _shareMemoryMap; 

Napi::Value CreateShareMemory(const Napi::CallbackInfo &info);
Napi::Value ReadShareMemory(const Napi::CallbackInfo &info);
Napi::Value WriteShareMemory(const Napi::CallbackInfo &info);
Napi::Value DeleteShareMemory(const Napi::CallbackInfo &info);

#endif