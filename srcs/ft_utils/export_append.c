/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:58:27 by lpetit            #+#    #+#             */
/*   Updated: 2024/04/21 16:21:58 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

int	has_plus_sign(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

t_env	*append_value(t_env *node, char *str)
{
	char	*tmp;

	tmp = str;
	while (*str != '=')
		str++;
	if (has_equal_sign(node->env_var))
		str++;
	str = ft_strjoin(node->env_var, str);
	if (!str)
	{
		free(tmp);
		return (NULL);
	}
	free(node->env_var);
	node->env_var = str;
	node->exp = 1;
	free(tmp);
	return (node);
}

int	export_append(char *str, t_minishell *mini)
{
	t_env	*tmp;
	char	**split;
	char	*join;

	split = ft_split(str, '+');
	join = ft_strjoin(split[0], split[1]);
	if (!join)
		return (1);
	tmp = ft_getenv(mini->env, join, 1);
	ft_free_split(split);
	if (tmp != NULL)
	{
		tmp = append_value(tmp, join);
		if (tmp == NULL)
			return (1);
	}
	else
	{
		tmp = export_new(join, mini);
		free(join);
		if (tmp == NULL)
			return (1);
	}
	return (0);
}
