/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:04:55 by lpetit            #+#    #+#             */
/*   Updated: 2024/04/16 23:18:39 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	ft_free_env_list(t_env *env)
{
	t_env	*current;
	t_env	*next;

	//printf("exit\n");
	current = env;
	while (current)
	{
		next = current->next;
		free(current->env_var);
		free(current);
		current = next;
	}
}

int	check_exit_arg_nbr(t_command *com)
{
	if (com->data[1] != NULL)
	{
		write(2, "exit: too many arguments\n", 25);
		return(1);
	}
	else
		return (0);
}

int	check_exit_arg_value(t_command *com)
{
	size_t	i;

	i = 0;
	if (com->data[0] == NULL)
		return (0);
	while (com->data[0][i])
	{
		if (!(ft_isdigit(com->data[0][i])))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(com->data[0], 2);
			ft_putstr_fd(":numeric argument required\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_exit(t_minishell *mini, t_command *com)
{
	int	ret;

	if (com->data[0] != NULL)
		ret = ft_atoi(com->data[0]);
	else
		ret = mini->status_com % 255;
	write(1, "exit\n", 5);
	if (check_exit_arg_value(com))
		ret = 2;
	else if (check_exit_arg_nbr(com))
		return (1);
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
	exit(ret);
}
