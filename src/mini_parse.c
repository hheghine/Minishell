/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 21:35:14 by hbalasan          #+#    #+#             */
/*   Updated: 2023/10/23 02:47:11 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char **split_final(char **args, t_prompt *prompt)
{
	char	**subsplit;
	int		i;
	int		q[2];

	i = -1;
	while (args && args[++i])
	{
		args[i] = expand_vars(args[i], prompt, q, -1);
		args[i] = expand_path(args[i], q, \
			get_env("HOME", prompt->envp, -1), -1);
		subsplit = cmd_subsplit(args[i], "<>|"); // split commands with <, >, or | 
		ft_matrix_replace(&args, subsplit, i);
		i += ft_matrixlen(subsplit) - 1;
		ft_free_matrix(&subsplit);
	}
	return (args);
}

void	*parse_args(char **args, t_prompt *prompt)
{
	char	**splitted;
	int		i;
	int		exitcode;

	exitcode = 0;
	splitted = split_final(args, prompt);
	prompt->cmds = fill_nodes(splitted, -1);
}

void	*check_args(char *cmd, t_prompt *prompt)
{
	char		**trim;
	t_command	command;

	if (!cmd || !ft_strncmp(cmd, "exit", 4))
	{
		printf("\033[1;35mexit⁺₊⋆☽⁺₊⋆\033[0m\n");
		free(cmd);
		return (NULL);
	}
	if (ft_strlen(cmd) > 0)
    	add_history(cmd);
	trim = cmd_trim(cmd, " ");
	if (!trim)
		return ("");
	free(cmd);
	prompt = parse_args(trim, prompt);
	return ("a"); // temporary
}