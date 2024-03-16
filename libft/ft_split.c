/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:58:40 by alexafer          #+#    #+#             */
/*   Updated: 2023/11/23 15:58:41 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_charset(char c, char charset)
{
	return (c == charset);
}

static int	ft_count_words(char const *str, char charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && ft_is_charset(str[i], charset))
			i++;
		if (str[i] && !ft_is_charset(str[i], charset))
			count++;
		while (str[i] && !ft_is_charset(str[i], charset))
			i++;
	}
	return (count);
}

static char	*ft_substring(char const *str, int start, int len)
{
	char	*sub;
	int		i;

	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (0);
	i = 0;
	while (i < len)
	{
		sub[i] = str[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

static char	**ft_free(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (0);
}

char	**ft_split(char const *str, char charset)
{
	int		i[4];
	char	**result;

	if (!str)
		return (0);
	i[0] = 0;
	i[1] = 0;
	i[3] = ft_count_words(str, charset);
	result = (char **)malloc(sizeof(char *) * (i[3] + 1));
	if (!result)
		return (0);
	while (i[1] < i[3] && result)
	{
		while (str[i[0]] && ft_is_charset(str[i[0]], charset))
			i[0]++;
		i[2] = i[0];
		while (str[i[0]] && !ft_is_charset(str[i[0]], charset))
			i[0]++;
		result[i[1]] = ft_substring(str, i[2], i[0] - i[2]);
		if (!result[i[1]])
			return (ft_free(result));
		i[1]++;
	}
	result[i[1]] = 0;
	return (result);
}
