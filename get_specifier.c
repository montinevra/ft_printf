/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_specifier.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 16:00:19 by pvan-erp          #+#    #+#             */
/*   Updated: 2017/02/07 16:00:21 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_len	get_len(const char *c)
{
	if (*c == 'h')
	{
		if (*(c + 1) == 'h')
			return (LEN_HH);
		return (LEN_H);
	}
	else if (*c == 'l')
	{
		if (*(c + 1) == 'l')
			return (LEN_LL);
		return (LEN_L);
	}
	else if (*c == 'j')
		return (LEN_J);
	else if (*c == 'z')
		return (LEN_Z);
	return (LEN_NONE);
}

static int		get_prec(char *s, va_list ap)
{
	int	prec;

	if (*s == '*')
		prec = va_arg(ap, int);
	else
		prec = ft_atoi_base(s, 10);
	if (prec < 0)
		prec = 0;
	return (prec);
}

static t_spec	get_width(char *s, t_spec spec, va_list ap)
{
	if (*s == '*')
	{
		spec.width = va_arg(ap, int);
		if (spec.width < 0)
		{
			spec.flags |= FLAG_LEFT;
			spec.width *= -1;
		}
	}
	else
		spec.width = ft_atoi_base(s, 10);
	return (spec);
}

static int		get_flag(char c)
{
	if (c == '-')
		return (FLAG_LEFT);
	else if (c == '+')
		return (FLAG_SIGN);
	else if (c == ' ')
		return (FLAG_NOSIGN);
	else if (c == '#')
		return (FLAG_ALT);
	else if (c == '0')
		return (FLAG_ZERO);
	return (0);
}

t_spec			get_spec(char *s, va_list ap)
{
	t_spec	spec;

	spec = (t_spec){.flags = 0, .width = 0, .len = LEN_NONE, .prec = -1};
	while (ft_memchr("-+ #*0123456789.hljz", *s, 20))
	{
		spec.flags |= get_flag(*s);
		if (ft_memchr("*123456789", *s, 10))
			spec = get_width(s, spec, ap);
		else if (*s == '.')
			spec.prec = get_prec(++s, ap);
		else if (ft_memchr("hljz", *s, 4))
			if (get_len(s) > spec.len)
				spec.len = get_len(s);
		if (ft_memchr("123456789", *s, 9))
			while (ft_isdigit(*s))
				s++;
		else if (ft_memchr("-+ #*0.hljz", *s, 11))
			s++;
		if (ft_memchr("hl", *s, 2) && *s == *(s - 1))
			s++;
	}
	spec.type = *s;
	if (ft_memchr("DUOpSC", spec.type, 6))
		spec.len = LEN_L;
	return (spec);
}
