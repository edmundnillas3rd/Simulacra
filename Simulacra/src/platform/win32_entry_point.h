#ifndef win32_entry_point
#define win32_entry_point

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

#include "window.h"
#include "simulacra_win32.h"

void simulacra_create_application(struct simulacra_window* win_props, void* args);
void simulacra_run_application();


int wWinMain(
	HINSTANCE 	hInstance,
	HINSTANCE 	hPrevInstance,
	PWSTR		pCmdLine,
	int		nCmdShow
)
{
	struct simulacra_window win_props = {0};
	struct simulacra_win32_args args = {0};
	args.hInstance = hInstance;
	args.hPrevInstance = hPrevInstance;
	args.pCmdLine = pCmdLine;
	args.nCmdShow = nCmdShow;
	
	simulacra_create_application(&win_props, &args);
	simulacra_run_application(&win_props, &args);
	return 0;
}

#endif
