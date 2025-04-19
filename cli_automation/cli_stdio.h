#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#pragma region Print Functionality
#if defined(_WIN32) || defined(_WIN64)
	#pragma region	Includes
	#include <windows.h>
	#include <io.h>
	#include <fcntl.h>
	#include <tchar.h>
	#include <stdarg.h>
	#include <string>
	#pragma endregion
	#pragma region Global Methods
	#define init_utf16_std() ((void)0)
	static void print_f(FILE* stream, const TCHAR* fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		_vftprintf(stream, fmt, args);
		va_end(args);
	}
	#pragma endregion
	#pragma region Global Macros
	#define printlnerr(fmt, ...) ((void)0)
	#define print(fmt, ...)							\
			print_f(stdout, _T(fmt), ##__VA_ARGS__##)
	#define println(fmt, ...)						\
			print_f(stdout, _T(fmt) _T("\n"), ##__VA_ARGS__##)
	#pragma endregion
	#if defined(_UNICODE) || defined(UNICODE)
		#undef init_utf16_std  
		#pragma region Methods
		static void init_utf16_std(void) 
		{
			if (_setmode(_fileno(stdout), _O_U16TEXT) == -1) {
				_ftprintf(stdout, _T("Error: no se pudo cambiar stdout a UTF‑16\n"));
				exit(EXIT_FAILURE);
			}
			if (_setmode(_fileno(stderr), _O_U16TEXT) == -1) {
				_ftprintf(stderr, _T("Error: no se pudo cambiar stderr a UTF‑16\n"));
				exit(EXIT_FAILURE);
			}
		}
		#pragma endregion
		#if defined(DEBUG)
			#define printlnerr(fmt, ...)									\
				print_f(stderr, _T("Error: " fmt _T("\n")), ##__VA_ARGS__##)
		#endif
	#endif
#endif
#pragma endregion