/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:31:02 by alexafer          #+#    #+#             */
/*   Updated: 2024/03/16 21:38:03 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"


char	*ft_make_promt(t_minishell mini)
{
	char	*prompt;
	char	*sub_prompt;

	sub_prompt = ft_strjoin("\033[35m", mini.folder);
	prompt = ft_strjoin(sub_prompt, "\033[0m");
	free(sub_prompt);
	sub_prompt = ft_strjoin(prompt, "\033[30m>\033[0m ");
	free(prompt);
	return (sub_prompt);
}
