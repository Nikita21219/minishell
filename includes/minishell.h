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
	char			*comm;
	char			**flags;
	char			*args;
	char			**env;
	struct s_data	*next;
}	t_data;

int		check_argv(int argc, char **argv, char **env, t_data *data);
void	error_mes_with_exit(char *err_mes, t_data *data);
void	parser(t_data *data, char *s, char **env);
t_data	*addelem(t_data *data, char **env);
void	delelem(t_data *data);
int		check_quote(char **s, t_data *data, char quote);
int		write_arg(char **arg, char **s, int i, char quote);
int		check_second_qoute(char *s, int i, char quote);
int		takevar(char **s, t_data *data, int i);

#endif