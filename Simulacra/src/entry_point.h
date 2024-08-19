#ifndef entry_point
#define entry_point

#include <windows.h>

#include "application.h"

int WINAPI wWinMain(
		HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		PWSTR	  pCmdLine,
		int	  nCmdShow
)
{
	struct win32_app_args args = {0};
	args.hInstance = hInstance;
	args.hPrevInstance = hPrevInstance;
	args.pCmdLine = pCmdLine;
	args.nCmdShow = nCmdShow;
	run_application(&args);	

	return 0;
}

#endif

