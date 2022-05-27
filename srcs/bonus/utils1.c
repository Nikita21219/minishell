#include "../../includes/minishell.h"

// int	check_pipe(t_comm *data)
// {
// 	if (is_same_lines(data->oper, "|"))
	
// }

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
	*box = tmp_box;
	return (0);
}
