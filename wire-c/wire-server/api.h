#ifndef __API_H__
#define __API_H__

struct wire_context;

typedef int (*api_function) (struct wire_context *context);

typedef struct function_table
{
	char api_name[1024];
	api_function api;
} APITable;

int start_wire_server(struct wire_context *context);
int run_scenario(struct wire_context *context);
int respond_to_scenario(struct wire_context *context);
int param_scenario_run(struct wire_context *context);
int scenario_as_variable(struct wire_context *context);

#endif
