/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 19:01:52 by alexafer          #+#    #+#             */
/*   Updated: 2024/04/11 12:54:04 by lpetit           ###   ########.fr       */
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

int	ft_getpid(void)
{
	pid_t	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
		exit(0);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (pid - 1);
	}
	return (0);
}

int	init_shell(t_minishell *mini, char **env)
{
	mini->path = 0;
	mini->stop = 0;
	mini->error = 0;
	mini->status_com = 0;
	mini->env = init_env_var(mini, env);
	mini->error = ft_get_path(mini);
	mini->pid = ft_getpid();
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	//char		**split;
	char		*input;
	//char		*prompt;
	//int			error;
	t_minishell	mini;

	(void)argv;
	(void)argc;
	//printf("Prog started.\n");
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	//mini.program_name = argv[argc - 1];
	init_shell(&mini, env);
	//printf("pid = %d\n", getpid());
	//printf("pid %d\n", mini.pid);
	//printf("getpid %d\n", getpid());
	//ft_printf("%s\n", mini.start_path);
	while (1)
	{
		mini.prompt = ft_make_prompt(mini);
		g_prompt = mini.prompt;
		input = readline(mini.prompt);
		free(mini.prompt);
		if (input && *input)
			add_history(input);
		ft_all_parser(&mini, input);
		if (mini.stop)
			break ;
		free(input);
		//printf("Last status : %d\n", mini.status_com);
	}
	if (input)
		free(input);
	ft_clearlst(mini.env);
	//ft_printf("Current working directory: %s\n", mini.path);
	return (0);
}
