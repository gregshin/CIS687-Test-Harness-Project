#pragma once

#ifdef TESTWAITLIBRARY_EXPORTS
#define TESTWAITLIBRARY_API __declspec(dllexport)
#else
#define TESTWAITLIBRARY_API __declspec(dllimport)
#endif

extern "C" TESTWAITLIBRARY_API bool iTest();