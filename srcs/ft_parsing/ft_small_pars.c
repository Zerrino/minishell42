/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_small_pars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:52:29 by alexafer          #+#    #+#             */
/*   Updated: 2024/04/08 20:45:28 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	ext(t_minishell *mini, t_command *command, char *input)
{
	char	**split;
	//char	**split2;
	int		*a[2];
	int		i;
	int		l;

	a[0] = ft_get_arr_com(mini, command, input);
	a[1] = ft_get_arr_red(mini, command, input);
	split = ft_split_str(input, " ");
	i = 0;
	while (split[i] && (ft_in_arr(i, a[0]) || ft_in_arr(i, a[1])))
		i++;
	set_command_data(command, split, &i);
	l = i;
	find_option(split, command, a, &i);
	if (i > l)
		command->option = "n";
	else
		command->option = 0;
	proc(command, split, i, a);
	ft_free_split(split);
	free(a[0]);
	free(a[1]);
	free(input);
}

void	set_command_data(t_command *command, char **split, int *i)
{
	command->command = ft_strdup(split[*i]);
	if (split[*i])
		(*i)++;
	if (!split[*i])
		command->option = 0;
}

void	find_option(char **split, t_command *command, int **array_max, int *i)
{
	int	option;
	int	j;

	(void)command;
	while (split[*i])
	{
		option = 1;
		j = 0;
		if (!ft_in_arr(*i, array_max[0]) || !ft_in_arr(*i, array_max[1]))
		{
			while (split[*i][j])
			{
				if (j == 0 && split[*i][j] == '-')
					;
				else if (split[*i][j] == 'n')
					option = 1;
				else
					option = 0;
				j++;
			}
			if (option == 0)
				break ;
		}
		(*i)++;
	}
}

void	proc(t_command *command, char **split, int start_index, int **array_max)
{
	int	i;

	command->data = ft_get_data(split, command, start_index, array_max);
	i = 0;
	while (command->data[i])
	{
		ft_reverse_quote(command->data[i]);
		command->data[i] = ft_rem_quote(command->data[i], 0);
		i++;
	}
	command->output_str = 0;
}

void	ft_parser(t_minishell *mini, char *input, t_command *command, int nom)
{
	parser_init(mini, &input, command);
	if (!(command->op != -1))
		return ;
	ext(mini, command, input);
	ft_take_action(command, mini, nom);
}
