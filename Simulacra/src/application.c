#include "window.h"

#ifdef _WIN32
#include "platform/simulacra_win32.h"
#endif

void simulacra_start_application(struct simulacra_window* win_props, void* data)
{
	simulacra_create_window(win_props, data);
}

void simulacra_run_application(struct simulacra_window* win_props, void* data)
{
	simulacra_start_application(win_props, data);
	simulacra_update_window();
}
