#ifndef window
#define window

#include <string.h>

typedef void (*app_process)();

struct simulacra_window
{
	wchar_t* title;
	int width;
	int height;
	app_process run_application;
};

void simulacra_create_window(struct simulacra_window* win_props, void* data);
void simulacra_update_window();
void simulacra_destroy_window();

#endif
