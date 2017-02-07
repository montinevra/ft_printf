#include "ft_printf.h"
#include <stdio.h>																	//debug

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

t_spec			get_spec(const char *s, va_list ap)
{
	unsigned int	i;
	t_spec			spec;
	
	i = 0;
	// printf("\nuninitialized spec.flags = %c; address = %p\n", spec.flags, &spec.flags);				///debug
	spec.flags = 0;
	spec.width = 0;
	spec.len = LEN_NONE;
	spec.prec = -1;
	// printf("\ninitialized spec.flags = %c; address = %p\n", spec.flags, &spec.flags);				///debug
	// write (1, "flags: ", 7);													///debug



	while (ft_memchr("-+ #*0123456789.hljz", s[i], 20))
	{
		if (get_flag(s[i]))		
			spec.flags |= get_flag(s[i++]);
		else if (s[i] == '*')
		{
			spec.width = va_arg(ap, int);
			if (spec.width < 0)
			{
				spec.flags |= FLAG_LEFT;
				spec.width *= -1;
			}
			i++;
		}
		else if (ft_memchr("123456789", s[i], 9))
		{
			spec.width = ft_atoi_base(&s[i], 10);

			while (ft_isdigit(s[i]))
				i++;

		}
		else if (s[i] == '.')
		{
			i++;
			if (s[i] == '*')
			{
				spec.prec = va_arg(ap, int);
				i++;
			}
			else
			{
				spec.prec = ft_atoi_base(&s[i], 10);
				while (ft_isdigit(s[i]))
					++i;
			}
			if (spec.prec < 0)
			{
				spec.prec = 0;
			}
		}
		else if (ft_memchr("hljz", s[i], 4))
		{
			if (get_len(&s[i]) > spec.len)
				spec.len = get_len(&s[i]);
			if (ft_memchr("hl", s[i], 2) && s[i] == s[i + 1])
				i++;
			i++;
		}
	}
	spec.type = s[i];




/*
	while (get_flag(s[++i]))		
	{
		spec.flags |= get_flag(s[i]);
		// write(1, &s[i], 1);														///debug
	}
	spec.width = ft_atoi(&s[i]);
	while (ft_isdigit(s[i]))
		++i;
	if (s[i] == '.')
	{
		++i;
		spec.prec = ft_atoi(&s[i]);
		if (spec.prec < 0)
			spec.prec = 0;
	}
	else
		spec.prec = -1;
	while (ft_isdigit(s[i]))
		++i;
	spec.len = get_len(&s[i]);
	while (get_len(&s[i]))
		++i;
	spec.type = s[i];

*/


	if (ft_memchr("DUOpSC", spec.type, 6))
	{
		spec.len = LEN_L;
		//spec.type = ft_tolower(spec.type);
		// if (spec.type == 'p')
		// {
		// 	spec.type = 'x';
		// 	spec.flags |= 2;
		// }
	}
	/*
	printf("\nflag bits = %d\nwidth = %d\nprecision = %d\nlength = %d\nconversion = %c\n",
		spec.flags, spec.width, spec.prec, spec.len, spec.type);				//debug
		// */
	// write (1, "\n", 1);															///debug
	return (spec);
}