/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 16:37:43 by pvan-erp          #+#    #+#             */
/*   Updated: 2017/02/07 16:41:31 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*join_padding(char *converted, char *leading, int len, t_spec spec)
{
	char *padded;

	padded = ft_strnew(spec.width);
	if (spec.flags & FLAG_ZERO && !(spec.flags & FLAG_LEFT) && spec.prec <= 0)
	{
		ft_strfill(padded, spec.width, '0');
		ft_strncpy(padded, leading, ft_strlen(leading));
		ft_strncpy(padded + ft_strlen(padded) - len, converted, len);
	}
	else
	{
		ft_strfill(padded, spec.width, ' ');
		if (spec.flags & FLAG_LEFT)
		{
			ft_strncpy(padded, leading, ft_strlen(leading));
			ft_strncpy(padded + ft_strlen(leading), converted, len);
		}
		else
		{
			ft_strncpy(padded + ft_strlen(padded) - ft_strlen(leading) - len,
					leading, ft_strlen(leading));
			ft_strncpy(padded + ft_strlen(padded) - len, converted, len);
		}
	}
	return (padded);
}

/*
**	standard library is inconsistent re: ("%#.0o", 0)
*/

static char	*pad_zero(char *converted, t_spec spec)
{
	char	*padded;

	if ((size_t)spec.prec > ft_strlen(converted) && spec.prec != -1)
	{
		padded = ft_strnew(spec.prec);
		ft_strfill(padded, spec.prec, '0');
		ft_strcpy(padded + ft_strlen(padded) - ft_strlen(converted), converted);
		free(converted);
		return (padded);
	}
	else if (ft_strequ("0", converted) && spec.prec == 0 &&
			!(ft_memchr("oO", spec.type, 2) && spec.flags & FLAG_ALT))
	{
		converted[0] = '\0';
	}
	return (converted);
}

static int	len_broken_utf8(char *converted, int prec)
{
	if (prec >= 3 && (converted[prec - 3] & 0xF0) == 0xF0)
		return (3);
	else if (prec >= 2 && (converted[prec - 2] & 0xE0) == 0xE0)
		return (2);
	else if (prec >= 1 && (converted[prec - 1] & 0xC0) == 0xC0)
		return (1);
	else
		return (0);
}

static char	*get_leading(char *converted, t_spec spec)
{
	char	*leading;

	leading = ft_strnew(2);
	if (ft_memchr("diD", spec.type, 3)
			&& (spec.flags & (FLAG_NEG | FLAG_SIGN | FLAG_NOSIGN)))
	{
		if (spec.flags & FLAG_NEG)
			leading = ft_strcpy(leading, "-");
		else if (spec.flags & FLAG_SIGN)
			leading = ft_strcpy(leading, "+");
		else
			leading = ft_strcpy(leading, " ");
	}
	else if ((ft_memchr("oOxX", spec.type, 4) && spec.flags & FLAG_ALT)
			|| spec.type == 'p')
	{
		if (ft_memchr("oO", spec.type, 2) && ft_strcmp("0", converted))
			leading = ft_strcpy(leading, "0");
		if ((spec.type == 'x' && ft_strcmp("0", converted)) || spec.type == 'p')
			leading = ft_strcpy(leading, "0x");
		if (spec.type == 'X' && ft_strcmp("0", converted))
			leading = ft_strcpy(leading, "0X");
	}
	return (leading);
}

char		*add_padding(char *converted, t_spec spec)
{
	char	*padded;
	char	*leading;
	int		len;

	leading = get_leading(converted, spec);
	if (ft_memchr("dDiuUoOxXp", spec.type, 10))
		converted = pad_zero(converted, spec);
	else if (ft_memchr("sS", spec.type, 2) &&
			(size_t)spec.prec < ft_strlen(converted))
		converted[spec.prec - len_broken_utf8(converted, spec.prec)] = '\0';
	if (spec.type == 'c' && spec.len != LEN_L)
		len = 1;
	else
		len = ft_strlen(converted);
	if (len + ft_strlen(leading) > (size_t)spec.width)
		padded = ft_strjoin(leading, converted);
	else
		padded = join_padding(converted, leading, len, spec);
	free(converted);
	free(leading);
	return (padded);
}
