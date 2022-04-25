#include "../includes/minishell.h"

void    *wild_add_elem(t_wild **dt, char *file)
{
    t_wild  *tmp_dt;
    (void) file;

    tmp_dt = *dt;
    if (tmp_dt)
        printf("test1\n");
    printf("test2\n");
    return (NULL);
}
