/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:09:21 by alexafer          #+#    #+#             */
/*   Updated: 2024/03/15 18:10:24 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_atoi_f(const char *str)
{
	int		i;
	long	result;
	long	last;
	int		sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		last = result;
		result = (result * 10) + (str[i++] - '0');
		if (result < last)
			return (~sign >> 1);
	}
	return ((int)result * sign);
}

int	ft_write(char *str, t_data *data, int w, int max)
{
	int	i;

	i = 0;
	if (data->flag_dot)
	{
		while (str[i] && i < data->flag_dot_len && i != max)
		{
			data->len += write(1, &str[i], w);
			data->len_wr++;
			i++;
		}
	}
	else
	{
		while (str[i] && i != max)
		{
			data->len += write(1, &str[i], w);
			data->len_wr++;
			i++;
		}
	}
	return (0);
}

void	ft_reset_flags(t_data *data)
{
	data->flag_space = 0;
	data->flag_plus = 0;
	data->flag_hastag = 0;
	data->flag_minus = 0;
	data->flag_zero = 0;
	data->flag_dot = 0;
	data->flag_minus_len = 0;
	data->flag_zero_len = 0;
	data->flag_dot_len = 0;
}

int	ft_char_in_arg(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i')
		return (1);
	if (c == 'u' || c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

int	ft_is_digit(t_data *data)
{
	char	c;

	c = data->conv;
	if (c == 'p' || c == 'd' || c == 'i' || c == 'u')
		return (1);
	if (c == 'u' || c == 'x' || c == 'X')
		return (1);
	return (0);
}
