/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_tilde.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:01:12 by lpetit            #+#    #+#             */
/*   Updated: 2024/04/04 14:48:03 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static char	*ft_charjoin_f(char *s1, char c)
{
	size_t	s1_size;
	char	*join;

	if (!s1)
		return (NULL);
	s1_size = ft_strlen(s1);
	join = (char *)malloc(((s1_size + 1) + 1) * sizeof(char));
	if (!join)
		return (NULL);
	ft_strlcpy(join, s1, s1_size + 1);
	join[s1_size] = c;
	join[s1_size + 1] = '\0';
	free(s1);
	return (join);
}

static char	*get_env_value(char *str, t_env *env)
{
	t_env	*node;
	char	*tmp;
	size_t	i;

	i = 0;
	if (str[1] != '\0' && str[1] != ' ' && str[1] != '/')
		return (NULL);
	node = ft_getenv(env, "HOME", 1);
	if (!node)
		return (NULL);
	tmp = node->env_var;
	while (*tmp != '=')
		tmp++;
	tmp++;
	return (tmp);
}

char	*converter_tilde(t_minishell *mini, char *str)
{
	char	*new;
	char	*env_value;
	char	*tmp;

	tmp = str;
	new = ft_strdup("");
	while (*tmp)
	{
		if (*tmp && *tmp == '~')
		{
			env_value = get_env_value(tmp, mini->env);
			if (env_value != NULL)
			{
				new = ft_strjoin_f(new, env_value);
				tmp++;
			}
		}
		if (*tmp)
		{
			new = ft_charjoin_f(new, *tmp);
			tmp++;
		}
	}
	free(str);
	return (new);
}
