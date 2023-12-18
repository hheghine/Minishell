/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 20:31:52 by hbalasan          #+#    #+#             */
/*   Updated: 2023/12/18 20:52:49 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// extern int	g_status;

char	*find_command(char **env_path, char *cmd, char *full_path)
{
	char	*temp;
	int		i;

	full_path = NULL;
	i = -1;
	while (env_path && env_path[++i])
	{
		if (full_path)
			free(full_path);
		temp = ft_strjoin(env_path[i], "/");
		if (!temp)
			return (NULL);
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			break ;
	}
	if (!env_path || !env_path[i])
	{
		free(full_path);
		return (NULL);
	}
	return (full_path);
}

DIR	*cmd_and_path_check(t_prompt *prompt, t_list *cmd, char ***str, char *path)
{
	DIR			*dir;
	t_command	*node;

	dir = NULL;
	node = cmd->content;
	if (node && node->full_cmd)
		dir = opendir(node->full_cmd[0]);
	if (node && node->full_cmd && ft_strchr(node->full_cmd[0], '/') \
		&& !dir)
	{
		*str = ft_split(node->full_cmd[0], '/');
		node->full_path = ft_strdup(node->full_cmd[0]);
		free(node->full_cmd[0]);
		node->full_cmd[0] = ft_strdup(str[0][ft_matrixlen(*str) - 1]);
	}
	else if (!is_builtin(node) && node && node->full_cmd && !dir)
	{
		path = get_env("PATH", prompt->envp, 4);
		*str = ft_split(path, ':');
		free(path);
		node->full_path = find_command(*str, *node->full_cmd, node->full_path);
		if (!node->full_path || !*node->full_cmd || !node->full_cmd[0][0])
			mini_error(ECMD, node->full_cmd[0], 127);
	}
	return (dir);
}

// finds the command in PATH and retrieves the full command
void	get_command(t_prompt *prompt, t_list *cmd)
{
	t_command	*node;
	DIR			*dir;
	char		**str;
	char		*path;

	str = NULL;
	path = NULL;
	node = cmd->content;
	dir = cmd_and_path_check(prompt, cmd, &str, path);
	if (!is_builtin(node) && node && node->full_cmd && dir)
		mini_error(ISDIR, node->full_cmd[0], 126);
	else if (!is_builtin(node) && node && node->full_path && \
		access(node->full_path, F_OK) == -1)
		mini_error(NDIR, node->full_path, 127);
	else if (!is_builtin(node) && node && node->full_path && \
		access(node->full_path, X_OK) == -1)
		mini_error(EPERM, node->full_path, 126);
	if (dir)
		closedir(dir);
	ft_free_matrix(&str);
}

void	*exec_command(t_prompt *prompt, t_list *cmd)
{
	int	fd[2];

	get_command(prompt, cmd);
	if (pipe(fd) < 0)
		return (mini_error(EPIPE, NULL, 1));
	if (!mini_fork_check(prompt, cmd, fd))
		return (NULL);
	close (fd[WRITE_END]);
	if (cmd->next && ((t_command *)cmd->next->content)->infile == STDIN_FILENO)
		((t_command *)cmd->next->content)->infile = fd[READ_END];
	else
		close(fd[READ_END]);
	if (((t_command *)cmd->content)->infile > 2)
		close(((t_command *)cmd->content)->infile);
	if (((t_command *)cmd->content)->outfile > 2)
		close(((t_command *)cmd->content)->outfile);
	return (NULL);
}
