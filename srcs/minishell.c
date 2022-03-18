#include "../includes/minishell.h"

void	parser(t_data *data)
{
	data->args = ft_split(data->str, ' ');
	if (!data->args)
		error_mes_with_exit("mini_hell: error memory allocated\n", data);
}

void	minishell(t_data *data)
{
	char	*str;
	int		i;

	while (1)
	{
		i = 0;
		data->str = readline(READLINE_RED "mini_hell$ " TERM_RESET);
		if (!data->str)
			return ;
		parser(data);
		while (data->args[i])
			printf("%s\n", data->args[i++]);
		add_history(data->str);
		free(data->str);
	}
}

int main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	(void) env;
	t_data	data;

	if (check_argv(argc, argv, env, &data))
		return (1);
	minishell(&data);
	return (0);
}
