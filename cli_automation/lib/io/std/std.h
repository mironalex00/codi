#pragma once 
// Project
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <errno.h>

#include "cli_api.h" 

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