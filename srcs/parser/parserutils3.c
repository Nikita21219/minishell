#include "../../includes/minishell.h"

void	move_list(t_comm **p)
{
	t_comm	*temp;
	char	**tmp_arg;
	int		i;

	i = 0;
	temp = (*p)->next;
	tmp_arg = (*p)->args;
	(*p)->args = temp->args;
	temp->args = tmp_arg;
	(*p)->comm = (*p)->args[1];
	while ((*p)->args[++i])
		(*p)->args[i] = (*p)->args[i + 1];
}

int	checkallcommands(t_comm **p)
{
	t_comm	*tmp;

	tmp = *p;
	if ((*p) && (*p)->next && !(*p)->comm && \
		((*p)->oper[0] == '<' || (*p)->oper[0] == '>'))
		move_list(p);
	while (tmp)
	{
		if ((!tmp->comm && !(is_same_lines(tmp->oper, ">") || \
		is_same_lines(tmp->oper, ">>") || is_same_lines(tmp->oper, "<") \
		|| is_same_lines(tmp->oper, "<<"))) || (tmp->oper && !tmp->next))
		{
			printf("Parse error\n");
			errno = 22;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	vars_quote_check(char **str, char **s, int i, t_comm *data)
{
	char	quote;

	if ((*s)[i] == '$' && (*s)[i + 1] \
		&& !ft_space((*s)[i + 1]) && (*s)[i + 1] != '=')
		return (takevar(s, str, data, i));
	if ((*s)[i] == 34 || (*s)[i] == 39)
	{
		quote = (*s)[i];
		if (check_second_qoute(*s, i, quote))
		{
			if (write_arg(str, s, i))
				return (-1);
			(*s)++;
			i = check_quote(s, str, quote, data);
			if (i < 0)
				return (-1);
			i = -1;
			(*s)++;
		}
	}
	i = check_wildcard_arg(str, s, i, data);
	return (++i);
}
