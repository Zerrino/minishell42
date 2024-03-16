/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 19:01:52 by alexafer          #+#    #+#             */
/*   Updated: 2024/03/16 21:34:31 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

void sigint_handler(int sig_num)
{
	(void)sig_num;
	//ft_printf("\n>>>");
	//printf("\n");
	rl_on_new_line();
	//rl_replace_line("", 0);
	rl_redisplay();
	ft_printf("\n>>>");
}

int	main(void)
{
	char		*input;
	char		*prompt;
	int			error;
	t_minishell	mini;

	signal(SIGINT, sigint_handler);
	mini.path = 0;
	mini.error = 0;
	mini.error = ft_get_path(&mini);
	while (1)
	{
		prompt = ft_make_promt(mini);
		input = readline(prompt);
		free(prompt);
		if (!input || mini.error)
			break ;
		if (!ft_strncmp(input, "path", 4))
			mini.error = ft_get_path(&mini);
		else if (ft_strncmp(input, "\0", 1))
			ft_printf("%s\n", input);
		if (*input)
			add_history(input);
		free(input);
	}
	ft_printf("\nCurrent working directory: %s\n", mini.path);
	return (0);
}
