#include "../includes/minishell.h"

t_data	*addelem(t_data *data, t_envr *en)
{
	t_data	*temp;
	t_data	*p;

	temp = (t_data *)malloc(sizeof(t_data));
	if (!temp)
		return (NULL);
	temp->args = (char **)malloc(sizeof(char *) * 100);
	temp->args[0] = ft_strdup("./minishell");
	temp->comm = NULL;
	temp->envr = en;
	temp->oper = NULL;
	temp->next = NULL;
	if (!data)
		return (temp);
	p = data;
	while (p->next)
		p = p->next;
	p->next = temp;
	return (temp);
}

void	delelem(t_data *data)
{
	int	i;

	i = 0;
	while (data)
	{
		while (data->args[i])
			free(data->args[i++]);
		free(data->args);
		free(data->comm);
		free(data->oper);
		data = data->next;
	}
}

t_envr	*take_start_env(t_envr *env, char **envar)
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
		while (envar[a][i])
		{
			while (envar[a][i] && envar[a][i] != '=')
				i++;
			temp->key = ft_substr(envar[a], 0, i);
			x = ++i;
			while (envar[a][i])
				i++;
			temp->val = ft_substr(envar[a], x, i - x);
		}
		temp->next = env;
		env = temp;
	}
	return (env);
}
