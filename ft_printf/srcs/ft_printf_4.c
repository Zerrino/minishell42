/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:11:18 by alexafer          #+#    #+#             */
/*   Updated: 2024/03/15 19:01:10 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_fill_correct(t_data *data)
{
	int	i;

	i = 1;
	while (i < data->flag_dot_len)
	{
		ft_write(" ", data, 1, -1);
		i++;
	}
}

void	ft_fillx(t_data *data)
{
	if (data->conv == 'p')
	{
		data->len += write(1, "0x", 2);
	}
	else if (data->flag_hastag)
	{
		if (data->arg_uint)
		{
			if (data->conv == 'X')
			{
				data->len += write(1, "0X", 2);
			}
			if (data->conv == 'x')
			{
				data->len += write(1, "0x", 2);
			}
		}
	}
}

void	ft_fill_sign(t_data *data)
{
	if (data->conv == 'd' || data->conv == 'i')
	{
		if (data->arg_int >> ((sizeof(int) * 8) - 1))
			ft_write("-", data, 1, -1);
		else if (data->flag_plus)
			ft_write("+", data, 1, -1);
		else if (data->flag_space)
			ft_write(" ", data, 1, -1);
	}
}

void	ft_fill_tot(int tot, t_data *data, int w)
{
	int	i;

	i = 0;
	while (i < tot)
	{
		ft_write(" ", data, w, -1);
		i++;
	}
}

void	ft_fill_dot_int(t_data *data)
{
	int	i;
	int	len;

	i = 0;
	len = data->flag_dot_len - data->len_wr;
	while (i < len)
	{
		ft_write("0", data, 1, -1);
		i++;
	}
}
