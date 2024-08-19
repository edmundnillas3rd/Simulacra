#ifndef simulacra_win32
#define simulacra_win32

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

struct win32_app_args
{
	HINSTANCE hInstance;
	HINSTANCE hPrevInstance;
	PWSTR	  pCmdLine;
	int	  nCmdShow;
};

void start_window(struct win32_app_args* args, const wchar_t* title, int width, int height);
void update_window();

#endif
