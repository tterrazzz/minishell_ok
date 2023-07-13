/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_list_to_tab_string.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <avan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:33:26 by avan              #+#    #+#             */
/*   Updated: 2023/07/13 18:33:27 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	static int ft_envp_nb_nodes returns the number of nodes in the envp list */
static int	ft_envp_nb_nodes(t_envp *envp)
{
	t_envp	*temp;
	int		nb_nodes;

	if (!envp)
		return (0);
	temp = envp;
	nb_nodes = 0;
	while (temp)
	{
		nb_nodes++;
		temp = temp->next;
	}
	return (nb_nodes);
}

/*	static char *ft_get_value joins the value[0] + '=' + value[1] of the
	envp node */
static char	*ft_get_value(char **value)
{
	char	*str;
	char	*stock;

	if (!value)
		return (0);
	if (!ft_strncmp(value[0], "OLDPWD") && !value[1])
		return (ft_strdup(value[0]));
	stock = ft_strjoin(value[0], "=");
	if (!value[1])
		str = ft_strjoin(stock, "\0");
	else
		str = ft_strjoin(stock, value[1]);
	free(stock);
	return (str);
}

/*	static char **ft_fill_tab_envp returns a char **tab filled with the value
	of the envp */
static char	**ft_fill_tab_envp(t_envp *envp)
{
	t_envp	*temp;
	char	**tab;
	int		i;
	int		size;

	if (!envp)
		return (NULL);
	size = ft_envp_nb_nodes(envp);
	tab = (char **)malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	temp = envp;
	i = 0;
	while (temp && i < size)
	{
		tab[i] = ft_get_value(temp->value);
		if (!(tab[i]))
			return (NULL);
		i++;
		temp = temp->next;
	}
	tab[i] = NULL;
	return (tab);
}

/*	char **ft_envp_list_to_tab_string gets the envp list and returns the pointer
	to a char** version of it */
char	**ft_envp_list_to_tab_string(t_envp	*envp)
{
	char	**tab;

	if (!envp)
		return (NULL);
	tab = ft_fill_tab_envp(envp);
	return (tab);
}
