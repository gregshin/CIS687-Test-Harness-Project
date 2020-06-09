#pragma once

#ifdef TESTEXCEPTIONLIBRARY_EXPORTS
#define TESTEXCEPTIONLIBRARY_API __declspec(dllexport)
#else
#define TESTEXCEPTIONLIBRARY_API __declspec(dllimport)
#endif

extern "C" TESTEXCEPTIONLIBRARY_API bool iTest();