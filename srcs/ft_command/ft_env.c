/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:17:05 by lpetit            #+#    #+#             */
/*   Updated: 2024/04/11 13:54:19 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static char	*ft_charjoin_f(char *s1, char c)
{
	size_t	s1_size;
	char	*join;

	if (!s1)
		return (NULL);
	s1_size = ft_strlen(s1);
	join = (char *)malloc(((s1_size + 1) + 1) * sizeof(char));
	if (!join)
	{
		free(s1);
		return (NULL);
	}
	ft_strlcpy(join, s1, s1_size + 1);
	join[s1_size] = c;
	join[s1_size + 1] = '\0';
	free(s1);
	return (join);
}

int	ft_env(t_env *env, t_command *com)
{
	t_env	*tmp;
	char	*str;

	tmp = env;
	if (!tmp)
		return (1);
	str = ft_strdup("");
	if (!str)
		return (1);
	while (tmp != NULL)
	{
		str = ft_strjoin_f(str, tmp->env_var);
		str = ft_charjoin_f(str, '\n');
		tmp = tmp->next;
	}
	if (!str)
		return (1);
	com->output_str = str;
	return (0);
}
