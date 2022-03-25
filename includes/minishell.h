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

typedef struct s_envr
{
	char			*key;
	char			*val;
	struct s_envr	*next;
}	t_envr;

typedef struct s_data
{
	char			*comm;
	char			**args;
	char			*oper;
	struct s_envr	*envr;
	struct s_data	*next;
}	t_data;

int		check_argv(int argc, char **argv, char **env, t_data *data);
void	error_mes_with_exit(char *err_mes, t_data *data);
t_envr	*take_start_env(t_envr *env, char **envar);
void	parser(t_data *data, char *s, t_envr *env);
t_data	*addelem(t_data *data, t_envr *en);
void	delelem(t_data *data);
int		check_quote(char **s, char **str, char quote);
int		write_arg(char **arg, char **s, int i, char quote);
int		check_second_qoute(char *s, int i, char quote);
int		takevar(char **s, char **str, int i);
int		operand(t_data	*data, char **s, int i);
int		is_same_lines(char *f_str, char *s_str);

#endif