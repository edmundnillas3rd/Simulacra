#include <stdio.h>
#include <string.h>

#include <Simulacra.h>

void Sandbox() 
{
	printf("Hello World, this was called in the Simulacra.exe itself not the library\n");
}

void create_application(struct application_specs* specs)
{
	strcpy(specs->props.title, "Simulacra\0");
	specs->props.width = 1280;
	specs->props.height = 768;
	specs->run_application = &Sandbox;
}
