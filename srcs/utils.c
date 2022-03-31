#include "../includes/minishell.h"

void	error_mes_with_exit(char *err_mes, t_data *data)
{
	printf("%s", err_mes);
	if (data->comm)
		delcommand(&data->comm);
	if (data->env)
		delenv(&data->env);
	if (data->instr)
		free(data->instr);
	exit(1);
}

int	is_same_lines(char *f_str, char *s_str)
{
	int	i;

	if (!f_str || !s_str)
		return (0);
	if (ft_strlen(f_str) != ft_strlen(s_str))
		return (0);
	i = -1;
	while (f_str[++i])
		if (f_str[i] != s_str[i])
			return (0);
	return (1);
}

void	freedata(t_data *data)
{
	delcommand(&data->comm);
	free(data->instr);
}

void	exit_from_minishell(void)
{
	printf("Fail from 'exit_from_minishell'\n");
	exit(1);
	return ;
}

int	get_count_comm(t_comm *data)
{
	int	count;

	count = 0;
	while (data)
	{
		count++;
		data = data->next;
	}
	return (count);
}

// int	create_pipes(int *fd, int count_comm)
// {
// 	int	i;

// 	i = 0;
// 	while (i < count_comm)
// 	{
// 		if (pipe(fd + i) == -1)
// 			return (1);
// 		i += 2;
// 	}
// 	return (0);
// }

int	ft_space(char str)
{
	if (str == ' ' || str == '\f' || str == '\n')
		return (1);
	if (str == '\r' || str == '\t' || str == '\v')
		return (1);
	return (0);
}
