/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:57:14 by alexafer          #+#    #+#             */
/*   Updated: 2023/11/23 15:57:21 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n-- > 0)
		*ptr++ = (unsigned char)c;
	return (s);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n-- > 0)
		*ptr++ = 0;
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char	*ptr_src;
	unsigned char		*ptr_dst;

	if (dst == src)
		return (dst);
	ptr_src = src;
	ptr_dst = dst;
	while (n-- > 0)
		*ptr_dst++ = *ptr_src++;
	return (dst);
}

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	const unsigned char	*ptr_src;
	unsigned char		*ptr_dst;

	if (dst == src)
		return (dst);
	ptr_src = src;
	ptr_dst = dst;
	if (ptr_dst < ptr_src)
		while (n-- > 0)
			*ptr_dst++ = *ptr_src++;
	else
	{
		ptr_src += n - 1;
		ptr_dst += n - 1;
		while (n-- > 0)
			*ptr_dst-- = *ptr_src--;
	}
	return (dst);
}
