/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:24:38 by alexafer          #+#    #+#             */
/*   Updated: 2024/04/02 17:21:50 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	ft_take_action(t_command *com, t_minishell *mini)
{
	if (!ft_strncmp("echo", com->command, 5))
		ft_echo(com);
	//else if (!ft_strncmp("pwd", com->command, ft_strlen(com->command)))
	//	ft_printf("%s\n", mini->path);
	//else if (!ft_strncmp("cd", com->command, ft_strlen(com->command)))
	//	ft_cd(com, mini);
	//else if (!ft_strncmp("env", com->command, ft_strlen(com->command)))
	//	ft_env(mini);
	else if (!ft_strncmp("pwd", com->command, ft_strlen(com->command)))
		ft_printf("%s\n", mini->path);
	else if (!ft_strncmp("cd", com->command, ft_strlen(com->command)))
		ft_cd(com, mini);
	else if (!ft_strncmp("env", com->command, ft_strlen(com->command)))
		com->status = ft_env(mini->env);
	else if (!ft_strncmp("export", com->command, ft_strlen(com->command)))
		com->status = ft_export(com, mini);
	else if (!ft_strncmp("unset", com->command, ft_strlen(com->command)))
		com->status = ft_unset(com, mini);
	else if (!ft_strncmp("test", com->command, ft_strlen(com->command)))
		test_converter(mini, com);
	else
		ft_error_msg(com->command);
}
