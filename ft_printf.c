#include "ft_printf.h"

static int	print_conv(t_spec spec, va_list ap)
{
	if (ft_memchr("cC", spec.type, 2))
	{
		// printf("char\n");														//debug
		return (print_char(spec, va_arg(ap, int)));
	}
	else if (ft_memchr("pdDioOuUxX", spec.type, 10))
	{
		// printf("int\n");														//debug
		return (print_int(spec, ap));
	}
	else if (ft_memchr("S", spec.type, 1) || (ft_memchr("s", spec.type, 1) && spec.len & LEN_L))
	{
		// printf("wide thing\n");														//debug
		return (print_wstr(spec, va_arg(ap, wchar_t *)));
	}
	else if (ft_memchr("s", spec.type, 1))
	{
		// printf("string\n");														//debug
		return (print_str(spec, va_arg(ap, char *)));
	}
		// printf("other\n");														//debug
	return (print_char(spec, spec.type));
}

int	ft_printf(const char * restrict format, ...)
{
	va_list			ap;
	unsigned int	i;
	int				written;
	t_spec			spec;
	//uintmax_t		arg;
	// int				d;
	// // unsigned int	x;
	// char			*str;
	// // wchar_t			*wc;
	// void			*ptr;

	va_start(ap, format);
	i = ~0;
	written = 0;
	while (format[++i])
	{
		if (format[i] != '%')
		{
			// printf("printing (%c)\n", format[i]);												//debug
			write(1, &format[i], 1);
			written++;
		}
		else
		{
			spec = get_spec(&format[++i], ap);
			// printf("\nflags: (%d)\nwidth: (%d)\nprec: (%d)\nlen: (%d)\ntype: (%d)[%c]\n", spec.flags, spec.width, spec.prec, spec.len, spec.type, spec.type);
			// if (ft_memchr("CS", spec.type, 2) && ft_strequ(setlocale(LC_ALL, NULL), "C"))
			// {
			// 	return (-1);
			// }
			written += print_conv(spec, ap);
			while (ft_memchr("-+ #0*123456789.hljz", format[i], 20))
				i++;
			// while (format[i] && ft_strchr("0123456789", format[i]))
			// 	i++;
			// while (format[i] && ft_strchr(".0123456789", format[i]))
			// 	i++;
			// while (format[i] && ft_strchr("hljz", format[i]))
			// 	i++;
			if (format[i] && format[i] != spec.type) //!ft_strchr("sSpdDioOuUxXcC%", format[i]))
				i++;
			if (format[i] ==  '\0')
				break;
			// while (!ft_strchr("sSpdDioOuUxXcC%", format[i]) && format[i] != spec.type)
			// 	i++;

			/*
			if (spec.type == '%')
			{
				written += print_token(spec);
				// char *converted = ft_strnew(1);
				// converted[0] = '%';
				// converted[1] = '\0';
				// converted = add_padding(converted, spec);
				// ft_putstr(converted);
				// written += ft_strlen(converted);
				// free(converted);
				while (format[i] != '%')
					i++;

			}
			else if (ft_strchr("pdDioOuUxX", spec.type))
			{
				written += print_int(spec, ap);
				while (!ft_strchr("pdDioOuUxX", format[i]))
					i++;
			}
			else if (ft_strchr("sc", spec.type))
			{
				written += print_str(spec, ap);
				while (!ft_strchr("sc", format[i]))
					i++;
			}
			else 
			{
				while (!ft_strchr("pdDioOuUxXsCSc%", format[i]))
					i++;
			}
			// */
			/*
			++i;
			if (format[i] == '%')
			{
				write(1, "%", 1);
				written++;
			}
			else if (ft_isdigit(format[i]))
			{
				//printf("%d\n", ft_atoi(&format[i]));									///debug
			}
			else if (format[i] == 'c')
			{
				d = va_arg(ap, int);
				write(1, &d, 1);
				written++;
			}
			else if (format[i] == 's')
			{
				str = va_arg(ap, char *);
				write(1, str, ft_strlen(str));
				written += ft_strlen(str);
			}
			// else if (format[i] == 'S')
			// {
			// 	wc = va_arg(ap, wchar_t*);
			// 	write(1, wc, ft_strlen(wc));
			// }
			else if (format[i] == 'd' || format[i] == 'i')
			{
				d = va_arg(ap, int);
				ft_putnbr(d);
			}
			else if (format[i] == 'p')
			{
				ptr = va_arg(ap, void *);
				write(1, "0x", 2);
				str = ft_itoa_base((unsigned long)ptr, 16);
				write(1, str, ft_strlen(str));
				written += ft_strlen(str) + 2;

			}
			else if (format[i] == 'x')
			{
				d = va_arg(ap, unsigned int);
				str = ft_itoa_base((unsigned int)d, 16);
				write(1, str, ft_strlen(str));
				written += ft_strlen(str);
			}
			// */
		}
	}
	va_end(ap);
	return (written);
}