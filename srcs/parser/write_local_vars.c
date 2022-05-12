#include "../../includes/minishell.h"

int	check_for_var(char **trm, char **str)
{
	int	a;

	a = 0;
	while (trm[a] && (trm[a][0] != '<' || trm[a][0] != '>' \
		|| trm[a][0] != '&' || trm[a][0] != '|'))
	{
		if (!ft_strchr(trm[a], '=') || check_right_var(trm[a]))
		{
			a = 0;
			break ;
		}
		while (**str && !ft_space(**str) && (**str != '<' || **str != '>' \
		|| **str != '&' || **str != '|'))
			(*str)++;
		while (**str && ft_space(**str))
			(*str)++;
		a++;
	}
	return (a);
}

int	check_for_local_vars(char **str, t_data *data)
{
	int		a;
	char	**trm;

	while (**str && ft_space(**str))
		(*str)++;
	if (data->comm || !(**str))
		return (0);
	trm = ft_split(*str, ' ');
	if (!trm)
	{
		printf("Error malloc in parse\n");
		errno = 12;
		return (1);
	}
	a = check_for_var(trm, str);
	while (a > 0)
	{
		if (add_list_env(&data->vars, trm[--a]))
		{
			errno = 12;
			return (1);
		}
	}
	free_arrs(trm);
	return (0);
}
