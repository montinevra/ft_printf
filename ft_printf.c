/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 22:27:12 by pvan-erp          #+#    #+#             */
/*   Updated: 2017/02/07 16:58:43 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_conv(t_spec spec, va_list ap)
{
	if (ft_memchr("cC", spec.type, 2))
	{
		return (print_char(spec, va_arg(ap, int)));
	}
	else if (ft_memchr("dDi", spec.type, 3))
	{
		return (print_int(spec, ap));
	}
	else if (ft_memchr("poOuUxX", spec.type, 7))
	{
		return (print_uint(spec, ap));
	}
	else if (ft_memchr("S", spec.type, 1) ||
			(ft_memchr("s", spec.type, 1) && spec.len & LEN_L))
	{
		return (print_wstr(spec, va_arg(ap, wchar_t *)));
	}
	else if (ft_memchr("s", spec.type, 1))
	{
		return (print_str(spec, va_arg(ap, char *)));
	}
	return (print_char(spec, spec.type));
}

int			ft_printf(const char *restrict format, ...)
{
	va_list			ap;
	unsigned int	i;
	int				written;
	t_spec			spec;

	va_start(ap, format);
	i = ~0;
	written = 0;
	while (format[++i])
	{
		if (format[i] != '%')
			written += write(1, &format[i], 1);
		else
		{
			spec = get_spec((char *)&format[++i], ap);
			written += print_conv(spec, ap);
			while (format[i] != spec.type)
				i++;
			if (format[i] == '\0')
				break ;
		}
	}
	va_end(ap);
	return (written);
}
