#include "../../includes/minishell.h"

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

int	writevar(char **str, t_envr p)
{
	char	*tmp;

	if (*str)
	{
		tmp = *str;
		*str = ft_strjoin(tmp, p.val);
		free(tmp);
	}
	else
		*str = ft_strdup(p.val);
	if (!(*str))
		return (1);
	return (0);
}

int	last_error(char **s, char **str)
{
	char	*tmp;
	char	*err;

	(*s)++;
	err = ft_itoa(errno);
	if (!err)
		return (1);
	if (*str)
	{
		tmp = *str;
		*str = ft_strjoin(tmp, err);
		free(tmp);
	}
	else
		*str = ft_strdup(err);
	free(err);
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
	tmp = NULL;
	p = data->data->env;
	(*s)++;
	if (varisdigit(s))
		return (0);
	if (**s == '?')
		return (last_error(s, str));
	while ((*s)[i] && ((*s)[i] == '_' || ft_isalnum((*s)[i])))
		i++;
	tmp = ft_substr(*s, 0, i);
	if (!tmp)
		return (-1);
	p = search_var(tmp, p, data->data->vars);
	if (p)
		if (writevar(str, *p))
			return (-1);
	while (i--)
		(*s)++;
	free(tmp);
	return (0);
}

int	ft_create_var(t_data *data, char *var)
{
	t_envr	*p;

	if (!ft_isalpha(*var))
		return (printf("%s: command not found\n", var));
	p = malloc(sizeof(t_envr));
	if (!p)
	{
		errno = 12;
		return (printf("Error malloc in export\n"));
	}
	write_start_env(var, &p);
	if (!p->key || !p->val)
	{
		errno = 12;
		return (printf("Error malloc in export\n"));
	}
	p->next = data->vars;
	data->vars = p;
	return (0);
}
