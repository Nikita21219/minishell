#include "../includes/minishell.h"

// void	error_mes_with_exit(char *err_mes, t_data *data)
// {
// 	printf("%s", err_mes);
// 	free(data->str);
// 	exit(1);
// }

int	is_same_lines(char *f_str, char *s_str)
{
	int	i;

	if (ft_strlen(f_str) != ft_strlen(s_str))
		return (0);
	i = -1;
	while (f_str[++i])
		if (f_str[i] != s_str[i])
			return (0);
	return (1);
}
