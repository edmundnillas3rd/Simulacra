#include <stdio.h>
#include <string.h>

#include <Simulacra.h>

void Sandbox() 
{
	printf("Hello World, this was called in the Simulacra.exe itself not the library\n");
}

void simulacra_create_application(struct simulacra_window* win_props, void* args)
{
	win_props->title = L"Simulacra";
	win_props->width = 1280;
	win_props->height = 768;
	win_props->run_application = &Sandbox;
}
