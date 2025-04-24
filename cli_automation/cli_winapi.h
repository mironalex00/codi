#pragma once
#include "lib/utils.h"
#pragma region OS Check
#if defined(_WIN32) || defined(_WIN64)
	#pragma region	Includes
	#pragma once
	#include <windows.h>
	#include <io.h>
	#include <fcntl.h>
	#pragma endregion
	#define WIN_OS
#endif
#pragma endregion