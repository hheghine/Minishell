/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_builtin1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:48:58 by hbalasan          #+#    #+#             */
/*   Updated: 2023/11/23 18:36:31 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

bool	is_builtin(t_command *cmd)
{
	int	len;

	if (!cmd->full_cmd)
		return (false);
	if ((cmd->full_cmd && ft_strchr(cmd->full_cmd[0], '/')) || \
		(cmd->full_path && ft_strchr(cmd->full_path, '/')))
		return (false);
	len = ft_strlen(cmd->full_cmd[0]);
	if (!ft_strncmp(cmd->full_cmd[0], "cd", len) && len == 2)
		return (true);
	if (!ft_strncmp(cmd->full_cmd[0], "pwd", len) && len == 3)
		return (true);
	if (!ft_strncmp(cmd->full_cmd[0], "env", len) && len == 3)
		return (true);
	if (!ft_strncmp(cmd->full_cmd[0], "echo", len) && len == 4)
		return (true);
	if (!ft_strncmp(cmd->full_cmd[0], "exit", len) && len == 4)
		return (true);
	if (!ft_strncmp(cmd->full_cmd[0], "unset", len) && len == 5)
		return (true);
	if (!ft_strncmp(cmd->full_cmd[0], "export", len) && len == 6)
		return (true);
	return (false);
}

static void	is_not_builtin(t_prompt *prompt, t_list *cmd)
{
	sigaction_handler2();
	exec_command(prompt, cmd);
}

int	mini_builtin(t_prompt *prompt, t_list *cmd, int *isexit, int n)
{
	t_command	*c;

	while (cmd)
	{
		c = cmd->content;
		n = 0;
		if (c && c->full_cmd && *c->full_cmd)
			n = ft_strlen(*c->full_cmd);
		if (c && c->full_cmd && *c->full_cmd && \
		!ft_strncmp(*c->full_cmd, "exit", n) && n == 4)
			g_status = mini_exit(cmd, isexit);
		else if (!cmd->next && c && c->full_cmd && \
		!ft_strncmp(*c->full_cmd, "cd", n) && n == 2)
			g_status = mini_cd(prompt);
		else if (!cmd->next && c && c->full_cmd && \
		!ft_strncmp(*c->full_cmd, "unset", n) && n == 5)
			g_status = mini_unset(prompt);
		else if (!cmd->next && c && c->full_cmd && \
		!ft_strncmp(*c->full_cmd, "export", n) && n == 6)
			g_status = mini_export(prompt, cmd);
		else
			is_not_builtin(prompt, cmd);
		cmd = cmd->next;
	}
	return (g_status);
}
