/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:31:08 by alexafer          #+#    #+#             */
/*   Updated: 2024/03/16 19:38:40 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

int	slen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_s(char *str, char c, int n)
{
	int	i;
	int	n_t;

	if (!str)
		return (0);
	n_t = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			n_t++;
		i++;
	}
	if (str[i] == c)
		n_t++;
	if (n_t >= n)
		return (1);
	return (0);
}

char	*ft_emptys1(void)
{
	char	*s1;

	s1 = (char *)malloc(sizeof(char) * 1);
	if (!s1)
		return (0);
	s1[0] = '\0';
	return (s1);
}

char	*ft_noresult(char *s1)
{
	free(s1);
	return (0);
}

char	*ft_make_it_bigger(char *s1, char *s2)
{
	char	*result;
	int		i;
	int		j;

	if (!s1)
		s1 = ft_emptys1();
	if (!s1)
		return (0);
	result = (char *)malloc(sizeof(char) * (slen(s1) + slen(s2) + 1));
	if (!result)
		return (ft_noresult(s1));
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		result[i++] = s2[j++];
	result[i] = '\0';
	free(s1);
	return (result);
}
