#include "minishell.h"

static void ft_struct_envp(t_struct *s, char **envp)
{
    if (!s)
        return ;
    (void) envp;
}

/*  void ft_struct_init creates the main struct and gets the envp */
void    ft_struct_init(t_struct *s, char **envp)
{
    if (!s)
        return ;
    ft_struct_envp(s, envp);
}