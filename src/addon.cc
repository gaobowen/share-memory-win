#include <napi.h>
#include "share-memory-win.h"

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports.Set(Napi::String::New(env, "CreateShareMemory"), Napi::Function::New(env, CreateShareMemory));
    exports.Set(Napi::String::New(env, "ReadShareMemory"), Napi::Function::New(env, ReadShareMemory));
    exports.Set(Napi::String::New(env, "WriteShareMemory"), Napi::Function::New(env, WriteShareMemory));
    exports.Set(Napi::String::New(env, "DeleteShareMemory"), Napi::Function::New(env, DeleteShareMemory));
    return exports;
}

NODE_API_MODULE(electron_share_memory, Init)