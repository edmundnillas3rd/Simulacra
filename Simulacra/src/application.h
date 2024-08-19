#ifndef application
#define application

#include <string.h>

#ifdef _WIN32
#include "platform/simulacra_win32.h"
#define ARGS(x) (struct win32_app_args*)(x)
#define ARGS_TYPE struct win32_app_args
#endif

typedef void (*app_process)();

struct application_props
{
	wchar_t* title;
	int width;
	int height;
};

struct application_specs
{
	app_process run_application;
	struct application_props props;
};

void create_application(struct application_specs* specs);
void run_application(ARGS_TYPE* args);

#endif
