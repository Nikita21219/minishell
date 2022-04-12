#include "../includes/minishell.h"

void    cd(char *path)
{
    if (chdir(path))
    {
        printf("FAIL\n");
        exit (1);
    }
}
    