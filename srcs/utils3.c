#include "../includes/minishell.h"

char *get_path_to_comm(char	**comm_split)
{
	int     i;
	char    *path_to_comm;
	char    *ptr_to_free;

	i = -1;
	while (comm_split[++i])
	{
		ptr_to_free = comm_split[i];
		comm_split[i] = ft_strjoin("/", comm_split[i]); //FIXME free if not allocated
		free(ptr_to_free);
	}
	i = -1;
	path_to_comm = ft_calloc(1, sizeof(char)); //FIXME free if not allocated
	while (comm_split[++i])
	{
		free(path_to_comm);
		path_to_comm = ft_strjoin(path_to_comm, comm_split[i]); //FIXME free if not allocated
	}
	return (path_to_comm);
}

// char	*ft_strjoin_mod(char const *s1, char const *s2)
// {
// 	size_t	len1;
// 	size_t	len2;
// 	char	*dst;

// 	dst = 0;
// 	if (s1 == NULL && s2 == NULL)
// 		return (NULL);
// 	if (s1 == NULL)
// 		return ((char *)s2);
// 	if (s2 == NULL)
// 		return ((char *)s1);
// 	len1 = ft_strlen(s1);
// 	len2 = ft_strlen(s2);
// 	dst = malloc(sizeof(char) * (len1 + len2) + 1);
// 	if (!dst)
// 		return (NULL);
// 	ft_strlcpy(dst, s1, len1 + 1);
// 	ft_strlcat(dst, s2, len1 + len2 + 1);
// 	return (dst);
// }
