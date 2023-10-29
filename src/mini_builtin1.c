/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_builtin1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:48:58 by hbalasan          #+#    #+#             */
/*   Updated: 2023/10/30 00:13:54 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	gstatus;

bool	is_builtin(t_command *cmd)
{
	int	len;

	if (!cmd->full_cmd)
		return (false);
	if (cmd->full_cmd && ft_strchr(cmd->full_cmd[0], '/') || \
		cmd->full_path && ft_strchr(cmd->full_path, '/'))
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

int	mini_builtin(t_prompt *prompt, t_list *cmd, bool *isexit, int n)
{
	t_command	*c;

	while (cmd)
	{
		c = cmd->content;
		n = 0;
		if (c && *c->full_cmd)
			n = ft_strlen(*c->full_cmd);
		if (c && *c->full_cmd && !ft_strncmp(*c->full_cmd, "exit", n) && n == 4)
			gstatus = mini_exit(cmd, isexit);
		else if (!cmd->next && c && !ft_strncmp(*c->full_cmd, "cd", n) && n == 2)
			gstatus = mini_cd(prompt);
		else if (!cmd->next && c && !ft_strncmp(*c->full_cmd, "unset", n) && n == 5)
			gstatus = mini_unset(prompt);
		else if (!cmd->next && c && !ft_strncmp(*c->full_cmd, "export", n) && n == 6)
			gstatus = mini_export(prompt);
		else
		{
			// signal handling ?? to ignore ??
			exec_command(prompt, cmd);
		}
		cmd = cmd->next;
	}
	return (gstatus);
}
