#pragma once
#include "cli_stdio.h"
#include <vector>

#pragma region  Screen definitions
typedef struct	Coordinates {
	SHORT x;
	SHORT y;
} Coordinates;
typedef struct	ScreenVolume {
	SHORT w;
	SHORT h;
} ScreenVolume;
#pragma endregion

#pragma region  Event definitions
typedef	enum {
	EVENT_INPUT,
	EVENT_EXIT,
	EVENT_RESIZE,
}EventType;
typedef struct {
	EventType		type;
} Event;
typedef struct {
	Event			base;
	ScreenVolume	volume;
} CliEvent;
typedef struct {
	CliEvent		base;
	char			key;
} CliInputEvent;
typedef void	(*Callback)(const Event* ev, void* userData);
typedef struct	EventListener {
	Callback				callback;
	void* userData;
	struct EventListener* next;
} EventListener;
#pragma endregion

#pragma region  CLIdefinitions
typedef struct	Option {
	char key;
	char* desc;
} Option;
typedef struct ExitConfig {
	const char* desc = "Salir del programa";
	int*		exitKeys;
	size_t		size;
	BOOL		stop;
} ExitConfig;
typedef struct	Menu {
	char* title;
	std::vector<Option> opts;
} Menu;
typedef struct	CLIMenu : Menu {
	Coordinates coords{};
	ScreenVolume volume{};
	const ExitConfig exitConfig = {
		.exitKeys = new int[4] {3, 26, 27, 'q'},
		.size = sizeof(int[4]) / sizeof(int),
		.stop = FALSE
	};
} CLIMenu;
#pragma endregion

#pragma region  CLI Events
void			CliAddEventListener(Callback cb, void* userData);
DWORD WINAPI	CliListenerThreadProc(LPVOID lpParam);
BOOL			CliStartListener(const CLIMenu* menu);
void			CliStopListener(void);
#pragma endregion
#pragma region  CLI Screen
void			CliClearRegion(const Coordinates& coords, const ScreenVolume& volume);
void			CliGotoXY(const Coordinates& coords);
void			CliPrintMenu(const CLIMenu& menu);
#pragma endregion
#pragma region  CLI Helpers
ScreenVolume	CliGetVolume();
HANDLE			CliGetHandle(DWORD nStdHandle);
//void			CliOnResize(function<void(int, int)> event);
#pragma endregion
#pragma region  CLI
void			CliRunMenu(CLIMenu& menu);
void			CliUpdateMessage(const char* message, const Coordinates& coords);
#pragma endregion