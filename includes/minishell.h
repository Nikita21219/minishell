#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "color.h"
# include "../libft/includes/libft.h"

typedef struct s_data
{
	char	**args;
	char	*str;
}	t_data;

int		check_argv(int argc, char **argv, char **env, t_data *data);
void    error_mes_with_exit(char *err_mes, t_data *data);

#endif