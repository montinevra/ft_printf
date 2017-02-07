/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 23:44:20 by pvan-erp          #+#    #+#             */
/*   Updated: 2017/02/06 22:29:19 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <wchar.h>
# include <locale.h>
# include "libft/libft.h"

typedef enum	e_flags
{
	FLAG_NEG = 1 << 5,
	FLAG_LEFT = 1 << 4,
	FLAG_SIGN = 1 << 3,
	FLAG_NOSIGN = 1 << 2,
	FLAG_ALT = 1 << 1,
	FLAG_ZERO = 1 << 0
}				t_flags;

typedef enum	e_len
{
	LEN_NONE, LEN_HH, LEN_H, LEN_L, LEN_LL, LEN_J, LEN_Z
}				t_len;

typedef	struct	s_spec
{
	t_flags		flags;
	int			width;
	int			prec;
	t_len		len;
	char		type;
}				t_spec;

int				ft_printf(const char *restrict format, ...);
t_spec			get_spec(char *s, va_list ap);
size_t			print_int(t_spec spec, va_list ap);
size_t			print_str(t_spec spec, char *converted);
size_t			print_char(t_spec spec, int c);
size_t			print_wstr(t_spec spec, wchar_t *converted);
char			*add_padding(char *converted, t_spec spec);
int				print_padding(char *converted, t_spec spec);

#endif
