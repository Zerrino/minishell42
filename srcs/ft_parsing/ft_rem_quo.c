/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rem_quo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:41:00 by alexafer          #+#    #+#             */
/*   Updated: 2024/04/05 18:35:26 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static	int	ft_rem_count(char *str, int len)
{
	int	i;
	int	quote;
	int	count;

	count = 0;
	i = 0;
	quote = 0;
	while (i < len)
	{
		if ((quote == 0 || quote == 1) && str[i] == '"')
		{
			quote = !quote;
			count++;
		}
		else if ((quote == 0 || quote == 2) && str[i] == 39)
		{
			if (!quote)
				quote = 2;
			else
				quote = 0;
			count++;
		}
		i++;
	}
	return (count);
}

static	char	*ft_rem_count_2(char *str, char *result, int len, int j)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (i < len)
	{
		if ((quote == 0 || quote == 1) && str[i] == '"')
		{
			quote = !quote;
		}
		else if ((quote == 0 || quote == 2) && str[i] == 39)
		{
			if (!quote)
				quote = 2;
			else
				quote = 0;
		}
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

char	*ft_rem_quote(char *str, int f)
{
	char	*result;
	int		len;
	int		count;
	int		j;

	len = ft_strlen(str);
	count = ft_rem_count(str, len);
	result = (char *)malloc(sizeof(char) * (len - count + 1));
	if (!result)
		return (0);
	j = 0;
	result = ft_rem_count_2(str, result, len, j);
	if (f)
		free(str);
	return (result);
}
