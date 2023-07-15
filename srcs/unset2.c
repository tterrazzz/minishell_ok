/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <avan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:04:02 by avan              #+#    #+#             */
/*   Updated: 2023/07/15 11:36:55 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	static void	ft_error_unset_identifier gets called by ft_error_unset */
static void	ft_error_unset_identifier(char *arg)
{
	char	*str;
	char	*stock;

	if (!arg)
		return ;
	str = NULL;
	stock = NULL;
	stock = ft_strjoin("minishell: unset: `", arg);
	str = ft_strjoin(stock, "\': not a valid identifier\n");
	ft_free_ptr((void *) stock);
	write(STDERR_FILENO, str, ft_strlen(str));
	ft_free_ptr((void *) str);
	g_st.error = 1;
}

/*	void ft_error_unset writes the correct error message for the unset function
	and sets g_st.error */
void	ft_error_unset(char *arg, int error)
{
	char	*str;
	char	*stock;
	char	str2[3];

	if (!arg)
		return ;
	str = NULL;
	stock = NULL;
	if (error == INVALID_OPTION)
	{
		ft_strlcpy(str2, arg, 3);
		stock = ft_strjoin("minishell: unset: ", str2);
		str = ft_strjoin(stock, ": invalid option\n");
		ft_free_ptr((void *) stock);
		write(STDERR_FILENO, str, ft_strlen(str));
		ft_free_ptr((void *) str);
		g_st.error = 2;
	}
	else
		ft_error_unset_identifier(arg);
}
