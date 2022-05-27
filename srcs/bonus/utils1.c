#include "../../includes/minishell.h"

int	handle_and(t_box **tmp_box, char *oper)
{
	(void) tmp_box;
	(void) oper;
	return (0);
}

// echo 1 && echo 2

int	handle_or(t_box **tmp_box, char *oper)
{
	(void) tmp_box;
	(void) oper;
	return (0);
}

int	set_next_box(t_box **box)
{
	t_box	*tmp_box;
	char	*oper;

	tmp_box = *box;
	oper = tmp_box->oper;
	if (is_same_lines(tmp_box->oper, "&&"))
	{
		handle_and(&tmp_box, tmp_box->oper);
	}
	else if (is_same_lines(tmp_box->oper, "||"))
	{
		handle_or(&tmp_box, tmp_box->oper);
	}
	else
		tmp_box = tmp_box->next;
	*box = tmp_box;
	return (0);
}

// echo 1 && echo 2
// echo 1 || echo 2