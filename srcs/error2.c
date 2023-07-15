/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <avan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 11:26:14 by avan              #+#    #+#             */
/*   Updated: 2023/07/15 11:55:47 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execve_error(char *name)
{
	char	*str;
	char	*stock;

	if (!name)
		return ;
	stock = ft_strjoin("minishell: ", name);
	if (!ft_check_if_slash(name, 0))
		str = ft_strjoin(stock, ": command not found\n");
	else
	{
		if (errno == EACCES)
			str = ft_strjoin(stock, ": Permission denied\n");
		else if (errno == ENOENT)
			str = ft_strjoin(stock, ": No such file or directory\n");
	}
	write(STDERR_FILENO, str, ft_strlen(str));
}

static void	print_error2(char *content)
{
	char	*str;
	char	*stock;

	stock = ft_strjoin("minishell: syntax error near unexpected token \'",
			content);
	str = ft_strjoin(stock, "\'\n");
	write(STDERR_FILENO, str, ft_strlen(str));
	g_st.error = 258;
	ft_free_ptr((void *)stock);
	ft_free_ptr((void *)str);
}

int	print_error(int error_code, char *content)
{
	char	*str;
	char	*stock;

	stock = NULL;
	str = NULL;
	if (error_code == 1)
	{
		write(STDERR_FILENO,
			"minishell: parse error quotes are never closed\n", 47);
		g_st.error = 1;
	}
	else if (error_code == 2)
		print_error2(content);
	else if (error_code == 3)
	{
		write(STDERR_FILENO, "minishell: syntax error\n", 24); 
		g_st.error = 1;
	}
	return (1);
}
