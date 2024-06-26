/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 04:16:31 by alexafer          #+#    #+#             */
/*   Updated: 2024/04/11 13:32:17 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

int	cd_home(t_command *com, t_minishell *mini)
{
	char	*str;

	str = converter(mini, ft_strjoin("$HOME", ""));
	if (chdir(str) == -1)
	{
		com->status = 1;
		free(str);
		return (1);
	}
	free(str);
	mini->error = ft_get_path(mini);
	com->status = 0;
	return (0);
}

int	ft_cd(t_command *command, t_minishell *mini)
{
	int	i;

	i = 0;
	if (!command->data || !command->data[0])
	{
		if (cd_home(command, mini) == 1)
			return (ft_printf_error());
		return (0);
	}
	while (command->data[i])
		i++;
	if (i > 1)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		command->status = 1;
		return (1);
	}
	if (chdir(command->data[0]) == -1)
	{
		command->status = 1;
		return (ft_printf_error());
	}
	mini->error = ft_get_path(mini);
	command->status = 0;
	return (mini->error);
}

char	**ft_strstrjoin(char *s1, char **s2)
{
	char	**result;
	int		len;
	int		i;

	len = 0;
	while (s2[len])
		len++;
	result = (char **)malloc(sizeof(char *) * (len + 2));
	if (!result)
		return (0);
	result[0] = ft_strdup(s1);
	i = 1;
	while ((i - 1) < len)
	{
		result[i] = ft_strdup(s2[i - 1]);
		i++;
	}
	result[len + 1] = 0;
	return (result);
}

char	**ft_converter_env(t_env *env)
{
	t_env	*start;
	char	**result;
	int		i;

	start = env;
	i = 0;
	while (start)
	{
		i++;
		start = start->next;
	}
	start = env;
	result = (char **)malloc(sizeof(char *) * (i + 1));
	if (!result)
		return (0);
	i = 0;
	while (start)
	{
		result[i] = ft_strdup(start->env_var);
		i++;
		start = start->next;
	}
	result[i] = 0;
	return (result);
}
