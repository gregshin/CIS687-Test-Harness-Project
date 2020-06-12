#pragma once

#ifdef TESTSUCCESSLIBRARY_EXPORTS
#define TESTSUCCESSLIBRARY_API __declspec(dllexport)
#else
#define TESTSUCCESSLIBRARY_API __declspec(dllimport)
#endif

extern "C" TESTSUCCESSLIBRARY_API bool iTest();