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
	ExitConfig* exitCfg = (ExitConfig*)lpParam;
	while (!exitCfg->stop) {
		if (_kbhit()) {
			int c = _getch();
			char ch = (char)tolower(c);
			BOOL isExitKey = FALSE;
			for (size_t i = 0; i < exitCfg->size; ++i) {
				if (c == exitCfg->exitKeys[i] || ch == exitCfg->exitKeys[i]) {
					isExitKey = TRUE;
					break;
				}
			}
			if (isExitKey) {
				CliInputEvent ev = {
					.base = {
						.base = {
							.type = EVENT_EXIT
						},
					},
					.key = ch
				};
				for (EventListener* e = g_listeners; e; e = e->next) {
					e->callback((const Event*)&ev, e->userData);
				}
				exitCfg->stop = TRUE;
				break;
			}
			else {
				CliInputEvent ev = {
					.base = {
						.base = {
							.type = EVENT_INPUT
						},
					},
					.key = ch
				};
				for (EventListener* e = g_listeners; e; e = e->next) {
					e->callback((const Event*)&ev, e->userData);
				}
			}
		}
		Sleep(10);
	}
	return 0;
}
BOOL CliStartListener(const CLIMenu* menu) {
	if (!menu || g_hListenerThread != NULL) return FALSE;
	g_hListenerThread = CreateThread(
		NULL, 0,
		CliListenerThreadProc,
		(LPVOID)&menu->exitConfig, 
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
void CliRunMenu(CLIMenu& menu)
{
	if (!CliStartListener(&menu)) {
		printlnerr("No se pudo iniciar ningun evento");
		exit(EXIT_FAILURE);
	}
	println("Presiona una tecla...");
	while (!menu.exitConfig.stop) {
		Sleep(100);
	}
	CliStopListener();
}