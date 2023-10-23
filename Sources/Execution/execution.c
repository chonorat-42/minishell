/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 12:48:14 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/08/24 19:06:58 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern long long	g_status;

int	is_builtin(t_tokens *temp)
{
	if (!ft_strcmp(temp->cmd_arr[0], "echo")
		|| !ft_strcmp(temp->cmd_arr[0], "cd")
		|| !ft_strcmp(temp->cmd_arr[0], "exit")
		|| !ft_strcmp(temp->cmd_arr[0], "env")
		|| !ft_strcmp(temp->cmd_arr[0], "unset")
		|| !ft_strcmp(temp->cmd_arr[0], "pwd")
		|| !ft_strcmp(temp->cmd_arr[0], "export"))
		return (g_status = 0, 1);
	return (0);
}

void	builtin_forwarding_pipe(t_tokens *temp, t_mshell *shell)
{
	if (!ft_strcmp(temp->cmd_arr[0], "echo"))
		echo_case(temp->cmd_arr, 1);
	else if (!ft_strcmp(temp->cmd_arr[0], "cd"))
		cd_case(shell, temp->cmd_arr);
	else if (!ft_strcmp(temp->cmd_arr[0], "exit"))
		exit_case(shell, temp->cmd_arr);
	else if (!ft_strcmp(temp->cmd_arr[0], "env"))
		env_case(shell, temp->cmd_arr, 1);
	else if (!ft_strcmp(temp->cmd_arr[0], "unset"))
		unset_case(shell, temp->cmd_arr);
	else if (!ft_strcmp(temp->cmd_arr[0], "pwd"))
		pwd_case(shell, temp->cmd_arr, 1);
	else if (!ft_strcmp(temp->cmd_arr[0], "export"))
		export_case(shell, temp->cmd_arr, 1);
}

void	builtin_forwarding(t_tokens *temp, t_mshell *shell)
{
	if (!ft_strcmp(temp->cmd_arr[0], "echo"))
		echo_case(temp->cmd_arr, temp->fd_out);
	else if (!ft_strcmp(temp->cmd_arr[0], "cd"))
		cd_case(shell, temp->cmd_arr);
	else if (!ft_strcmp(temp->cmd_arr[0], "exit"))
		exit_case(shell, temp->cmd_arr);
	else if (!ft_strcmp(temp->cmd_arr[0], "env"))
		env_case(shell, temp->cmd_arr, temp->fd_out);
	else if (!ft_strcmp(temp->cmd_arr[0], "unset"))
		unset_case(shell, temp->cmd_arr);
	else if (!ft_strcmp(temp->cmd_arr[0], "pwd"))
		pwd_case(shell, temp->cmd_arr, temp->fd_out);
	else if (!ft_strcmp(temp->cmd_arr[0], "export"))
		export_case(shell, temp->cmd_arr, temp->fd_out);
}

void	executable(t_tokens *temp, t_mshell *shell)
{
	pid_t	child;

	child = fork();
	if (child == -1)
		return (free_struct(shell), exit(EXIT_FAILURE));
	if (!child)
	{
		exec_sig(shell);
		manage_fd(temp->fd_in, temp->fd_out);
		temp->fd_in = 0;
		temp->fd_out = 1;
		bin_exec(shell, temp->cmd_arr);
	}
	else
	{
		if (temp->fd_in != 0)
			close(temp->fd_in);
		if (temp->fd_out != 1)
			close(temp->fd_out);
		if (waitpid(child, (int *)&g_status, 0) == -1)
			return (perror("waitpid"), free_struct(shell), exit(EXIT_FAILURE));
	}
	get_fork_status();
	if (temp->cmd_arr)
		free_arr(temp->cmd_arr);
	temp->cmd_arr = NULL;
}

void	exec_forwarding(t_tokens *temp, t_mshell *shell)
{
	// ft_dprintf(2, "in exec forwarding, cmd = %s, fd = %d\n", temp->cmd_arr[0], temp->fd_out);
	if (has_bad_fd(temp))
	{
		g_status = 1;
		return (print_errors(temp));
	}
	if (is_builtin(temp))
		builtin_forwarding(temp, shell);
	else
	{
		ignore_sig(shell);
		executable(temp, shell);
	}
}

void	execution(t_mshell *shell)
{
	t_tokens	*temp;

	temp = shell->tok_lst;
	if (temp->next && temp->next->type == PIPE)
		handle_pipes(shell, temp);
	else
		exec_forwarding(temp, shell);
	free(shell->input);
	free_tokens(&shell->tok_lst);
}
