/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:24:22 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/08/24 18:17:10 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_input_loop(t_mshell *shell)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("\033[1mminishell@42\033[0m:~\033[0;32m$\033[0m ");
		if (!line)
			return (free_struct(shell), exit(2));
		else
			add_history(line);
		shell->input = ft_strtrim((const char *)line, "\n\t\v\f\r ");
		free(line);
		if (!shell->input)
			return (free_struct(shell), exit(3));
		parsing(shell);
		tokenizer(shell);
		execution(shell);
	}
}
