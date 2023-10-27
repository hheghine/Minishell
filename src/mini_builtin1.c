/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_bultin1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 02:28:45 by hbalasan          #+#    #+#             */
/*   Updated: 2023/10/28 02:18:14 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	gstatus;

int	mini_cd(t_prompt *prompt)
{
	char	**full_cmd;
	char	**str;
	char	*temp;

	gstatus = 0;
	full_cmd = ((t_command *)prompt->cmds->content)->full_cmd;
	temp = get_env("HOME", prompt->envp, 4);
	if (!temp)
		temp = ft_strdup("");
	str = ft_extend_matrix(NULL, temp);
	free(temp);
	temp = getcwd(NULL, 0);
	str = ft_extend_matrix(str, temp);
	free(temp);
	mini_cd_error(full_cmd, str);
	if (!gstatus)
		prompt->envp = set_env("OLDPWD", str[1], prompt->envp);
	temp = getcwd(NULL, 0);
	if (!temp)
		temp = ft_strdup("");
	str = ft_extend_matrix(str, temp);
	free(str);
	prompt->envp = set_env("PWD", str[2], prompt->envp);
	ft_free_matrix(&str);
	return (gstatus);
}

int	mini_echo(t_list *cmd)
{
	char		**full_cmd;
	t_command	*node;
	int			i;
	bool		newline;

	i = 0;
	newline = 1;
	node = cmd->content;
	full_cmd = node->full_cmd;
	while (full_cmd && full_cmd[++i])
	{
		if (i == 1 && !ft_strncmp(full_cmd[i], "-n", 2) && \
			ft_strlen(full_cmd[i]) == 2)
			newline = 0;
		else
		{
			ft_putstr_fd(full_cmd[i], 1);
			if (full_cmd[i + 1])
				ft_putchar_fd(' ', 1);
		}
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}

// echo -n: this option is used to omit echoing trailing newline.
int	mini_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (0);
}
