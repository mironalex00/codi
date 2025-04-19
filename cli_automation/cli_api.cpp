#pragma once
#include "cli_api.h"
#include <atomic>
#include <iostream>
#include <thread>
#include <conio.h>

using namespace std;

// Puntero global a la lista de listeners.
static EventListener*			g_listeners = NULL;
static HANDLE					g_hListenerThread = NULL;

static DWORD WINAPI CliListenerThreadProc(LPVOID lpParam) {  
   CLIMenu* menu = (CLIMenu*)lpParam;  
   HANDLE hConsole = CliGetHandle(STD_INPUT_HANDLE);  
   SetConsoleMode(hConsole, ENABLE_WINDOW_INPUT | ENABLE_PROCESSED_INPUT);  
   INPUT_RECORD inputRecord = {}; 
   DWORD numEvents = 0;
   while (!menu->exitConfig.stop)
   {
	   WaitForSingleObject(hConsole, INFINITE);
	   ReadConsoleInput(hConsole, &inputRecord, 1, &numEvents);
	   if (inputRecord.EventType == KEY_EVENT)
	   {
		   KEY_EVENT_RECORD keyEvent = inputRecord.Event.KeyEvent;
		   if (keyEvent.bKeyDown) {
			   char ch = (char)tolower(keyEvent.uChar.AsciiChar);
			   int c = keyEvent.wVirtualKeyCode;
			   CliInputEvent ev = {
					.base = {.base = {.type = EVENT_INPUT }, },
					.key = ch
			   };
			   for (EventListener* e = g_listeners; e; e = e->next) {
				   e->callback((const Event*)&ev, e->userData);
			   }
			   // Is Exit?
			   for (size_t i = 0; i < menu->exitConfig.size; ++i) {
				   if (c == menu->exitConfig.exitKeys[i] || ch == menu->exitConfig.exitKeys[i]) {
					   ev.base.base.type = EVENT_EXIT;
					   for (EventListener* e = g_listeners; e; e = e->next) {
						   e->callback((const Event*)&ev, e->userData);
					   }
					   ((ExitConfig*)&menu->exitConfig)->stop = TRUE;
					   exit(EXIT_SUCCESS);
					   break;
				   }
			   }
		   }
	   }
	   if (inputRecord.EventType == WINDOW_BUFFER_SIZE_EVENT)
	   {
		   menu->volume = CliGetVolume();
		   CliEvent resizeEv = {
				.base = {.type = EVENT_RESIZE },
				.volume = menu->volume
		   };
		   for (EventListener* e = g_listeners; e; e = e->next) {
			   e->callback((const Event*)&resizeEv, e->userData);
		   }
	   }
   }

   return 0;  
}
BOOL CliStartListener(const CLIMenu* menu) {
	if (!menu || g_hListenerThread != NULL) return FALSE;
	g_hListenerThread = CreateThread(
		NULL, 0,
		CliListenerThreadProc,
		(LPVOID)menu, 
		0, NULL
	);
	return g_hListenerThread != NULL;
}
void CliStopListener(void) 
{
	if (g_hListenerThread) {
		WaitForSingleObject(g_hListenerThread, INFINITE);
		CloseHandle(g_hListenerThread);
		g_hListenerThread = NULL;
	}
}
void CliAddEventListener(Callback cb, void* userData)
{
	EventListener* e = (EventListener*)malloc(sizeof * e);
	if (!e) return;
	e->callback = cb;
	e->userData = userData;
	e->next = g_listeners;
	g_listeners = e;
}

//	CLI 
HANDLE CliGetHandle(DWORD nStdHandle)
{
	HANDLE cliHandle = GetStdHandle(nStdHandle);
	if (cliHandle == INVALID_HANDLE_VALUE)
	{
		return INVALID_HANDLE_VALUE;
	}
	return cliHandle;
}
ScreenVolume CliGetVolume()
{
	ScreenVolume vol{};
	HANDLE hCli = CliGetHandle(STD_OUTPUT_HANDLE); // STD_OUTPUT_HANDLE
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(hCli, &csbi)) {
		printlnerr("No se pudo determinar las dimensiones del CLI");
		return vol;
	}
	vol.w = static_cast<SHORT>(csbi.srWindow.Right - csbi.srWindow.Left + 1);
	vol.h = static_cast<SHORT>(csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
	return vol;
}
//	
void CliPrintMenu(CLIMenu* menu)
{
	// Todo: implement print menu
}
void CliRunMenu(CLIMenu& menu)
{
	if (!CliStartListener(&menu)) {
		printlnerr("No se pudo iniciar ningun evento");
		exit(EXIT_FAILURE);
	}
	CliPrintMenu(&menu);
	while (!menu.exitConfig.stop) {
		Sleep(100);
	}
	CliStopListener();
}