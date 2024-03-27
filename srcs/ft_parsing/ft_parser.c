/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:47:31 by alexafer          #+#    #+#             */
/*   Updated: 2024/03/27 20:32:43 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"
#include <fcntl.h>

int	ft_empty_par(t_minishell *mini, char *input)
{
	if (!input)
	{
		mini->stop = 1;
		return (1);
	}
	if (input[0] == 0)
		return (1);
	return (0);
}

int	ft_redir_right(char *folder_name, int doub)
{
	int	fd_nb;
	char	*str;
	fd_nb = 1;
	if (!folder_name || !folder_name[0] || ft_strchr(folder_name, '>'))
		return (-1);
	if (doub == 1)
	{
		fd_nb = open(folder_name, O_RDWR);
		while (get_next_line(fd_nb))
			;
	}
	else if (doub == 0)
		fd_nb = open(folder_name, O_RDWR ,O_TRUNC);
	if (fd_nb == -1)
	{
		fd_nb = open(folder_name, O_CREAT);
		if (fd_nb == -1)
			return (ft_printf_error());
		close(fd_nb);
		fd_nb = open(folder_name, O_WRONLY);
	}
	return (fd_nb);
}

int	ft_output_com(t_minishell *mini, char *input)
{
	char	**splited;
	int		i;
	int		doub;
	int		output;

	i  = 0;
	doub = 0;
	output = 1;
	while (input[i])
	{
		if (input[i] == '>')
		{
			doub = 0;
			if (output != 1)
				close(output);
			if (input[i + 1] == '>')
			{
				doub = 1;
				i++;
			}
			splited = ft_split(&input[i + 1], ' ');
			output = ft_redir_right(splited[0], doub);
			ft_free_split(splited);
			if (output == -1)
				return (-1);
			//printf("output : %d\n", output);
		}
		i++;
	}
	return (output);
}

int	*ft_get_arr_com(t_minishell *mini, t_command *command, char *input)
{
	char	**splited;
	int		*array;
	int		i;
	int		j;
	int		nb;
	int		x;

	nb = 0;
	i  = 0;
	splited = ft_split(input, ' ');
	while (splited[i])
	{
		if (ft_strchr(splited[i], '>'))
		{
			x = 0;
			if (splited[i][1] == '>')
				x = 1;
			if (!splited[i][1 + x])
				nb++;
			nb++;
		}
		i++;
	}
	array = (int *)malloc(sizeof(int) * (nb + 1));
	if (!array)
		return (0);
	i = 0;
	x = 0;
	j = 0;
	while (splited[i])
	{
		if (ft_strchr(splited[i], '>'))
		{
			x = 0;
			if (splited[i][1] == '>')
				x = 1;
			if (!splited[i][1 + x])
			{
				array[j] = i + 1;
				j++;
			}
			array[j] = i;
			j++;
		}
		i++;
	}
	array[j] = -1;
	return (array);
}

int	ft_in_arr(int nb, int *array)
{
	int	i;

	i = 0;
	while (array[i] != -1)
	{
		if (nb == array[i])
			return (1);
		i++;
	}
	return (0);
}

char	**ft_get_data(char **split, t_command *command, int l, int *array)
{
	char	**result;
	int		i;
	int		j;

	i = l;
	j = 0;
	while (split[i])
	{
		if (!ft_in_arr(i, array))
			j++;
		i++;
	}
	result = (char **)malloc(sizeof(char *) * (j + 1));
	if (!result)
		return (0);
	i = l;
	j = 0;
	while (split[i])
	{
		if (!ft_in_arr(i, array))
		{
			result[j] = split[i];
			j++;
		}
		i++;
	}
	result[j] = 0;
	return (result);
}


void	ft_parser(t_minishell *mini, char *input)
{
	t_command	command;
	char		**split;
	int			i;
	int			l;
	int			j;
	int			option;
	int			output;
	int			*array;

//	printf("Parsing : %s\n", input);
	if (ft_empty_par(mini, input))
		return ;
	command.op = 1;
	//ft_printf("nb : %d\n", ft_output_com(mini, input));
	command.op = ft_output_com(mini, input);
	if (command.op == -1)
		return ;
	//write(command.op, "test\n", 5);
	array = ft_get_arr_com(mini, &command, input);
	//close(output);
	i = 0;
	split = ft_split(input, ' ');
	i = 0;
	while (split[i] && ft_in_arr(i, array))
		i++;
	command.command = split[i];
	i++;
	if (!split[i])
		command.option = 0;
	l = i;
	while (split[i])
	{
		option = 1;
		j = 0;
		if (!ft_in_arr(i, array))
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
		command.option = "n";
	else
		command.option = 0;
	command.data = ft_get_data(split, &command, i, array);
	/*
	//printf("command : %s\n", command.command);
	//printf("option : %s\n", command.option);
	i = 0;
	while (command.data[i])
	{
		printf("data[%d] : %s\n", i, command.data[i]);
		i++;
	}
	*/
	ft_take_action(&command, mini);
	write(command.op, command.output_str, ft_strlen(command.output_str));
}

