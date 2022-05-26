#include "../../includes/minishell.h"

int	ft_sign(char **str)
{
	int	n;

	n = 1;
	if (**str == '-')
			n = -1;
	if (**str == '-' || **str == '+')
		(*str)++;
	return (n);
}

int	ft_checkdig(char **str, unsigned long long int *dig, int *j)
{
	while (**str >= '0' && **str <= '9')
	{
		*dig = 10 * (*dig) + (**str - '0');
		(*str)++;
		(*j)++;
	}
	while (ft_space(**str))
		(*str)++;
	if (**str)
		return (1);
	return (0);
}

long int	ft_atoi_mod(char *str, int pid)
{
	int						n;
	char					*err;
	unsigned long long int	dig;
	int						j;
	unsigned long long int	max;

	if (!str)
		return (0);
	err = str;
	max = 9223372036854775807;
	max++;
	n = ft_sign(&str);
	j = 0;
	dig = 0;
	if (pid != 0)
		printf("exit\n");
	if (ft_checkdig(&str, &dig, &j) || j > 19 || \
	(n > 0 && dig > (max - 1)) || (n < 0 && dig > max))
	{
		printf("exit: %s: numeric argument required\n", err);
		return (255);
	}
	return (n * dig);
}

int	ft_exit(t_data *data)
{
	int			i;

	i = 0;
	if (data->comm->args[1] && data->comm->args[2])
	{
		printf("exit: too many arguments\n");
		return (1);
	}
	errno = ft_atoi_mod(data->comm->args[1], data->comm->pid);
	freedata(data);
	delenv(&data->env);
	exit(errno % 256);
}
