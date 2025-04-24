#pragma once  
#include "cli_winapi.h" 

#pragma region Struct Def  
typedef struct PrintStream {
    void (*printf) (const char* fmt, ...);
    void (*println)(const char* fmt, ...);
} PrintStream;  

typedef struct {  
   const PrintStream out;  
   const PrintStream err;  
} SystemType;  
#pragma endregion  
extern const SystemType System;