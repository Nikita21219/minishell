#include "../../includes/minishell.h"

int	wait_process_and_set_next_ptr(t_data *data, char *path)
{
	if (waitpid(data->comm->prnt, &data->comm->status, 0) == -1)
		fprintf(stderr, "Error waitpid\n");
	if (WIFEXITED(data->comm->status))
		errno = WEXITSTATUS(data->comm->status);
	set_next_ptr_data_and_free_path(data, path);
	return (1);
}

int	parenthesis_logic(char *path, int c, t_data *data, t_comm *tmp_dt)
{
	char	*new_instr;

	check_oper(data);
	data->comm->prnt = fork();
	if (data->comm->prnt == 0)
	{
		if (handle_oper(data, c))
			return (1);
		new_instr = ft_strdup(data->comm->comm);
		if (new_instr == NULL)
			return (1);
		freedata(data);
		data->instr = new_instr;
		pars_and_launch(data, 0);
	}
	else if (tmp_dt->fd[1])
	{
		if (close(tmp_dt->fd[1]))
			fprintf(stderr, "Error close\n");
		tmp_dt->fd[1] = 0;
	}
	return (wait_process_and_set_next_ptr(data, path));
}

int	check_parenthesis(char *path, int c, t_data *data, t_comm *tmp_dt)
{
	if (data->comm->status == 1)
		return (parenthesis_logic(path, c, data, tmp_dt));
	return (0);
}
