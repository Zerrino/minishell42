/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:04:55 by lpetit            #+#    #+#             */
/*   Updated: 2024/04/04 15:12:01 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

int	ft_exit(t_minishell *mini, t_command *com)
{
	ft_clearlst(mini->env);
	ft_free_split(com->data);
	exit(0);
}
