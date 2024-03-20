/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 19:01:52 by alexafer          #+#    #+#             */
/*   Updated: 2024/03/20 16:17:56 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

volatile char	*g_prompt;

void	sigint_handler(int sig_num)
{
	(void)sig_num;
	//ft_printf("\n>>>");
	//printf("\n");
	//printf("\n val : %d\n", sig_num);


	rl_on_new_line();
	rl_replace_line("", 0);
	ft_printf("%s\n", g_prompt);
	rl_redisplay();
}

int	main(int argc, char **argv)
{
	char		**split;
	char		*input;
	char		*prompt;
	int			error;
	t_minishell	mini;

	printf("Prog started.\n");
	signal(SIGINT, sigint_handler);
	//mini.program_name = argv[argc - 1];
	mini.path = 0;
	mini.error = 0;
	mini.stop = 0;
	mini.error = ft_get_path(&mini);
	//ft_printf("%s\n", mini.start_path);
	while (1)
	{
		mini.prompt = ft_make_prompt(mini);
		g_prompt = mini.prompt;
		input = readline(mini.prompt);
		ft_parser(&mini, input);
		free(mini.prompt);
		if (mini.stop)
			break ;
		if (*input)
			add_history(input);
		free(input);
	}
	if (input)
		free(input);
	ft_printf("Current working directory: %s\n", mini.path);
	return (0);
}
