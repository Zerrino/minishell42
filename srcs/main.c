/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 19:01:52 by alexafer          #+#    #+#             */
/*   Updated: 2024/04/20 14:38:07 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

void	sigint_handler(int sig_num)
{
	(void)sig_num;
	rl_on_new_line();
	rl_replace_line("", 0);
	ft_printf("\033[35mminishell > \033[0m\n");
	rl_redisplay();
}

int	ft_getpid(void)
{
	pid_t	pid;
	int		status;

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

char	**base_env(t_minishell *mini)
{
	char	**base_env;
	char	*str;

	str = "PWD=";
	str = ft_strjoin(str, mini->start_path);
	str = ft_strjoin_f(str, " SHLVL=1 _=/usr/bin/env");
	base_env = ft_split(str, 32);
	if (str != NULL)
		free(str);
	mini->base_env = base_env;
	return (base_env);
}

int	init_shell(t_minishell *mini, char **env)
{
	mini->prompt = 0;
	mini->path = 0;
	mini->stop = 0;
	mini->error = 0;
	mini->status_com = 0;
	mini->base_env = 0;
	mini->error = ft_get_path(mini);
	if (env[0] == NULL)
		env = base_env(mini);
	mini->env = init_env_var(env);
	if (mini->base_env != NULL)
		ft_free_split(mini->base_env);
	if (mini->env == NULL)
	{
		free(mini->start_path);
		exit(1);
	}
	mini->pid = ft_getpid();
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_minishell	mini;

	(void)argv;
	(void)argc;
	init_shell(&mini, env);
	while (1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		input = readline("\033[35mminishell > \033[0m");
		if (input && *input)
			add_history(input);
		ft_all_parser(&mini, input);
		if (mini.stop)
			break ;
		free(input);
	}
	if (input)
		free(input);
	ft_clearlst(mini.env);
	return (0);
}
