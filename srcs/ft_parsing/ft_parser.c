/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:47:31 by alexafer          #+#    #+#             */
/*   Updated: 2024/04/08 21:33:25 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	child_process(t_pipeline_data *data)
{
	int	len;

	ft_parser(data->mini, data->splited[data->i], data->commands, 0);
	handle_redirections(data);
	if (data->commands->output_str)
	{
		len = ft_strlen(data->commands->output_str);
		write(data->commands->op, data->commands->output_str, len);
	}
	execute_command(data);
	exit(0);
}

void	process_command(t_pipeline_data *data)
{
	data->pid = fork();
	if (data->pid == 0)
		child_process(data);
	else if (data->pid > 0)
		parent_process(data);
	else
	{
		perror("Fork error");
		exit(1);
	}
}

void	setup_pipe(t_pipeline_data *data)
{
	if (data->i < data->num_cmds - 1)
	{
		if (pipe(data->pipe_fd) == -1)
		{
			perror("Pipe error");
			exit(1);
		}
	}
}

void	ft_execute_pipeline(t_minishell *mini, t_command *c, int n, char **s)
{
	t_pipeline_data	data;

	data.mini = mini;
	data.commands = c;
	data.splited = s;
	data.num_cmds = n;
	data.in_fd = 0;
	data.i = 0;
	while (data.i < n)
	{
		setup_pipe(&data);
		process_command(&data);
		data.i++;
	}
}

void	ft_all_parser(t_minishell *mini, char *input)
{
	t_command	command;
	char		**splited;
	int			i;
	int			max;

	if (ft_empty_par(mini, input))
		return ;
	i = 0;
	ft_replace_quote(input);
	splited = ft_split(input, '|');
	while (splited[i])
		i++;
	max = i;
	ft_execute_pipeline(mini, &command, max, splited);
}
