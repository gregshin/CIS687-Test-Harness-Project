#pragma once

#ifdef TESTFAILURELIBRARY_EXPORTS
#define TESTFAILURELIBRARY_API __declspec(dllexport)
#else
#define TESTFAILURELIBRARY_API __declspec(dllimport)
#endif

extern "C" TESTFAILURELIBRARY_API bool iTest();