/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:24:38 by alexafer          #+#    #+#             */
/*   Updated: 2024/03/24 23:18:34 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	ft_take_action(t_command *com, t_minishell *mini)
{
	if (!ft_strncmp("echo", com->command, ft_strlen(com->command)))
		ft_echo(com);
	else if (!ft_strncmp("pwd", com->command, ft_strlen(com->command)))
		ft_printf("%s", mini->path);
	else if (!ft_strncmp("cd", com->command, ft_strlen(com->command)))
		ft_cd(com, mini);
	else
		ft_error_msg(com->command);
}
