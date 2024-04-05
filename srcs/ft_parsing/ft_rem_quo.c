/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rem_quo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:41:00 by alexafer          #+#    #+#             */
/*   Updated: 2024/04/05 17:45:32 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

char	*ft_rem_quote(char *str, int f)
{
	int	len;
	int	count;
	int	i;
	int	j;
	int	quote;
	char	*result;

	len = ft_strlen(str);
	quote = 0;
	count = 0;
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
	result = (char *)malloc(sizeof(char) * (len - count + 1));
	if (!result)
		return (0);
	i = 0;
	j = 0;
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
	if (f)
		free(str);
	return (result);
}
