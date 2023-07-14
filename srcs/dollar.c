/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurenc <llaurenc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:05:34 by avan              #+#    #+#             */
/*   Updated: 2023/07/14 13:01:06 by llaurenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strnew(size_t size)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	ft_bzero(str, size + 1);
	return (str);
}

static char	*ft_dollar_change(char *str, int start, int end, char *new_str)
{
	char	*result;
	int		str_len;
	int		new_str_len;

	str_len = ft_strlen(str);
	new_str_len = ft_strlen(new_str);
	result = ft_strnew(str_len - (end - start) + new_str_len);
	if (start < 0 || end < 0 || start >= str_len || end >= str_len)
		return (NULL);
	ft_strncpy(result, str, start);
	ft_strcpy(result + start, new_str);
	ft_strcpy(result + start + new_str_len, str + end + start + 1);
	free(str);
	return (result);
}

static char	*ft_dollar_replace(t_struct *s, char *line, int i, int k)
{
	char	*env_name;
	char	*env_value;
	int		start;

	start = i;
	i++;
	if (ft_isalpha(line[i]) || line[i] == '_')
	{
		while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
			i++;
	}
	else if (line[i] != '\"' && line[i] != '\'')
		i++;
	env_name = malloc(sizeof(char) * (i - start + 1));
	i = start + 1;
	ft_fill_dollar(line, &i, &k, &env_name);
	env_name[k] = '\0';
	env_value = ft_get_env_value(s, env_name);
	line = ft_dollar_change(line, start, k, env_value);
	free(env_name);
	return (line);
}

static int	ft_is_flagged(char c, int flag)
{
	if (c == '\"' && flag == 1)
		flag = 0;
	else if (c == '\"' && flag == 0)
		flag = 1;
	return (flag);
}

char	**ft_dollar_check(t_struct *s, char **tab, int j, int flag)
{
	int	i;

	while (tab[++j])
	{
		i = 0;
		while (tab[j][i])
		{
			flag = ft_is_flagged(tab[j][i], flag);
			if (tab[j][i] == '\'' && flag == 0)
				ft_advance_quoted(tab[j], &i);
			else if (tab[j][i] == '$')
			{
				if (!tab[j][i + 1] || tab[j][i + 1] == ' '
					|| (tab[j][i + 1] == '\"' && flag == 1))
				{
					i++;
					continue ;
				}
				tab[j] = ft_dollar_replace(s, tab[j], i, 0);
			}
			else
				i++;
		}
	}
	return (tab);
}
