#include "application.h"

struct application_state
{
	int running;
	ARGS_TYPE* args;
	struct application_specs specs;
};

static struct application_state state;

void start_application()
{
	struct application_specs specs;

	create_application(&specs);

	state.specs = specs;

	start_window(ARGS(state.args), specs.props.title, specs.props.width, specs.props.height);

	state.running = 1;
}

void run_application(ARGS_TYPE* args)
{
	state.args = args;
	start_application();

	state.specs.run_application();
	update_window();

	state.running = 0;
}
