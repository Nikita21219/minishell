#include "../includes/minishell.h"

void	take_data_in_list(t_comm **temp, t_data *data)
{
	(*temp)->comm = NULL;
	(*temp)->oper = NULL;
	(*temp)->data = data;
	(*temp)->next = NULL;
}

t_comm	*addelem(t_data *data)
{
	t_comm	*temp;
	t_comm	*p;

	temp = (t_comm *)malloc(sizeof(t_comm));
	if (!temp)
		return (NULL);
	temp->args = (char **)ft_calloc(sizeof(char *), 100);
	if (!temp->args)
		return (NULL);
	temp->args[0] = ft_strdup("./minishell");
	if (!temp->args[0])
		return (NULL);
	take_data_in_list(&temp, data);
	if (!data->comm)
	{
		data->comm = temp;
		return (temp);
	}
	p = data->comm;
	while (p->next)
		p = p->next;
	p->next = temp;
	return (temp);
}

void	delcommand(t_comm **comm)
{
	int		i;
	t_comm	*p;

	while (*comm)
	{
		i = 0;
		p = *comm;
		*comm = p->next;
		while (p->args[i])
		{
			free(p->args[i]);
			p->args[i++] = NULL;
		}
		free(p->args);
		if (p->comm)
			free(p->comm);
		if (p->oper)
			free(p->oper);
		free(p);
	}
}

void	delenv(t_envr **env)
{
	t_envr	*p;

	while (*env)
	{
		if ((*env)->key)
			free((*env)->key);
		if ((*env)->val)
			free((*env)->val);
		p = *env;
		*env = (*env)->next;
		free (p);
	}
}

void	write_start_env(char *envar, t_envr **temp)
{
	int	x;
	int	i;

	i = 0;
	while (envar[i] && envar[i] != '=')
		i++;
	(*temp)->key = ft_substr(envar, 0, i);
	x = ++i;
	while (envar[i])
		i++;
	(*temp)->val = ft_substr(envar, x, i - x);
}

void	take_start_env(t_data *data, char **envar)
{
	t_envr	*temp;
	int		a;

	a = -1;
	while (envar[++a])
	{
		temp = (t_envr *)malloc(sizeof(t_envr));
		if (!temp)
		{
			errno = 12;
			error_mes_with_exit("Error malloc\n", data);
		}
		write_start_env(envar[a], &temp);
		if (!temp->key || !temp->val)
		{
			errno = 12;
			error_mes_with_exit("Error malloc\n", data);
		}
		temp->next = data->env;
		data->env = temp;
	}
}
