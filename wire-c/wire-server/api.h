#ifndef __API_H__
#define __API_H__

struct wire_context;

int api_match_name(struct wire_context *context, char* name);
int invoke_by_id(int id, struct wire_context *context);

typedef int (*api_function) (void *userData);

typedef struct function_table
{
	char api_name[1024];
	api_function api;
} APITable;

int start_wire_server(void *data);
int run_scenario(void *data);
int respond_to_scenario(void *data);
int param_scenario_run(void *data);
int scenario_as_variable(void *data);

#endif
