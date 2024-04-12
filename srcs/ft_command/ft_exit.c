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

	current = env;
	while (current)
	{
		next = current->next;
		free(current->env_var);
		free(current);
		current = next;
	}
}


/*
	char	*program_name;
	char	*prompt;
	char	*folder;
	char	*start_path;
	char	*path;
	char	*line;
	*/

int	ft_exit(t_minishell *mini, t_command *com)
{
	printf("EXIT ENTER\n");
	/*
	free(mini->program_name);
	free(mini->prompt);
	free(mini->start_path);
	free(mini->path);
	free(mini->line);
	*/
	//free(mini->input);
	clear_history();
	ft_free_env_list(mini->env);
	ft_free_split(com->data);
	exit(0);
}
