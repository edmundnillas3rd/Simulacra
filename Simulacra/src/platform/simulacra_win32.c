#include "simulacra_win32.h"


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void start_window(struct win32_app_args* args, const wchar_t* title, int width, int height)
{
	const wchar_t CLASS_NAME[] = L"SimulacraWindow";

	WNDCLASS wc = {0};

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = args->hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	HWND hwnd = CreateWindowEx(
		0,
		CLASS_NAME,
		title,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, width, height,
		NULL,
		NULL,
		args->hInstance,
		NULL
	);

	if (hwnd == NULL) // If window is not created sucessfully
		return;

	ShowWindow(hwnd, args->nCmdShow);
	
}

void update_window()
{
	MSG msg = {0};
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		{
			if (MessageBox(hwnd, L"Really Quit?", L"Simulacra", MB_OKCANCEL) == IDOK)
			{
				DestroyWindow(hwnd);
			}
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

			EndPaint(hwnd, &ps);
		}
		return 0;
	};

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

