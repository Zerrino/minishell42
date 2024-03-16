/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_7.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:14:35 by alexafer          #+#    #+#             */
/*   Updated: 2024/03/15 18:54:54 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_arg_up(char c, t_data *data)
{
	if (c == ' ')
		data->flag_space = 1;
	else if (c == '+')
		data->flag_plus = 1;
	else if (c == '#')
		data->flag_hastag = 1;
}

void	ft_up_more(const char *fmt, t_data *data, int *i)
{
	if (fmt[*i] == '-')
	{
		data->flag_minus = 1;
		if (ft_atoi_f(&fmt[*i + 1]) > data->flag_minus_len)
			data->flag_minus_len = ft_atoi_f(&fmt[*i + 1]);
		*i += ft_return_last(&fmt[*i + 1]);
	}
	else if (fmt[*i] == '.')
	{
		data->flag_dot = 1;
		if (ft_atoi_f(&fmt[*i + 1]) > data->flag_dot_len)
			data->flag_dot_len = ft_atoi_f(&fmt[*i + 1]);
		if (!data->flag_dot_len)
			data->flag_dot_len = 1;
		*i += ft_return_last(&fmt[*i + 1]);
	}
	else if (fmt[*i] == '0')
	{
		data->flag_zero = 1;
		if (ft_atoi_f(&fmt[*i + 1]) > data->flag_zero_len)
			data->flag_zero_len = ft_atoi_f(&fmt[*i + 1]);
		*i += ft_return_last(&fmt[*i + 1]);
	}
}

void	ft_lentilarg(const char *fmt, t_data *data)
{
	int	i;

	i = 1;
	while (fmt[i] && !ft_char_in_arg(fmt[i]))
	{
		ft_arg_up(fmt[i], data);
		ft_up_more(fmt, data, &i);
		i++;
	}
	data->len_conv = i;
	if (!fmt[i])
		data->len_conv = -1;
	data->conv = fmt[i];
}
