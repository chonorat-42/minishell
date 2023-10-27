/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:59:01 by chonorat          #+#    #+#             */
/*   Updated: 2023/10/27 13:27:38 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern long long	g_status;

void	exit_case(t_mshell *shell, char **cmd)
{
	ft_putendl_fd("exit", 1);
	if (ft_arr_size(cmd) > 1)
	{
		if (!only_digit(cmd[1]))
		{
			builtin_error(cmd[0], cmd[1], 1);
			g_status = 2;
		}
		else if (ft_arr_size(cmd) > 2)
			return (builtin_error(cmd[0], cmd[1], 2));
		else
			g_status = ll_atoi(cmd[1]);
	}
	else
		g_status = shell->exit_status;
	return (free_struct(shell), close_std_fds(), exit(g_status % 256));
}
