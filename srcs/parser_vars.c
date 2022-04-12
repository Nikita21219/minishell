#include "../includes/minishell.h"

int	varisdigit(char **s)
{
	if (ft_isdigit(**s))
	{
		while ((**s) && ft_isdigit(**s))
			(*s)++;
		return (1);
	}
	return (0);
}

int	writevar(char **str, char **tmp, t_envr p)
{
	if (*str)
	{
		free(tmp);
		tmp = str;
		*str = ft_strjoin(*tmp, p.val);
	}
	else
		*str = ft_strdup(p.val);
	if (!(*str))
		return (1);
	return (0);
}

int	takevar(char **s, char **str, t_comm *data)
{
	char	*tmp;
	t_envr	*p;
	int		i;

	i = 0;
	p = data->data->env;
	(*s)++;
	if (varisdigit(s))
		return (0);
	while ((*s)[i] && ((*s)[i] == '_' || ft_isalnum((*s)[i])))
		i++;
	tmp = ft_substr(*s, 0, i);
	if (!tmp)
		return (-1);
	while (p && !is_same_lines(tmp, p->key))
		p = p->next;
	if (p)
		if (writevar(str, &tmp, *p))
			return (-1);
	while (i--)
		(*s)++;
	free(tmp);
	return (0);
}
