/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 21:35:14 by hbalasan          #+#    #+#             */
/*   Updated: 2023/10/30 19:12:55 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	gstatus;

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
	bool	isexit;

	isexit = false;
	splitted = split_final(args, prompt);
	prompt->cmds = fill_nodes(splitted, -1);
	if (!prompt->cmds)
		return (prompt);
	i = ft_lstsize(prompt->cmds);
	gstatus = mini_builtin(prompt, prompt->cmds, &isexit, 0);
	while (--i >= 0)
		wait(&gstatus);
	// if (!isexit || gstatus == 3) // 3 - corresponds to my NOTDIR
	if (gstatus == 3 || gstatus == 3) // 13 - for cat
		gstatus = 0;
	if (isexit && args)
	{
		ft_lstclear(&prompt->cmds, free_content);
		return (NULL);
	}
	return (prompt);
}

void	*check_args(char *cmd, t_prompt *prompt)
{
	char		**trim;
	t_command	*command;

	if (!cmd || !ft_strncmp(cmd, "exit", 4))
	{
		// printf("\033[1;35mexit⁺₊⋆☽⁺₊⋆\033[0m\n");
		ft_putstr_fd("\033[1;35mexit⁺₊⋆☽⁺₊⋆\033[0m\n", 2);
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
	if (prompt && prompt->cmds)
		command = prompt->cmds->content;
	if (prompt && prompt->cmds && command && command->full_cmd \
		&& ft_lstsize(prompt->cmds) == 1)
		prompt->envp = set_env("_", \
		command->full_cmd[ft_matrixlen(command->full_cmd) - 1],prompt->envp);
	if (prompt && prompt->cmds)
		ft_lstclear(&prompt->cmds, free_content);
	return (prompt);
}