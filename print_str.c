/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 18:50:13 by pvan-erp          #+#    #+#             */
/*   Updated: 2017/02/07 18:50:15 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	i_to_utf8(int c, char *converted)
{
	if (c >= 0x110000)
		return (0);
	else if (c >= 0x10000)
	{
		converted[0] = 0xF0 | ((c >> 18) & 07);
		converted[1] = 0x80 | ((c >> 12) & 077);
		converted[2] = 0x80 | ((c >> 6) & 077);
		converted[3] = 0x80 | (c & 077);
		return (4);
	}
	else if (c >= 0x800)
	{
		converted[0] = 0xE0 | ((c >> 12) & 017);
		converted[1] = 0x80 | ((c >> 6) & 077);
		converted[2] = 0x80 | (c & 077);
		return (3);
	}
	else if (c >= 0x80)
	{
		converted[0] = 0xC0 | ((c >> 6) & 037);
		converted[1] = 0x80 | (c & 077);
		return (2);
	}
	converted[0] = c;
	return (1);
}

size_t		print_char(t_spec spec, int c)
{
	size_t	written;
	char	*converted;

	if (spec.type == 'c' && spec.len != LEN_L)
		converted = ft_strndup((char *)&c, 1);
	else
	{
		converted = ft_strnew(4);
		i_to_utf8(c, converted);
	}
	converted = add_padding(converted, spec);
	ft_putstr(converted);
	written = ft_strlen(converted);
	if ((spec.type == 'c' || spec.type == 'C') && c == '\0')
	{
		ft_putstr(converted + ft_strlen(converted) + 1);
		written += ft_strlen(converted + ft_strlen(converted) + 1) + 1;
	}
	free(converted);
	return (written);
}

size_t		print_str(t_spec spec, char *converted)
{
	size_t	written;

	if (converted)
	{
		converted = ft_strdup(converted);
		converted = add_padding(converted, spec);
	}
	else
		converted = ft_strdup("(null)");
	ft_putstr(converted);
	written = ft_strlen(converted);
	free(converted);
	return (written);
}

size_t		print_wstr(t_spec spec, wchar_t *wconverted)
{
	size_t	written;
	char	*converted;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (wconverted)
	{
		converted = ft_strnew(ft_ustrlen(wconverted));
		while (wconverted[i])
		{
			j += i_to_utf8(wconverted[i], &converted[j]);
			i++;
		}
		converted = add_padding(converted, spec);
	}
	else
		converted = ft_strdup("(null)");
	ft_putstr(converted);
	written = ft_strlen(converted);
	free(converted);
	return (written);
}
