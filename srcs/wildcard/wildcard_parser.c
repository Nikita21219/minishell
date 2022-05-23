#include "../../includes/minishell.h"

int	check_wildcard_command(t_comm *tmp, int *pos, char **wild)
{
	if (tmp->comm && ft_strchr(tmp->comm, -42))
	{
		if (take_pos_for_wild(&tmp->comm, &pos))
			return (1);
		wild = wildcard(tmp->comm, pos);
		free (pos);
		if (!wild)
			return (1);
		tmp->comm = wild[0];
		if (tmp->prev && (tmp->prev->oper[0] == '<' \
		|| tmp->prev->oper[0] == '>') && len(wild) > 1)
		{
			if (write_arg_wild(&tmp->args, wild + 1, 1))
			{
				free(wild);
				return (1);
			}
			free(wild);
			return (0);
		}
		else
			free(wild);
	}
	return (0);
}

int	check_wildcard_arguments(t_comm *tmp, int *pos, char **wild)
{
	int		a;

	a = -1;
	while (tmp->args[++a])
	{
		pos = NULL;
		if (ft_strchr(tmp->args[a], -42))
		{
			if (take_pos_for_wild(&tmp->args[a], &pos))
				return (1);
			wild = wildcard(tmp->args[a], pos);
			free (pos);
			if (!wild)
				return (1);
			if (write_arg_wild(&tmp->args, wild, a))
			{
				free(wild);
				return (1);
			}
			free(wild);
		}
	}
	return (0);
}

int	check_wildcard(t_comm *tmp)
{
	char	**wild;
	int		*pos;

	if (tmp->prev && is_same_lines(tmp->prev->oper, "<<"))
		return (0);
	pos = NULL;
	wild = NULL;
	if (!check_wildcard_command(tmp, pos, wild))
		if (!check_wildcard_arguments(tmp, pos, wild))
			return (0);
	return (1);
}
