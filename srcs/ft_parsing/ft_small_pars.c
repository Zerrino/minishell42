/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_small_pars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:52:29 by alexafer          #+#    #+#             */
/*   Updated: 2024/04/05 18:56:37 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	ft_parser(t_minishell *mini, char *input, t_command	*command)
{
	char		**split;
	int			i;
	int			l;
	int			j;
	int			option;
	int			output;
	int			*array;
	char		*ou;
	int			*array2;
	int			*array_max[2];

//	printf("Parsing : %s\n", input);
	input = converter(mini, input);
	if (ft_empty_par(mini, input))
		return ;
	command->op = 1;
	//ft_printf("nb : %d\n", ft_output_com(mini, input));
	command->op = ft_output_com(mini, input);
	ou = ft_input_dir(mini, input);
	if (ou)
		command->in = ou;
	if (command->op == -1)
		return ;
	//write(command.op, "test\n", 5);
	array = ft_get_arr_com(mini, command, input);
	array2 = ft_get_arr_red(mini, command, input);
	//close(output);
	i = 0;
	split = ft_split(input, ' ');
	i = 0;
	while (split[i] && (ft_in_arr(i, array) || ft_in_arr(i, array2)))
		i++;
	command->command = split[i];
	if (split[i])
		i++;
	if (!split[i])
		command->option = 0;
	l = i;
	while (split[i])
	{
		option = 1;
		j = 0;
		if ((!ft_in_arr(i, array) || !ft_in_arr(i, array2)))
		{
			while (split[i][j] && option)
			{
				if ((j == 0 && split[i][j] == '-'))
					;
				else if (split[i][j] == 'n')
					option = 1;
				else
					option = 0;
				j++;
			}
			if (option == 0)
				break ;
		}
		i++;
	}
	if (i > l)
		command->option = "n";
	else
		command->option = 0;
	array_max[0] = array;
	array_max[1] = array2;
	command->data = ft_get_data(split, command, i, array_max);
	//printf("command : %s\n", command->command);
	//printf("option : %s\n", command->option);
	i = 0;
	while (command->data[i])
	{
		printf("data[%d] : %s\n", i, command->data[i]);
		i++;
	}
	i = 0;
	while (array[i] != -1)
	{
		//printf("array : %d\n", array[i]);
		i++;
	}
	i = 0;
	while (array2[i] != -1)
	{
		//printf("array2 : %d\n", array2[i]);
		i++;
	}
	i = 0;
	while (command->data[i])
	{
		ft_reverse_quote(command->data[i]);
		command->data[i] = ft_rem_quote(command->data[i], 0);
		i++;
	}
	i = 0;
	while (command->data[i])
	{
		printf("data[%d] : %s\n", i, command->data[i]);
		i++;
	}
	command->output_str = 0;
	//printf("in : %s\n", command->in);
	ft_take_action(command, mini);
	//printf("input : %s\n", command->in);
	if ((command->op != 1 || command->next == 0) && command->output_str)
		write(command->op, command->output_str, ft_strlen(command->output_str));
}
