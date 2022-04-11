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
# include <dirent.h>
# include <fcntl.h>

# include "color.h"
# include "../libft/includes/libft.h"

typedef struct s_envr
{
	char			*key;
	char			*val;
	struct s_envr	*next;
}	t_envr;

typedef struct s_comm
{
	int				fd[2];
	int				i;
	char			*comm;
	char			**args;
	char			*oper;
	struct s_data	*data;
	struct s_comm	*next;
	struct s_comm	*prev;
}	t_comm;

typedef struct s_data
{
	struct s_comm	*comm;
	struct s_envr	*env;
	char			*instr;
}	t_data;

int		check_argv(int argc, char **argv, char **env, t_data *data);
void	error_mes_with_exit(char *err_mes, t_data *data);
void	take_start_env(t_data *data, char **envar);
int		parser(t_data *data);
t_comm	*addelem(t_data *data);
void	delcommand(t_comm **comm);
int		check_quote(char **s, char **str, char quote, t_comm *data);
int		write_arg(char **arg, char **s, int i);
int		check_second_qoute(char *s, int i, char quote);
int		takevar(char **s, char **str, t_comm *data);
int		operand(t_comm	*data, char **s, int i);
int		is_same_lines(char *f_str, char *s_str);
void	delenv(t_envr **env);
void	freedata(t_data *data);
int		command_in_bin(char *command);
void	exit_from_minishell(void);
int		launcher(t_comm *data, char **env);
int		get_count_comm(t_comm *data);
int		ft_space(char str);
void	add_ptr_prev_to_data(t_comm *data);
int		close_fd(t_comm *data);
int		is_correct_comm(char *comm, char **dirs);
void	free_arrs(char **arr);
char	*get_path_to_comm(char	**comm_split);
char	*ft_strjoin_mod(char const *s1, char const *s2);
int		continue_with_print(char *err_str);
int		handle_error_executor(int error);
int		create_pipe(t_comm *data);
char	*heredoc(t_comm *data);
int		is_redirect(char *op);
char	*implement_redirections(t_comm *data);

#endif