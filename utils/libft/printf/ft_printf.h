/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:45:31 by avan              #+#    #+#             */
/*   Updated: 2022/12/07 11:14:35 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "../libft.h"

# define FLAG_ZERO 0b1
# define FLAG_MOINS 0b10
# define FLAG_POINT 0b100
# define FLAG_HASHTAG 0b1000
# define FLAG_ESPACE 0b10000
# define FLAG_PLUS 0b100000

typedef struct elem
{
	char			spe;
	char			*elflag;
	long			flags;
	int				tabint[2];
	char			*s;
}			t_elem;

t_elem	*ft_enew(void);
int		ft_isspeci(char c);
int		ft_isflag(char c);
int		ft_isvalidflag(const char *str, int i, int nbr);
int		ft_cutflag(t_elem *e);
int		ft_givespeci(const char *arg);
int		ft_giveindex(char speci);
void	ft_putnstr_printf(const char *s, int len, int *nbr);
int		ft_findlen(const char *s, int *len);
int		ft_printf(const char *content, ...);
void	ft_fillf(void (**f)());
void	ft_strdup_pf(void *adr, t_elem *e);
void	ft_itoa_baseprintf(void *adr, t_elem *e);
void	ft_itoa_i(void *adr, t_elem *e);
void	ft_putchar_printf(char c, int fd, int *nbr);
void	ft_putstr_printf(char *c, int fd, int *nbr);
void	ft_putnstr_printf(const char *s, int len, int *nbr);
void	ft_putnstr_nodouble(const char *s, int len, int *nbr);
void	ft_putelses(t_elem *e, int *nb, int l, int temp);

#endif
