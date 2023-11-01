/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 01:46:09 by hbalasan          #+#    #+#             */
/*   Updated: 2023/11/01 20:11:11 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	gstatus;

void	this_is_childbuiltin(t_list *cmd, t_command *node, char **envp, int len)
{
	sigaction_handler3();
	// write (2, "\033[1;33m⚠ minishell: \033[0;33m", ft_strlen("\033[1;33m⚠ minishell: \033[0;33m"));
	if (!is_builtin(node) && node->full_cmd)
		execve(node->full_path, node->full_cmd, envp);
	else if (is_builtin(node) && node->full_cmd && \
		!ft_strncmp(node->full_cmd[0], "echo", len) && len == 4)
		gstatus = mini_echo(cmd);
	else if (is_builtin(node) && node->full_cmd && \
		!ft_strncmp(node->full_cmd[0], "pwd", len) && len == 3)
		gstatus = mini_pwd();
	else if (is_builtin(node) && node->full_cmd && \
		!ft_strncmp(node->full_cmd[0], "env", len) && len == 3)
	{
		ft_printmatrix_fd(envp, 1);
		gstatus = 0;
	}
}

void	*childprocess_io(t_list *cmd, t_command *node, int fd[2])
{
	if (node->infile != STDIN_FILENO)
	{
		if (dup2(node->infile, STDIN_FILENO) < 0)
			return (mini_error(DUPERR, NULL, 1));
		close(node->infile);
	}
	if (node->outfile != STDOUT_FILENO)
	{
		if (dup2(node->outfile, STDOUT_FILENO) < 0)
			return (mini_error(DUPERR, NULL, 1));
		close(node->outfile);
	}
	else if (cmd->next && dup2(fd[WRITE_END], STDOUT_FILENO) < 0)
		return (mini_error(DUPERR, NULL, 1));
	close(fd[WRITE_END]);
	return ("");
}

void	*this_is_childprocess(t_prompt *prompt, t_list *cmd, int fd[2])
{
	t_command	*node;
	int			len;

	node = cmd->content;
	len = 0;
	if (node->full_cmd)
	{
		// printf("%s\n", node->full_cmd[0]);
		len = ft_strlen(node->full_cmd[0]);
	}
	childprocess_io(cmd, node, fd);
	close(fd[READ_END]);
	this_is_childbuiltin(cmd, node, prompt->envp, len);
	ft_lstclear(&prompt->cmds, free_content);
	exit(gstatus);
}

void	execute(t_prompt *prompt, t_list *cmd, int fd[2])
{
	pid_t	id;

	id = fork();
	if (id < 0)
	{
		close(fd[READ_END]);
		close(fd[WRITE_END]);
		mini_error(EFORK, NULL, 1);
	}
	else if (id == 0)
		this_is_childprocess(prompt, cmd, fd); // THIS IS SEMPITERNAL! WILL WE EVER SEE THE END?!
	// wait(&gstatus);
}

void	*mini_fork_check(t_prompt *prompt, t_list *cmd, int fd[2])
{
	t_command	*node;
	DIR			*dir;

	dir = NULL;
	node = cmd->content;
	// printf("%s\n", node->full_cmd[0]);
	if (node->full_cmd)
		dir = opendir(node->full_cmd[0]);
	if (node->infile == -1 || node->outfile == -1)
		return (NULL);
	if ((node->full_path && access(node->full_path, X_OK) == 0) || is_builtin(node)) // is builtin or executable
		execute(prompt, cmd, fd);
	else if (!is_builtin(node) && ((node->full_path && \
		access(node->full_path, F_OK) == 0) || dir)) // is a directory
		gstatus = 126;
	else if (!is_builtin(node) && node->full_cmd) // command not found
		gstatus = 127;
	if (dir)
		closedir(dir);
	return ("");
}