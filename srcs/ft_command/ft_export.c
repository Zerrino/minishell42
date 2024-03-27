/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:21:47 by lpetit            #+#    #+#             */
/*   Updated: 2024/03/26 19:31:40 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

char	*get_key(char **data)
{
	char	*key;
	int	i;

	i = 0;
	ft_strlcpy(key, data[1], ft_strlen(data[1]));
	while (key[i] != '=')
		i++;
	key[i] = '\0';
	return (key);
}

int	ft_export(t_command *com, t_minishell *mini)
{
	
	if (getenv(get_key(com->data)) != NULL)
		update value
	else
		create env
	return (0);
}
