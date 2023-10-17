/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:23:29 by chonorat          #+#    #+#             */
/*   Updated: 2023/10/17 12:48:19 by chonorat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_error(char *cmd, int error)
{
	if (error == 1)
		ft_dprintf(2, "%s: command not found\n", cmd);
	else if (error == 2)
		ft_dprintf(2, "%s: No such file or directory\n", cmd);
}

static void	heredoc_error(char *delimiter)
{
	ft_dprintf(2, "warning: ");
	ft_dprintf(2, "here-document delimited by end-of-file");
	ft_dprintf(2, "(wanted `%s')", delimiter);
}

void	show_error(char *cmd, char *type, int error)
{
	ft_putstr_fd("minishell: ", 2);
	if (ft_strcmp(type, "EXEC") == 0)
		exec_error(cmd, error);
	if (ft_strcmp(type, "QUOTES") == 0)
		ft_putendl_fd("Quotes are not closed", 2);
	if (ft_strcmp(type, "HEREDOC") == 0)
		heredoc_error(cmd);
}
