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
}
/* Callback para evento de cambio de resolucion*/
static void onResize(const Event* ev, void *ud) {
	if (ev->type == EVENT_RESIZE) {
		const CliEvent* resizeEv = (const CliEvent*)ev;
		println("Nuevo tamaño: %dx%d\n", resizeEv->volume.w, resizeEv->volume.h);
	}
}

//	Main
int main()
{
	init_utf16_std();
	CLIMenu mainMenu;
	mainMenu.title = "Seleccione una opción";
	mainMenu.opts = {
		{ 1, "Opción 1" },
		{ 2, "Opción 2" },
		{ 3, "Opción 3" }
	};
	mainMenu.coords = {
		.x = 5,
		.y = 2
	};
	CliAddEventListener(onInput, &mainMenu);
	CliAddEventListener(onExit, &mainMenu);
	CliAddEventListener(onResize, NULL);
	CliRunMenu(mainMenu);
	return EXIT_SUCCESS;
}