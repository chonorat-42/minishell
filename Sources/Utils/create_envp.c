/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:20:57 by chonorat          #+#    #+#             */
/*   Updated: 2023/10/05 16:40:55 by chonorat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pwd(t_mshell *shell)
{
	t_var	new;
	char	path[PATH_MAX];

	new.name = ft_strdup("PWD");
	if (!new.name)
		return (free_struct(shell), exit(2));
	new.content = getcwd(path, PATH_MAX);
	if (!new.content)
		return (free(new.name), free_struct(shell), exit(2));
	if (new.content[0] == '\0')
		new.content = NULL;
	new.readable = 1;
	if (!new.content)
		new.readable = 0;
	new.alterable = 1;
	create_envp_list(shell, &new);
}

static void	shlvl(t_mshell *shell)
{
	t_var	new;

	new.name = ft_strdup("SHLVL");
	if (!new.name)
		return (free_struct(shell), exit(2));
	new.content = ft_strdup("1");
	if (!new.content)
		return (free(new.name), free_struct(shell), exit(2));
	new.readable = 1;
	new.alterable = 1;
	create_envp_list(shell, &new);
}

static void	underscore(t_mshell *shell, char **argv)
{
	t_var	new;

	new.name = ft_strdup("_");
	if (!new.name)
		return (free_struct(shell), exit(2));
	new.content = ft_strdup(argv[0]);
	if (!new.content)
		return (free(new.name), free_struct(shell), exit(2));
	new.readable = 1;
	new.alterable = 0;
	create_envp_list(shell, &new);
}

void	create_envp(t_mshell *shell, char **argv)
{
	pwd(shell);
	shlvl(shell);
	underscore(shell, argv);
}