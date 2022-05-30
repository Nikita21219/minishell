#include "../../includes/minishell.h"

void	handle_logic_operators(t_box **tmp_box, char *oper)
{
	t_box	*next;

	if (!oper || (oper[0] == '&' && errno == 0) || (oper[0] == '|' && errno != 0))
		return ;
	else
		while (*tmp_box && is_same_lines(oper, (*tmp_box)->oper))
		{
			next = (*tmp_box)->next;
			freebox(tmp_box);
			*tmp_box = next;
		}
}

void	set_next_box(t_box **box)
{
	t_box	*tmp_box;

	tmp_box = (*box)->next;
	if (tmp_box == NULL)
	{
		*box = tmp_box;
		return ;
	}
	handle_logic_operators(&tmp_box, tmp_box->oper);
	*box = tmp_box;
}

int	freebox(t_box **box)
{
	if (*box)
	{
		if ((*box)->oper)
		{
			free((*box)->oper);
			(*box)->oper = NULL;
		}
		if ((*box)->oper)
		{
			free((*box)->next);
			(*box)->next = NULL;
		}
		delcommand(&(*box)->dt_comm);
		if (*box)
		{
			free(*box);
			*box = NULL;
		}
	}
	return (0);
}
