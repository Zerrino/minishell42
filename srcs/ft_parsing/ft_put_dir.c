/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:48:44 by alexafer          #+#    #+#             */
/*   Updated: 2024/04/05 18:37:33 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static void	ft_util_com(int *i, int *doub)
{
	*doub = 1;
	*i += 1;
}

static int	ft_output_util(t_command *c, char **splited, int doub)
{
	int	output;
	int	i;

	output = ft_redir_right(splited[0], doub);
	if (output != -1)
	{
		c->file_out.file_name = splited[0];
		c->file_out.doub = doub;
	}
	i = 0;
	while (splited[i])
	{
		if (i > 0)
			free(splited[i]);
		i++;
	}
	free(splited);
	return (output);
}

int	ft_output_com(t_command *command, char *input)
{
	char	**splited;
	int		i;
	int		doub;
	int		output;

	command->file_out.file_name = 0;
	i = 0;
	output = 1;
	while (input[i])
	{
		if (input[i] == '>')
		{
			doub = 0;
			if (output != 1)
				close(output);
			if (input[i + 1] == '>')
				ft_util_com(&i, &doub);
			splited = ft_split(&input[i + 1], ' ');
			output = ft_output_util(command, splited, doub);
			if (output == -1)
				return (-1);
		}
		i++;
	}
	return (output);
}

static char	*ft_input_util(t_command *c, char **splited, t_minishell *mini,
	t_ran ran)
{
	int	i;

	if (ran.output)
		free(ran.output);
	ran.output = ft_redir_left(c, splited[0], ran.doub, mini);
	if (ran.output)
	{
		c->file_in.file_name = splited[0];
		c->file_in.doub = ran.doub;
	}
	i = 0;
	while (splited[i])
	{
		if (i > 0)
			free(splited[i]);
		i++;
	}
	free(splited);
	return (ran.output);
}

char	*ft_input_dir(t_minishell *mini, t_command *command, char *input)
{
	t_ran	ran;
	char	**splited;
	int		i;
	int		doub;

	i = 0;
	ran.output = 0;
	command->file_in.file_name = 0;
	while (input[i])
	{
		if (input[i] == '<')
		{
			doub = 0;
			if (input[i + 1] == '<')
				ft_util_com(&i, &doub);
			splited = ft_split(&input[i + 1], ' ');
			ran.doub = doub;
			ran.output = ft_input_util(command, splited, mini, ran);
			if (ran.output == 0)
				return (0);
		}
		i++;
	}
	return (ran.output);
}
