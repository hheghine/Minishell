/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 01:46:09 by hbalasan          #+#    #+#             */
/*   Updated: 2023/10/29 02:34:25 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	gstatus;

void	*mini_fork_check(t_prompt *prompt, t_list *cmd, int fd[2])
{
	t_command	*node;
	DIR			*dir;

	dir = NULL;
	node = cmd->content;
	if (node->full_cmd)
		dir = opendir(node->full_cmd[0]);
	if (node->infile == -1 || node->outfile == -1)
		return (NULL);
	if (is_builtin(node) || node->full_cmd && access(node->full_cmd, X_OK) == 0) // is builtin or executable
		execute();
	else if (!is_builtin(node) && ((node->full_cmd && \
		access(node->full_cmd, F_OK) == 0) || dir)) // is a directory
		gstatus = 126;
	else if (!is_builtin(node) && node->full_cmd) // command not found
		gstatus = 127;
	if (dir)
		closedir(dir);
	return ("");
}