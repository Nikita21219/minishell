#include "../../includes/minishell.h"

int	check_wildcard(t_comm *tmp)
{
	char	**wild;
	int		*pos;
	int		a;

	a = -1;
	if (ft_strchr(tmp->comm, -42))
	{
		pos = NULL;
		if (take_pos_for_wild(&tmp->comm, &pos))
			return (1);
		wild = wildcard(tmp->comm, pos);
		free (pos);
		if (wild)
		{
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
	}
	while (tmp->args[++a])
	{
		pos = NULL;
		if (ft_strchr(tmp->args[a], -42))
		{
			if (take_pos_for_wild(&tmp->args[a], &pos))
				return (1);
			wild = wildcard(tmp->args[a], pos);
			free (tmp->args[a]);
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
