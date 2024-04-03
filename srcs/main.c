/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 19:01:52 by alexafer          #+#    #+#             */
/*   Updated: 2024/04/03 02:34:43 by alexafer         ###   ########.fr       */
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

	//if (sig_num == SIGQUIT)
	//	return ;
	rl_on_new_line();
	rl_replace_line("", 0);
	ft_printf("%s\n", g_prompt);
	rl_redisplay();
}

int	main(int argc, char **argv, char **env)
{
	char		**split;
	char		*input;
	char		*prompt;
	int			error;
	t_minishell	mini;

	printf("Prog started.\n");
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	//mini.program_name = argv[argc - 1];
	mini.path = 0;
	mini.error = 0;
	mini.stop = 0;
	mini.error = ft_get_path(&mini);
	mini.env = init_env_var(&mini, env);
	mini.status_com = 0;
	//ft_printf("%s\n", mini.start_path);
	while (1)
	{
		mini.prompt = ft_make_prompt(mini);
		g_prompt = mini.prompt;
		input = readline(mini.prompt);
		ft_all_parser(&mini, input);
		//free(mini.prompt);
		if (mini.stop)
			break ;
		if (*input)
			add_history(input);
		//free(input);
		printf("Last status : %d\n", mini.status_com);
	}
	if (input)
		//free(input);
	ft_clearlst(mini.env);
	ft_printf("Current working directory: %s\n", mini.path);
	return (0);
}
