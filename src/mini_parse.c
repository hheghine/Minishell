/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 21:35:14 by hbalasan          #+#    #+#             */
/*   Updated: 2023/11/23 18:36:31 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

char	**split_final(char **args, t_prompt *prompt)
{
	char	**subsplit;
	int		i;
	int		q[2];

	i = -1;
	while (args && args[++i])
	{
		if (i < 2 || ft_strncmp(args[i - 2], "<<", 2) > 0)
		{
			args[i] = expand_vars(args[i], prompt, q, -1);
			args[i] = expand_path(args[i], q, \
			get_env("HOME", prompt->envp, -1), -1);
		}
		subsplit = cmd_subsplit(args[i], "<>|");
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
	int		isexit;

	isexit = 0;
	splitted = split_final(args, prompt);
	prompt->cmds = fill_nodes(prompt, splitted, -1);
	if (!prompt->cmds)
		return (prompt);
	i = ft_lstsize(prompt->cmds);
	g_status = mini_builtin(prompt, prompt->cmds, &isexit, 0);
	while (--i >= 0)
	{
		wait(&g_status);
	}
	if (!isexit && (g_status == 3 || g_status == 13))
		g_status = 0;
	if (g_status > 255)
		g_status %= 255;
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

	if (!cmd)
	{
		ft_putstr_fd("\033[0;35mexit\033[1;36m⁺₊⋆☽⁺₊⋆\033[0m\n", 2);
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
		command->full_cmd[ft_matrixlen(command->full_cmd) - 1], prompt->envp);
	if (prompt && prompt->cmds)
		ft_lstclear(&prompt->cmds, free_content);
	return (prompt);
}
