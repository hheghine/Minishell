/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_builtin2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 02:28:45 by hbalasan          #+#    #+#             */
/*   Updated: 2023/10/30 00:17:09 by hbalasan         ###   ########.fr       */
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
	free(temp);
	prompt->envp = set_env("PWD", str[2], prompt->envp);
	ft_free_matrix(&str);
	return (gstatus);
}

// echo -n: this option is used to omit echoing trailing newline.
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

int	mini_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (0);
}

int	mini_exit(t_list *cmd, bool *isexit)
{
	t_command	*node;
	long		status[2];

	node = cmd->content;
	*isexit = !(cmd->next);
	if (*isexit)
		ft_putstr_fd("\033[1;35mexit⁺₊⋆☽⁺₊⋆\033[0m\n", 2);
	if (!node->full_cmd || !node->full_cmd[1]) // if there is no second argument after the "exit" command
		return (0);
	status[0] = ft_atoi_ext(node->full_cmd[1], &status[0]);
	if (status[0] == -1)
	{
		print_error_msg_fd("exit: ");
		ft_putstr_fd(node->full_cmd[1], 2);
		ft_putstr_fd("\033[0;33m: numeric argument required\033[0m\n", 2);
		return (255);
	}
	else if (node->full_cmd[2])
	{
		*isexit = 0;
		print_error_msg_fd("exit: too many arguments\n");
		return (1);
	}
	status[1] = (status[1] % 256) + 256 * (status[1] < 0); // range [0, 255] as exit statuses are typically limited to 8 bits
	return (status[1]);
}

