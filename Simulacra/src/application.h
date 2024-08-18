#ifndef application
#define application

typedef void (*app_process)();

struct application_props
{
	char title[1024];
	int width;
	int height;
};

struct application_specs
{
	app_process run_application;
	struct application_props props;
};

void create_application(struct application_specs* specs);

#endif
