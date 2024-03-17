/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 19:01:52 by alexafer          #+#    #+#             */
/*   Updated: 2024/03/17 01:06:59 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

volatile t_minishell	mini;

void sigint_handler(int sig_num)
{
	(void)sig_num;
	//ft_printf("\n>>>");
	//printf("\n");
	//printf("\n val : %d\n", sig_num);
	if (sig_num == 2)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		ft_printf("%s\n", mini.prompt);
		rl_redisplay();
	}
}

int	main(void)
{
	char		*input;
	char		*prompt;
	int			error;
	//t_minishell	mini;

	signal(SIGINT, sigint_handler);
	mini.path = 0;
	mini.error = 0;
	mini.error = ft_get_path(&mini);
	//ft_printf("%s\n", mini.start_path);

	while (1)
	{
		mini.prompt = ft_make_prompt(mini);
		input = readline(mini.prompt);
		free(mini.prompt);
		if (!input || mini.error || !ft_strncmp(input, "exit", 4))
			break ;
		if (!ft_strncmp(input, "pwd", 3))
			ft_printf("%s\n", mini.path);
		//else if (ft_strncmp(input, "\0", 1))
		//	ft_printf("%s\n", input);
		if (*input)
			add_history(input);
		free(input);
	}
	ft_printf("\nCurrent working directory: %s\n", mini.path);
	return (0);
}
