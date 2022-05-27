#include "../../includes/minishell.h"

int	is_logic_oper(char *str)
{
	if (is_same_lines("&&", str))
		return (1);
	if (is_same_lines("||", str))
		return (2);
	return (0);
}