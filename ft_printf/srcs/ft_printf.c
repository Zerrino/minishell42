/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 00:11:16 by alexafer          #+#    #+#             */
/*   Updated: 2024/03/15 18:57:36 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_act(va_list ap, t_data *data)
{
	if (data->conv == 'd' || data->conv == 'i')
		data->arg_int = va_arg(ap, int);
	if (data->conv == 'x' || data->conv == 'X' || data->conv == 'u')
		data->arg_uint = (unsigned int)va_arg(ap, int);
	if (data->conv == 's')
		data->arg_str = va_arg(ap, char *);
	if (data->conv == 'c')
		data->arg_char = (char)va_arg(ap, int);
	if (data->conv == 'p')
		data->arg_void = va_arg(ap, void *);
}

void	ft_actual_print(va_list ap, t_data *data, int w)
{
	if (!w)
		ft_act(ap, data);
	if (data->len_conv != -1)
	{
		if (data->conv == 'd' || data->conv == 'i')
			ft_putdigit(data->arg_int, data, w);
		if (data->conv == 'x')
			ft_puthexa_l(data->arg_uint, data, w);
		if (data->conv == 'X')
			ft_puthexa_u(data->arg_uint, data, w);
		if (data->conv == 's')
			ft_putstring(data->arg_str, data, w);
		if (data->conv == 'u')
			ft_putuint(data->arg_uint, data, w);
		if (data->conv == 'c')
			data->len += write(1, &data->arg_char, w);
		if (data->conv == 'p')
			ft_putadd(data->arg_void, data, w);
		if (data->conv == '%')
			data->len += write(1, "%", w);
	}
}

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	t_data	data;

	data.len = 0;
	va_start(ap, fmt);
	ft_parse(ap, fmt, &data);
	va_end(ap);
	return (data.len);
}
