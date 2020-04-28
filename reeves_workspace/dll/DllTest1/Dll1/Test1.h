#pragma once

#ifdef Dll1_EXPORTS 
#define Dll1_Export __declspec(dllexport)
#else
#define Dll1_Import __declspec(dllimport)
#endif


extern "C" Dll1_Import bool Itest();


