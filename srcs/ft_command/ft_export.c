/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:21:47 by lpetit            #+#    #+#             */
/*   Updated: 2024/03/29 13:46:52 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

/*char	*get_key(char **data)
{
	char	*key;
	int	i;

	i = 0;
	ft_strlcpy(key, data[1], ft_strlen(data[1]));
	while (key[i] != '=')
		i++;
	key[i] = '\0';
	return (key);
}*/

t_env	*ft_getenv(t_env *env, char *str)
{
	t_env	*tmp;
	size_t	i;

	tmp = env;
	while (tmp != NULL)
	{
		i = 0;
		while (tmp->env_var[i] == str[i])
		{
			if (tmp->env_var[i] == '=')
				return (tmp);
			i++;
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_export(t_command *com, t_minishell *mini)
{
	t_env	*tmp;

	tmp = ft_getenv(mini->env, com->data[0]);
	if (tmp != NULL)
	{
		if (update_node(tmp, com->data[0]) != 0)
		{
			ft_clearlst(mini->env);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		tmp = mini->env;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = ft_newnode(com->data[0]);
	}
	return (0);
}
