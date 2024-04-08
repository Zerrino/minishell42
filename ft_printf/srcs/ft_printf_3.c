/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:09:53 by alexafer          #+#    #+#             */
/*   Updated: 2024/03/15 19:00:58 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_spi(va_list ap, const char *fmt, t_data *data)
{
	ft_reset_flags(data);
	ft_lentilarg(fmt, data);
	ft_actual_print(ap, data, 0);
	ft_fillx(data);
}

void	ft_spi2(t_data *data, int *i)
{
	int	tot;

	if (data->flag_dot && data->flag_zero && !data->flag_minus)
	{
		tot = data->flag_zero_len - data->flag_dot_len;
		*i = 1;
		if (data->flag_dot_len <= data->len_wr)
			*i = data->len_wr - data->flag_dot_len + 1;
		while (*i++ < tot)
			data->len += write(1, " ", 1);
		data->flag_dot_len++;
	}
	ft_fill_sign(data);
	if (data->flag_dot)
		ft_fill_dot_int(data);
	if (!data->flag_dot && data->flag_zero && !data->flag_minus)
		ft_fill_zero(data);
}

int	ft_arguments(va_list ap, const char *fmt, t_data *data)
{
	int	len;
	int	i;

	data->len_wr = 0;
	len = data->len;
	ft_spi(ap, fmt, data);
	if (ft_is_digit(data))
		ft_spi2(data, &i);
	else
	{
		ft_fill_sign(data);
		if (!data->flag_minus)
			ft_fill_zero(data);
	}
	ft_actual_print(ap, data, 1);
	len = data->len - len;
	ft_fill_minus(len, data);
	return (data->len_conv);
}
