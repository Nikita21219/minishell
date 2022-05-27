#include "../includes/minishell.h"

void	tmp_print_arg_after_parser(t_comm *data)
{
	int j;

	int i = 0;
	int cout_comm = get_count_comm(data);
	while (i < cout_comm)
	{
		j = -1;
		printf("command: %s\n", data->comm);
		while (data->args[++j])
			printf("data args %d: %s\n", j, data->args[j]);
		printf("data args %d: %s\n", j, data->args[j]);
		printf("oper: %s\n", data->oper);
		printf("i: %d\n", data->i);
		printf("\n\n");
		i++;
		data = data->next;
	}
} //FIXME delete this func

void    tmp_print_env(t_envr *env)
{
	t_envr  *envr;
	envr = env;
	while (envr)
	{
		printf("%s=%s\n", envr->key, envr->val);
        envr = envr->next;
	}
} //FIXME delete this func

void	print_containers(t_box *box)
{
	int	i;

	i = 0;
	while (box)
	{
		printf("CONTAINER NUMBER %d\n", ++i);
		while (box->dt_comm)
		{
			printf("command = %s %s; next = %p\n", box->dt_comm->comm, box->dt_comm->args[1], box->dt_comm->next);
			box->dt_comm = box->dt_comm->next;
		}
		printf("oper box = %s\n", box->oper);
		printf("\n\n");
		box = box->next;
	}
}
