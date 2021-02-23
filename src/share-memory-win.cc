#include <napi.h>
#include <node.h>
#include <memory>
#include <iostream>
#include <string>
#include <cstdio>
#include "share-memory-win.h"

using namespace Napi;
using namespace std;

Napi::Value CreateShareMemory(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() < 2)
        return Napi::Boolean::New(env, false);
    if (!info[0].IsString())
        return Napi::Boolean::New(env, false);
    if (!info[1].IsNumber())
        return Napi::Boolean::New(env, false);
    auto name = info[0].As<Napi::String>().Utf8Value();
    auto mapsize = info[1].As<Napi::Number>();

    HANDLE mapping = CreateFileMappingA(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        (int64_t)mapsize, //兼容32位
        name.c_str());

    if (mapping)
    {
        _shareMemoryMap[name] = mapping;
        if (GetLastError() == ERROR_ALREADY_EXISTS)
        {
            printf("CreateShareMemory => %s ERROR_ALREADY_EXISTS", name.c_str());
        }
        return Napi::Boolean::New(env, true);
    }
    return Napi::Boolean::New(env, false);
}

Napi::Value ReadShareMemory(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    if (info.Length() < 2)
        return Napi::Boolean::New(env, false);
    if (!info[0].IsString())
        return Napi::Boolean::New(env, false);
    if (!info[1].IsArrayBuffer())
        return Napi::Boolean::New(env, false);
    auto name = info[0].As<Napi::String>().Utf8Value();
    auto buff = info[1].As<Napi::ArrayBuffer>();
    auto bufflen = buff.ByteLength();
    HANDLE mapping = OpenFileMappingA(FILE_MAP_READ, false, name.c_str());
    if (mapping)
    {
        void *ptr = MapViewOfFile(mapping, FILE_MAP_READ, 0, 0, bufflen);
        if (ptr)
        {
            memcpy(buff.Data(), ptr, bufflen);
            UnmapViewOfFile(ptr);
            CloseHandle(mapping);
            return Napi::Boolean::New(env, true);
        }
        CloseHandle(mapping);
    }
    return Napi::Boolean::New(env, false);
}

Napi::Value WriteShareMemory(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    if (info.Length() < 2)
        return Napi::Boolean::New(env, false);
    if (!info[0].IsString())
        return Napi::Boolean::New(env, false);
    if (!info[1].IsArrayBuffer())
        return Napi::Boolean::New(env, false);
    auto name = info[0].As<Napi::String>().Utf8Value();
    auto buff = info[1].As<Napi::ArrayBuffer>();
    auto bufflen = buff.ByteLength();
    HANDLE mapping = OpenFileMappingA(FILE_MAP_WRITE, false, name.c_str());
    if (mapping)
    {
        void *ptr = MapViewOfFile(mapping, FILE_MAP_WRITE, 0, 0, bufflen);
        if (ptr)
        {
            memcpy(ptr, buff.Data(), bufflen);
            UnmapViewOfFile(ptr);
            CloseHandle(mapping);
            return Napi::Boolean::New(env, true);
        }
        CloseHandle(mapping);
    }
    return Napi::Boolean::New(env, false);
}

Napi::Value DeleteShareMemory(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    if (info.Length() < 1)
        return Napi::Boolean::New(env, false);
    if (!info[0].IsString())
        return Napi::Boolean::New(env, false);
    auto name = info[0].As<Napi::String>().Utf8Value();
    auto it = _shareMemoryMap.find(name);
    if (it != _shareMemoryMap.end())
    {
        CloseHandle(_shareMemoryMap[name]);
        _shareMemoryMap.erase(name);
    }
    return Napi::Boolean::New(env, true);
}