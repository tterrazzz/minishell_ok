/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_return_code.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <avan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:07:36 by avan              #+#    #+#             */
/*   Updated: 2023/07/13 18:07:37 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_change_return_code(t_struct *s)
{
	t_envp	*return_code;

	if (!s)
		return ;
	return_code = s->envp;
	while (return_code && ft_strncmp(return_code->value[0], "?"))
		return_code = return_code->next;
	if (return_code)
	{
		if (return_code->value[1])
			ft_free_ptr((void *)return_code->value[1]);
		return_code->value[1] = ft_itoa(g_st.error);
	}
	g_st.signal = 0;
}
