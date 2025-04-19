#pragma once
#include "cli_automation.h"
#include "cli_api.h"
#include <windows.h>

/* Callback para teclas normales */
static void onInput(const Event* ev, void* ud) {
	if (ev->type != EVENT_INPUT) return;
	const CliInputEvent* cli_inp_ev = (const CliInputEvent*)ev;
	println("Has pulsado: %c (%d)", cli_inp_ev->key, (int)cli_inp_ev->key);
}
/* Callback para evento de salida */
static void onExit(const Event* ev, void* ud) {
	if (ev->type != EVENT_EXIT) return;
	println("¡Ok!. Limpiando y cerrando...");
	exit(EXIT_SUCCESS);
}

//	Main
int main()
{
	init_utf16_std();
	Coordinates coords{};
	ScreenVolume volume = CliGetVolume();
	CLIMenu mainMenu;
	coords.x = 5;
	coords.y = 2;
	mainMenu.coords = coords;
	mainMenu.volume = volume;
	CliAddEventListener(onInput, &mainMenu);
	CliAddEventListener(onExit, &mainMenu);
	CliRunMenu(mainMenu);
	return EXIT_SUCCESS;
}