#pragma once
#include "cli_automation.h"

//	Main
int main()
{
	System.err.println("¡Holá, esto es un error!");
	System.out.println("¡Holá, esto es un output!");
	File *f = get_file_contents("C:\\Users\\Usuario\\Source\\Repos\\codi\\cli_automation\\CMakeLists.txt");
	System.out.println("El archivo %s, contiene %d lineas", f->name, f->size);
	return EXIT_SUCCESS;
}