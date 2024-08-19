#ifndef simulacra_win32
#define simulacra_win32

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>


struct simulacra_win32_args
{
	HINSTANCE 	hInstance;
	HINSTANCE 	hPrevInstance;
	PWSTR		pCmdLine;
	int		nCmdShow;
};

#endif
