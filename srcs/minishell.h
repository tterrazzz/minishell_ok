#ifndef MINISHELL_H
# define MINISHELL_H

# include "../utils/libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define SYNTAX 1
# define MALLOC 2
# define PIPE 3
# define FORK 4
# define FIILE 5

# define INFILE_PERMISSION_DENIED 1

# include <fcntl.h>

typedef enum e_token_type
{
	cmd,
	pipex,
	redirect_in,
	redirect_out,
	double_redirect_in,
	double_redirect_out,
	quote,	
	double_quote,	
	option,
	v_env,
	space,
}	t_Tokentype;

typedef struct s_envp
{
	char			**value;
	struct s_envp	*next;
}	t_envp;

typedef struct s_token
{
	char		*str;
	t_Tokentype	type;
}	t_token;

typedef struct s_redirec
{
	struct s_redirec	*next;
	struct s_redirec	*prev;
	char				*filename;
	int					index;
	int					in_or_out;
}	t_redirec;

typedef struct s_parsed
{
	char			**command;
	char			*path;
	pid_t			pid;
	t_redirec		*redirection;
	int				*pipe_fd;
	int				nb_redirect;
	int				fd_in;
	int				fd_out;
	int				error;
	struct s_parsed	*next;
	struct s_parsed	*prev;
}	t_parsed;

typedef struct s_struct
{
	t_envp		*envp;
	t_token		*token;
	t_parsed	*parsed;
	int			i_cmd;
	int			nb_cmd;
	int			nb_pipe;
	int			error;
}	t_struct;

/*  Errors */

void	ft_error(t_struct *s, int error, char *name);

/*  Freeing */

void	ft_free_everything(t_struct *s);
//void	ft_free_ptr(void *ptr);

/*  Lexer */

void	ft_lexer(t_struct *s, char *line);

/*	Init */

void	ft_struct_init(t_struct *s, char **envp);

/*  Utils */

void	ft_node_add_front(t_struct *s, char *cmd_name);
void	ft_node_add_back_envp(t_struct *s);
char	**ft_minisplit(char *line, char c);

#endif