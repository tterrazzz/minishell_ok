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
	char			c;
	t_Tokentype		type;
	struct s_token	*next;
}	t_token;

typedef struct s_redirec
{
	struct s_redirec	*next;
	struct s_redirec	*prev;
	char				*filename;	
	int					*here_d_pipe_fd;
	pid_t				pid;				
	int					fd;					
	t_Tokentype			type;
}	t_redirec;

typedef struct s_parsed
{
	char			**command;
	char			*path;
	pid_t			pid;
	t_redirec		*redirection;
	t_redirec		*last_redire;
//	int				*pipe_fd;
	int				*here_d_pipe_fd;
//	int				previous_fd;
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

void	ft_parsing_error(int error);
void	ft_error(int error, char *line);

/*  Freeing */

void	ft_free_loop(t_struct *s);
void	ft_free_everything(t_struct *s);
//void	ft_free_ptr(void *ptr);

/*  Lexer */

void	ft_lexer(t_struct *s, char *line);
char	**ft_dollar_check(t_struct *s, char **tab);
char	**ft_quote_check(t_struct *s, char **tab);

/* Parsing */

void	ft_parsing(t_struct *s);

/* Expander */

char	*ft_get_env_value(t_struct *s, char *env_name);

/*	Init */

void	ft_struct_init(t_struct *s);
void	ft_struct_envp(t_struct *s, char **envp);

/*  Utils */

void	ft_node_add_front(t_struct *s, char *cmd_name);
void	ft_node_add_back_envp(t_struct *s);
char	**ft_minisplit(char *line, char c);
void	ft_struct_token(t_struct *s, char **temp);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strncpy(char *dest, const char *src, size_t n);
int		ft_strcmp(const char *s1, const char *s2);

#endif