#include "ft_printf.h"
#include <stdio.h>																								//debug
/*
char *get_sint(t_spec spec, va_list ap)
{
	char		*converted;
	intmax_t	arg;
	int			iarg;
	char		carg;
	short		sarg;

	if (spec.len == LEN_NONE)
	{
		iarg = va_arg(ap, int);
		converted = ft_itoa(iarg);
	}
	else if (spec.len == LEN_HH)
	{
		carg = va_arg(ap, int);
		converted = ft_itoa(carg);
	}
	else if (spec.len == LEN_H)
	{
		sarg = va_arg(ap, int);
		converted = ft_itoa(sarg);
	}
	else
	{
		arg = va_arg(ap, intmax_t);
		converted = ft_itoa(arg);
	}

	return (converted);	
}
// */
size_t	print_int(t_spec spec, va_list ap)
{
	size_t		written;
	char		*converted;
	intmax_t	arg;


	/*

	if (spec.len == LEN_NONE)
	{
		arg = va_arg(ap, int);
		//arg &= 4294967295;
	}
	else if (spec.len == LEN_HH)
		arg = (unsigned char)va_arg(ap, int);
	else if (spec.len == LEN_H)
		arg = (unsigned short)va_arg(ap, int);
	else
		arg = va_arg(ap, uintmax_t);
// */

	written = 0;
	if (spec.type == 'd' || spec.type == 'i'  || spec.type == 'D' )
	{
		//converted = get_sint(spec, ap);
		/*
		arg = va_arg(ap, unsigned int);
		if (spec.len == LEN_NONE)
			converted = ft_itoa((int)arg);
		else if (spec.len == LEN_HH)
			converted = ft_itoa((char)arg);
		else if (spec.len == LEN_H)
			converted = ft_itoa((short)arg);
		converted = ft_itoa(arg);
		//	*/
		//*
		arg = va_arg(ap, intmax_t);

		if (spec.len == LEN_NONE)
		{
			// arg &= (int)-1;
			arg = (int)arg;
		}
		else if (spec.len == LEN_HH)
		{
			// arg &= (char)-1;
			arg = (char)arg;
		}
		else if (spec.len == LEN_H)
		{
			// arg &= (short)-1;
			arg = (short)arg;
		}
		if (arg < 0)
		{
			//printf("arg < 0\n");
			spec.flags |= FLAG_NEG;
			arg = arg * -1;
		}
		converted = ft_itobase(arg, 10, "0123456789");
		// */
	}
	else
	{
		arg = va_arg(ap, uintmax_t);
		if (spec.len == LEN_NONE)
		{
			// arg &= (int)-1;
			arg &= 4294967295;
		}
		else if (spec.len == LEN_HH)
		{
			// arg &= (char)-1;
			arg &= 255;
		}
		else if (spec.len == LEN_H)
		{
			// arg &= (short)-1;
			arg &= 65535;
		}
		if (spec.type == 'u' || spec.type == 'U')
		{
			/*
			if (spec.len == LEN_NONE)
				converted = ft_itobase((unsigned int)arg, 10, "0123456789");
			else if (spec.len == LEN_HH)
				converted = ft_itobase((unsigned char)arg, 10, "0123456789");
			else if (spec.len == LEN_H)
				converted = ft_itobase((unsigned short)arg, 10, "0123456789");
				// */
			converted = ft_itobase(arg, 10, "0123456789");
		}
		else if (spec.type == 'o' || spec.type == 'O')
		{
			/*
			if (spec.len == LEN_NONE)
				converted = ft_itoa_base((unsigned int)arg, 8);
			else if (spec.len == LEN_HH)
				converted = ft_itoa_base((unsigned char)arg, 8);
			else if (spec.len == LEN_H)
				converted = ft_itoa_base((unsigned short)arg, 8);
				//*/
			converted = ft_itoa_base(arg, 8);
		}
		else if (spec.type == 'x' || spec.type == 'p')
		{
			/*
			if (spec.len == LEN_NONE)
				converted = ft_itoa_base((unsigned int)arg, 16);
			else if (spec.len == LEN_HH)
				converted = ft_itoa_base((unsigned char)arg, 16);
			else if (spec.len == LEN_H)
				converted = ft_itoa_base((unsigned short)arg, 16);
				//*/
			converted = ft_itoa_base(arg, 16);
		}
		else //if (spec.type == 'X')
		{
			/*
			if (spec.len == LEN_NONE)
				converted = ft_itobase((unsigned int)arg, 16, "0123456789ABCDEF");
			else if (spec.len == LEN_HH)
				converted = ft_itobase((unsigned char)arg, 16, "0123456789ABCDEF");
			else if (spec.len == LEN_H)
				converted = ft_itobase((unsigned short)arg, 16, "0123456789ABCDEF");
				//*/
			converted = ft_itobase(arg, 16, "0123456789ABCDEF");
		}
	}
	// spec.width -= ft_strlen(converted);
	// while ((long)spec.width-- > 0)
	// {
	// 	ft_putchar(' ');
	// 	written++;
	// }
	//written += print_padding(converted, spec);
	//*
	converted = add_padding(converted, spec);
	ft_putstr(converted);
	written += ft_strlen(converted);
	// */
	//printf("(char)~0 = %u\n", (char)~0);																		//debug
	// printf("flags = %d\n", spec.flags);																		//debug
	// printf("arg   = %ju\n", arg);																		//debug
	free(converted);
	return (written);
}