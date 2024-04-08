/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:09:31 by alexafer          #+#    #+#             */
/*   Updated: 2024/03/15 19:19:48 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_putdigit(int nb, t_data *data, int w)
{
	char	*base;

	base = "0123456789";
	if (nb == -2147483648)
	{
		ft_write(&base[2 % 10], data, w, 1);
		ft_putdigit(147483648, data, w);
	}
	else
	{
		if (nb < 0)
			nb = -nb;
		if (nb > 9)
			ft_putdigit(nb / 10, data, w);
		ft_write(&base[nb % 10], data, w, 1);
	}
	return (0);
}

void	ft_puthexa_l(unsigned int nb, t_data *data, int w)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (nb > 15)
		ft_puthexa_l(nb / 16, data, w);
	ft_write(&hex[nb % 16], data, w, 1);
}

void	ft_puthexa_u(unsigned int nb, t_data *data, int w)
{
	char	*hex;

	hex = "0123456789ABCDEF";
	if (nb > 15)
		ft_puthexa_u(nb / 16, data, w);
	ft_write(&hex[nb % 16], data, w, 1);
}

void	ft_putuint(unsigned int nb, t_data *data, int w)
{
	char	*base;

	base = "0123456789";
	if (nb > 9)
		ft_putuint(nb / 10, data, w);
	ft_write(&base[nb % 10], data, w, 1);
}

int	ft_count_digit(unsigned long nb)
{
	int	i;

	i = 0;
	while (nb)
	{
		nb /= 16;
		i++;
	}
	return (i);
}
