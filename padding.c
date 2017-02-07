#include "ft_printf.h"
#include <stdio.h>																								//debug
/*
**	standard library is inconsistent re: "%#.0o", 0
*/
//*

static char	*pad_zero(char *converted, t_spec spec)
{
	char	*padded;
	// printf("padding zero... spec.prec =%d; strlen conv = %zu\n", spec.prec, ft_strlen(converted));			///debug
	if ((size_t)spec.prec > ft_strlen(converted) && spec.prec != -1)
	{
		padded = ft_strnew(spec.prec);
		ft_strfill(padded, spec.prec, '0');
		// printf("filled padded: %s\n", padded);														//debug
		ft_strcpy(padded + ft_strlen(padded) - ft_strlen(converted), converted);
		// printf("copied converted: %s\n", padded);													//debug
		free(converted);
		return (padded);
	}
	else if (ft_strequ("0", converted) && spec.prec == 0 && !(ft_memchr("oO", spec.type, 2) && spec.flags & FLAG_ALT))
	{
		converted[0] = '\0';
	}
	return (converted);
}
// */



static char	*get_leading(char *converted, t_spec spec)
{
	char	*leading;

	leading = ft_strnew(2);
	if (ft_memchr("diD", spec.type, 3) && (spec.flags & (FLAG_NEG | FLAG_SIGN | FLAG_NOSIGN)))// && converted[0] != '-')
	{
		// pad_int(converted, spec);
		// printf("int with sign\n");																			//debug
		//*
		if (spec.flags & FLAG_NEG)
			leading = ft_strcpy(leading, "-");
		else if (spec.flags & FLAG_SIGN)
			leading = ft_strcpy(leading, "+");
		else
			leading = ft_strcpy(leading, " ");
			// */
	}
	else if ((ft_memchr("oOxX", spec.type, 4) && spec.flags & FLAG_ALT) || spec.type == 'p')
	{
		// printf("octal or hex\n");																					//debug
			//*
		if (ft_memchr("oO", spec.type, 2) && ft_strcmp("0", converted))// && !(!ft_strcmp("0", converted) != !(spec.prec != 0)))
			leading = ft_strcpy(leading, "0");
		if ((spec.type == 'x' && ft_strcmp("0", converted)) || spec.type == 'p')
			leading = ft_strcpy(leading, "0x");
		if (spec.type == 'X' && ft_strcmp("0", converted))
			leading = ft_strcpy(leading, "0X");
			// */
	}
	return (leading);
}

char		*add_padding(char *converted, t_spec spec)
{
	char	*padded;
	char	*leading;
	int 	len;

	// printf("flags: %i\n", spec.flags);																			//debug
	leading = get_leading(converted, spec);
	if (ft_memchr("dDiuUoOxXp", spec.type, 10))
	{
		converted = pad_zero(converted, spec);
		// printf("converted with zero padded: %s\n", converted);											///debug
	}
	else if (ft_memchr("sS", spec.type, 2) && (size_t)spec.prec < ft_strlen(converted))
	{
		if (spec.prec >= 3 && (converted[spec.prec - 3] & 0xF0) == 0xF0)
			converted[spec.prec - 3] = '\0';
		else if (spec.prec >= 2 && (converted[spec.prec - 2] & 0xE0) == 0xE0)
			converted[spec.prec - 2] = '\0';
		else if (spec.prec >= 1 && (converted[spec.prec - 1] & 0xC0) == 0xC0)
			converted[spec.prec - 1] = '\0';
		else
			converted[spec.prec] = '\0';
	}


	if (spec.type == 'c' && spec.len != LEN_L)
	{
		len = 1;
	}
	else
	{
		len = ft_strlen(converted);
		// printf("%lu", ft_strlen(leading));																		//debug
	}
	if (len + ft_strlen(leading) > (size_t)spec.width)
	{
		padded = ft_strjoin(leading, converted);
	}
	else
	{
		padded = ft_strnew(spec.width);
		if (spec.flags & FLAG_ZERO && !(spec.flags & FLAG_LEFT) && spec.prec <= 0)
		{
			ft_strfill(padded, spec.width, '0');
			ft_strncpy(padded, leading, ft_strlen(leading));
			ft_strncpy(padded + ft_strlen(padded) - len, converted, len);
		}
		else
		{
			// printf("filling with       .\n");
			ft_strfill(padded, spec.width, ' ');
			// printf("(%s)\n", padded);
			if (spec.flags & FLAG_LEFT)
			{
				// printf("left aligned\n");
				ft_strncpy(padded, leading, ft_strlen(leading));
				ft_strncpy(padded + ft_strlen(leading), converted, len);
			}
			else
			{
				// printf("right aligned\n");
				ft_strncpy(padded + ft_strlen(padded) - ft_strlen(leading) - len, leading, ft_strlen(leading));
				ft_strncpy(padded + ft_strlen(padded) - len, converted, len);
				// printf("(%s len = %d)\n", padded, len);

			}
		}
	}

	free(converted);
	free(leading);
	return (padded);
}