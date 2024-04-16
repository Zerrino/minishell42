/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:24:38 by alexafer          #+#    #+#             */
/*   Updated: 2024/04/16 14:26:23 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static void	ft_take_action_2(t_command *com, t_minishell *mini, int nom)
{
	if (!ft_strncmp("export", com->command, ft_strlen("export")))
	{
		if (nom)
			com->status = ft_export(com, mini);
	}
	else if (!ft_strncmp("unset", com->command, ft_strlen("unset")))
	{
		if (nom)
			com->status = ft_unset(com, mini);
	}
	else if (!ft_strncmp("exit", com->command, ft_strlen("exit")))
	{
		if (nom)
			com->status = ft_exit(mini, com);
	}
	else
		com->found = 0;
}

void	ft_take_action(t_command *com, t_minishell *mini, int nom)
{
	com->found = 1;
	if (!ft_strncmp("echo", com->command, 5))
		ft_echo(com);
	else if (!ft_strncmp("pwd", com->command, ft_strlen("pwd")))
		com->output_str = ft_strjoin(mini->path, "\n");
	else if (!ft_strncmp("cd", com->command, ft_strlen("cd")))
	{
		if (nom)
			ft_cd(com, mini);
	}
	else if (!ft_strncmp("env", com->command, ft_strlen("env")))
		com->status = ft_env(mini->env, com);
	else
		ft_take_action_2(com, mini, nom);
}
