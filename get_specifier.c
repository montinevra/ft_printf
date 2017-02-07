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
	{
		prec = va_arg(ap, int);
	}
	else
	{
		prec = ft_atoi_base(s, 10);
	}
	if (prec < 0)
	{
		prec = 0;
	}
	return (prec);
}

static int		get_flag(char c)
{
	if (c == '-')
		return(FLAG_LEFT);
	else if (c == '+')
		return(FLAG_SIGN);
	else if (c == ' ')
		return(FLAG_NOSIGN);
	else if (c == '#')
		return(FLAG_ALT);
	else if (c == '0')
		return(FLAG_ZERO);
	return (0);
}

t_spec			get_spec(char *s, va_list ap)
{
	t_spec			spec;
	
	spec.flags = 0;
	spec.width = 0;
	spec.len = LEN_NONE;
	spec.prec = -1;
	while (ft_memchr("-+ #*0123456789.hljz", *s, 20))
	{
		if (get_flag(*s))		
			spec.flags |= get_flag(*s++);
		else if (*s == '*')
		{
			spec.width = va_arg(ap, int);
			if (spec.width < 0)
			{
				spec.flags |= FLAG_LEFT;
				spec.width *= -1;
			}
			s++;
		}
		else if (ft_memchr("123456789", *s, 9))
		{
			spec.width = ft_atoi_base(s, 10);
			while (ft_isdigit(*s))
				s++;
		}
		else if (*s == '.')
		{
			spec.prec = get_prec(++s, ap);
			if (*s == '*')
				s++;
			else
			{
				while (ft_isdigit(*s))
					s++;
			}
		}
		else if (ft_memchr("hljz", *s, 4))
		{
			if (get_len(s) > spec.len)
				spec.len = get_len(&*s);
			if (ft_memchr("hl", *s, 2) && *s == *(s + 1))
				s++;
			s++;
		}
	}
	spec.type = *s;
	if (ft_memchr("DUOpSC", spec.type, 6))
		spec.len = LEN_L;
	return (spec);
}