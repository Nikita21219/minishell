#include "../../includes/minishell.h"

int	handle_and(t_box **tmp_box)
{
	if (errno == 0)
		return (0);
	else
	{
		while (*tmp_box && is_same_lines("&&", (*tmp_box)->oper))
			*tmp_box = (*tmp_box)->next;
	}
	return (0);
}

int	handle_or(t_box **tmp_box)
{
	if (errno != 0)
		return (0);
	else
	{
		while (*tmp_box && is_same_lines("||", (*tmp_box)->oper))
			*tmp_box = (*tmp_box)->next;
	}
	return (0);
}

void	handle_logic_operators(t_box **tmp_box, char *oper)
{
	if (!oper || (oper[0] == '&' && errno == 0) || (oper[0] == '|' && errno != 0))
		return ;
	else
		while (*tmp_box && is_same_lines(oper, (*tmp_box)->oper))
			*tmp_box = (*tmp_box)->next;
}

int	set_next_box(t_box **box)
{
	t_box	*tmp_box;
	char	*oper;

	tmp_box = (*box)->next;
	if (tmp_box == NULL)
	{
		*box = tmp_box;
		return (0);
	}
	oper = tmp_box->oper;
	handle_logic_operators(&tmp_box, tmp_box->oper);
	// if (is_same_lines(tmp_box->oper, "&&"))
	// {
	// 	handle_and(&tmp_box);
	// }
	// else if (is_same_lines(tmp_box->oper, "||"))
	// {
	// 	handle_or(&tmp_box);
	// }
	// else
	// 	tmp_box = tmp_box->next;
	*box = tmp_box;
	return (0);
}

// echo 1 && echo 2
// echo 1 || echo 2