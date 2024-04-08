/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:12:22 by alexafer          #+#    #+#             */
/*   Updated: 2024/03/15 18:56:48 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_fill_minus(int len, t_data *data)
{
	while (len < data->flag_minus_len)
	{
		data->len += write(1, " ", 1);
		len++;
	}
}

void	ft_fill_zero(t_data *data)
{
	int	i;
	int	len;

	i = 0;
	len = data->flag_zero_len - data->len_wr;
	if (data->flag_dot && data->flag_zero && ft_is_digit(data))
	{
		while (i < data->flag_zero_len)
		{
			ft_write("0", data, 1, -1);
			i++;
		}
	}
	else if (data->flag_zero)
	{
		while (i < len)
		{
			ft_write("0", data, 1, -1);
			i++;
		}
	}
}

void	ft_putadd(void *add, t_data *data, int w)
{
	unsigned long	address;
	char			*hex;
	int				i;
	int				j;

	hex = "0123456789abcdef";
	address = (unsigned long)add;
	if (!add)
	{
		ft_write("0", data, w, -1);
		return ;
	}
	i = ft_count_digit(address);
	while (i)
	{
		address = (unsigned long)add;
		j = i;
		while (j-- - 1)
			address /= 16;
		ft_write(&(hex[address % 16]), data, w, 1);
		i--;
	}
}

void	ft_putstring(char *str, t_data *data, int w)
{
	if (!str)
		str = "(null)";
	ft_write(str, data, w, -1);
}

void	ft_putchart(char c, t_data *data, int w)
{
	char	two[2];

	two[0] = c;
	two[1] = '\0';
	ft_write(two, data, w, 1);
}
