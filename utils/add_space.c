/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <avan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:39:04 by avan              #+#    #+#             */
/*   Updated: 2023/07/13 19:40:38 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

static int	ft_count_pipe(t_struct *s, char *line)
{
	int	i;
	int	count;

	if (!line)
		return (0);
	count = 0;
	i = 0;
	while (line[i])
	{
		ft_flag_quote(s, line[i]);
		if (line[i] == '|' && s->f_dquote == 0 && s->f_quote == 0)
			count += 2;
		i++;
	}
	return (count);
}

static int	ft_count_redirect(t_struct *s, char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		ft_flag_quote(s, line[i]);
		if ((line[i] == '<' && line [i + 1] == '<'
				&& s->f_dquote == 0 && s->f_quote == 0)
			|| (line[i] == '>' && line[i + 1] == '>'
				&& s->f_dquote == 0 && s->f_quote == 0))
		{
			count += 2;
			i++;
		}
		else if ((line[i] == '<' && line[i + 1] != '<'
				&& s->f_dquote == 0 && s->f_quote == 0)
			|| (line[i] == '>' && line[i + 1] != '>'
				&& s->f_dquote == 0 && s->f_quote == 0))
			count += 2;
		i++;
	}
	return (count);
}

static char	*ft_handle_redirec(char *str, int *i, int *y, char *line)
{
	if (line[*i + 1] && line[*i + 1] == '>')
		str = ft_write_doubleredirec(str, i, y, 2);
	else
		str = ft_write_redirec(str, y, 2);
	return (str);
}

static char	*ft_space_add(t_struct *s, char *line, char *str, int i)
{
	int	y;

	y = 0;
	while (line[i])
	{
		ft_flag_quote(s, line[i]);
		str[y] = line[i];
		if (line[i] == '|' && s->f_dquote == 0 && s->f_quote == 0)
			str = ft_write_space(str, &y);
		if (line[i] == '<' && s->f_dquote == 0 && s->f_quote == 0)
		{
			if (line[i + 1] && line[i + 1] == '<')
				str = ft_write_doubleredirec(str, &i, &y, 1);
			else
				str = ft_write_redirec(str, &y, 1);
		}
		else if (line[i] == '>' && s->f_dquote == 0 && s->f_quote == 0)
			str = ft_handle_redirec(str, &i, &y, line);
		i++;
		y++;
	}
	str[y] = '\0';
	return (str);
}

char	*ft_add_space(t_struct *s, char *line)
{
	char	*str;
	int		count;

	count = ft_count_pipe(s, line);
	count += ft_count_redirect(s, line);
	str = malloc(sizeof(char) * (count + ft_strlen(line) + 1));
	if (!str)
		return (NULL);
	str = ft_space_add(s, line, str, 0);
	free(line);
	return (str);
}
