#ifndef MINISHELL_H
# define MINISHELL_H

# include "../utils/libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define SYNTAX 1
# define MALLOC 2

typedef enum
{
    cmd, pipe, rin, rout, drin, drout, q, dq, opt, venv
}   Tokentype;

typedef struct s_envp
{
    char            *name;
    char            **value;
    struct s_envp   *next;
}                   t_envp;

typedef struct s_token
{
    char        *str;
    Tokentype   type;
}           t_token;

typedef struct s_parsed
{
    char            **command;
    char            *path;
    pid_t           pid;
    char            **redirection_in;
    char            **redirection_out;
    struct s_parsed *next;
    struct s_parsed *prev;
}                   t_parsed;

typedef struct s_struct
{
    t_envp      *envp;
    t_token     *token;
    t_parsed    *parsed;
    int         *pid;
}           t_struct;

/*  Errors */

void    ft_error(int error, char *line);

/*  Freeing */
void    ft_free_everything(t_struct *s);
void    ft_free_ptr(void *ptr);

/*  Lexer */

void    ft_struct_init(t_struct *s, char **envp);

/*  Utils */

void	ft_node_add_front(t_struct *s, char *cmd_name);


#endif