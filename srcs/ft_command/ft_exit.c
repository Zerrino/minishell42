/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:04:55 by lpetit            #+#    #+#             */
/*   Updated: 2024/04/04 15:12:01 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	ft_free_env_list(t_env *env)
{
	t_env	*current;
	t_env	*next;

	printf("exit\n");
	current = env;
	while (current)
	{
		next = current->next;
		free(current->env_var);
		free(current);
		current = next;
	}
}

int	ft_exit(t_minishell *mini, t_command *com, int i)
{
	if (com)
	{
		free(com->command);
		if (com->data)
			ft_free_split(com->data);
	}
	free(mini->path);
	free(mini->start_path);
	free(mini->input_1);
	rl_clear_history();
	ft_free_env_list(mini->env);
	exit(i);
}
