/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:47:31 by alexafer          #+#    #+#             */
/*   Updated: 2024/03/30 03:14:21 by alexafer         ###   ########.fr       */
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

char	*ft_redir_left(char *folder_name, int doub)
{
	int	fd_nb;
	int	i;
	char	*str;
	char	*result;

	if (!folder_name || !folder_name[0] || ft_strchr(folder_name, '>'))
		return (0);
	if (doub == 1)
	{
		str = get_next_line(0);
		folder_name = ft_strjoin(folder_name, "\n");
		result = ft_calloc(1, sizeof(char));
		while (ft_strncmp(folder_name, str, ft_strlen(str)))
		{
			result = ft_strjoin_f(result, str);
			free(str);
			str = get_next_line(0);
		}
		free(str);
		result = ft_strjoin(result, "\0");
		//i = 0;
		//while (result[i])
		//	i++;
		//result[i - 1] = 0;
	}
	else
	{
		fd_nb = open(folder_name, O_RDONLY);
		if (fd_nb == -1)
		{
			ft_printf_error();
			return (0);
		}
		str = get_next_line(fd_nb);
		result = ft_calloc(1, sizeof(char));
		while (str)
		{
			result = ft_strjoin_f(result, str);
			free(str);
			str = get_next_line(fd_nb);
		}
		free(str);
		result = ft_strjoin_f(result, "\0");
		close(fd_nb);
	}
	return (result);
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
		}
		i++;
	}
	return (output);
}

char	*ft_input_dir(t_minishell *mini, char *input)
{
	char	**splited;
	int		i;
	int		doub;
	char	*output;

	i  = 0;
	doub = 0;
	output = 0;
	while (input[i])
	{
		if (input[i] == '<')
		{
			doub = 0;
			if (input[i + 1] == '<')
			{
				doub = 1;
				i++;
			}
			splited = ft_split(&input[i + 1], ' ');
			if (output)
				free(output);
			output = ft_redir_left(splited[0], doub);
			ft_free_split(splited);
			if (output == 0)
				return (0);
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

int	*ft_get_arr_red(t_minishell *mini, t_command *command, char *input)
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
		if (ft_strchr(splited[i], '<'))
		{
			x = 0;
			if (splited[i][1] == '<')
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
		if (ft_strchr(splited[i], '<'))
		{
			x = 0;
			if (splited[i][1] == '<')
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

char	**ft_get_data(char **split, t_command *command, int l, int *array, int *array2)
{
	char	**result;
	int		i;
	int		j;

	i = l;
	j = 0;
	while (split[i])
	{
		if (!ft_in_arr(i, array) && !ft_in_arr(i, array2))
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
		if (!ft_in_arr(i, array) && !ft_in_arr(i, array2))
		{
			result[j] = split[i];
			j++;
		}
		i++;
	}
	result[j] = 0;
	return (result);
}


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

//	printf("Parsing : %s\n", input);
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
	command->data = ft_get_data(split, command, i, array, array2);
	//printf("command : %s\n", command->command);
	//printf("option : %s\n", command->option);
	i = 0;
	while (command->data[i])
	{
		//printf("data[%d] : %s\n", i, command->data[i]);
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
	command->output_str = 0;
	//printf("in : %s\n", command->in);
	ft_take_action(command, mini);
	//printf("input : %s\n", command->in);
	if ((command->op != 1 || command->next == 0) && command->output_str)
		write(command->op, command->output_str, ft_strlen(command->output_str));
}

void	ft_all_parser(t_minishell *mini, char *input)
{
	t_command	*command;
	char	**splited;
	int		i;
	int		max;

	if (ft_empty_par(mini, input))
		return ;
	i  = 0;
	splited = ft_split(input, '|');
	while (splited[i])
		i++;
	max = i;
	command = (t_command *)malloc(sizeof(t_command) * (i));
	if (!command)
		return ;
	i = 0;
	while (i < max)
	{
		command[i].in = 0;
		command[i].next = 1;
		if (i + 1 == max)
			command[i].next = 0;
		if (i > 0)
		{
			if (command[i - 1].next == 1)
				command[i].in = command[i - 1].output_str;
		}
		ft_parser(mini, splited[i], &command[i]);
		if (mini->stop)
			return ;
		i++;
	}
	//ft_parser(mini, input, &command);
}
