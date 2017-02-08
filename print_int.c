/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 16:58:06 by pvan-erp          #+#    #+#             */
/*   Updated: 2017/02/07 16:58:08 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	print_int(t_spec spec, va_list ap)
{
	size_t		written;
	char		*converted;
	intmax_t	arg;

	arg = va_arg(ap, intmax_t);
	if (spec.len == LEN_NONE)
		arg = (int)arg;
	else if (spec.len == LEN_HH)
		arg = (char)arg;
	else if (spec.len == LEN_H)
		arg = (short)arg;
	if (arg < 0)
	{
		spec.flags |= FLAG_NEG;
		arg = arg * -1;
	}
	converted = ft_itobase(arg, 10, "0123456789");
	converted = add_padding(converted, spec);
	ft_putstr(converted);
	written = ft_strlen(converted);
	free(converted);
	return (written);
}

size_t	print_uint(t_spec spec, va_list ap)
{
	size_t		written;
	char		*converted;
	intmax_t	arg;

	arg = va_arg(ap, uintmax_t);
	if (spec.len == LEN_NONE)
		arg &= 4294967295;
	else if (spec.len == LEN_HH)
		arg &= 255;
	else if (spec.len == LEN_H)
		arg &= 65535;
	if (spec.type == 'u' || spec.type == 'U')
		converted = ft_itobase(arg, 10, "0123456789");
	else if (spec.type == 'o' || spec.type == 'O')
		converted = ft_itoa_base(arg, 8);
	else if (spec.type == 'x' || spec.type == 'p')
		converted = ft_itoa_base(arg, 16);
	else
		converted = ft_itobase(arg, 16, "0123456789ABCDEF");
	converted = add_padding(converted, spec);
	ft_putstr(converted);
	written = ft_strlen(converted);
	free(converted);
	return (written);
}
