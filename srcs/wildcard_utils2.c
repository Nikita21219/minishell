#include "../includes/minishell.h"

int	check_parts(t_finfo *dt, char *filename)
{
	if (dt->start)
		if (check_start(dt, filename))
			return (free_dt(dt));
	if (dt->finish)
		if (check_finish(dt, filename))
			return (free_dt(dt));
	if (dt->between)
		if (check_between(dt, filename))
			return (free_dt(dt));
	free_dt(dt);
	return (1);
}

int	in_arr(int *arr, int i)
{
	int	j;

	j = 0;
	while (arr[j] != -1)
		if (arr[j++] == i)
			return (1);
	return (0);
}

int	len_words_wild(int *arr)
{
	int	i;

	i = 0;
	while (arr[i] != -1)
		i++;
	return (i + 3);
}

char	**split_wild(char *str, int *arr)
{
	size_t	i;
	int		j;
	int		k;
	char	**res;

	i = 0;
	j = 0;
	k = 0;
	res = malloc(len_words_wild(arr) * (sizeof(char *) + 1));
	while (i < ft_strlen(str))
	{
		if (in_arr(arr, i))
		{
			k++;
			i++;
			continue ;
		}
		res[j] = ft_substr(str, i, arr[k] - i);
		i += ft_strlen(res[j++]);
	}
	j--;
	if (arr[--k] == (int)ft_strlen(res[j]))
		res[j][ft_strlen(res[j])] = 0;
	res[j + 1] = NULL;
	return (res);
}
