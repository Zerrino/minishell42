/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_6.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:13:28 by alexafer          #+#    #+#             */
/*   Updated: 2024/03/15 18:14:18 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_first_digit(int nb)
{
	if (nb < 0)
		nb = -nb;
	while (nb > 9)
		nb /= 10;
	return (nb);
}

int	ft_last_digit(int nb)
{
	int	i;

	i = 0;
	while (nb > 9)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

int	ft_return_last(const char *fmt)
{
	int	i;

	i = 0;
	while (fmt[i] && (fmt[i] >= '0' && fmt[i] <= '9'))
		i++;
	return (i);
}

void	ft_parse(va_list ap, const char *fmt, t_data *data)
{
	while (*fmt)
	{
		if (*fmt == '%')
			fmt += ft_arguments(ap, fmt, data);
		else
			data->len += write(1, fmt, 1);
		fmt++;
	}
}
