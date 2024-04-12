/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_tilde.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:01:12 by lpetit            #+#    #+#             */
/*   Updated: 2024/04/05 20:25:29 by lpetit           ###   ########.fr       */
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

static char	*join_value(char *new, char *str, t_minishell *mini)
{
	char	*env_value;
	char	*tmp;

	if (!new)
		return (NULL);
	tmp = new;
	env_value = get_env_value(str, mini->env);
	if (env_value != NULL)
		new = ft_strjoin_f(new, env_value);
	if (!new)
		free(tmp);
	return (new);
}

char	*converter_tilde(t_minishell *mini, char *str)
{
	char	*new;
	char	*tmp;

	tmp = str;
	new = ft_strdup("");
	while (*tmp)
	{
		if (*tmp && *tmp == '~')
		{
			new = join_value(new, tmp, mini);
			tmp++;
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
