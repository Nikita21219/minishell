#include "../includes/minishell.h"

t_comm	*addelem(t_data *data)
{
	t_comm	*temp;
	t_comm	*p;

	temp = (t_comm *)malloc(sizeof(t_comm));
	if (!temp)
		return (NULL);
	temp->args = (char **)malloc(sizeof(char *) * 100);
	temp->args[0] = ft_strdup("./minishell");
	temp->comm = NULL;
	temp->oper = NULL;
	temp->data = data;
	temp->next = NULL;
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
		while ((*comm)->args[i])
			free((*comm)->args[i++]);
		if ((*comm)->args)
			free((*comm)->args);
		if ((*comm)->comm)
			free((*comm)->comm);
		if ((*comm)->oper)
			free((*comm)->oper);
		p = *comm;
		*comm = (*comm)->next;
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

void	take_start_env(t_data *data, char **envar)
{
	t_envr	*temp;
	int		i;
	int		x;
	int		a;

	a = -1;
	while (envar[++a])
	{
		i = 0;
		temp = (t_envr *)malloc(sizeof(t_envr));
		if (!temp)
			error_mes_with_exit("Error malloc\n", data);
		while (envar[a][i])
		{
			while (envar[a][i] && envar[a][i] != '=')
				i++;
			temp->key = ft_substr(envar[a], 0, i);
			x = ++i;
			while (envar[a][i])
				i++;
			temp->val = ft_substr(envar[a], x, i - x);
			if (!temp->key || !temp->val)
				error_mes_with_exit("Error malloc\n", data);
		}
		temp->next = data->env;
		data->env = temp;
	}
}
