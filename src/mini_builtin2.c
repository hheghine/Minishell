/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_builtin2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 02:28:45 by hbalasan          #+#    #+#             */
/*   Updated: 2023/10/31 01:38:31 by hbalasan         ###   ########.fr       */
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
	t_command	*node;
	char		**fullcmd;
	int			newline;
	int			i[2];

	node = cmd->content;
	fullcmd = node->full_cmd;
	i[0] = 0;
	i[1] = 0;
	newline = 1;
	while (fullcmd && fullcmd[++i[0]])
	{
		if (!i[1] && !ft_strncmp(fullcmd[i[0]], "-n", 2) && \
			(ft_charcount(fullcmd[i[0]], 'n') == \
			(int)(ft_strlen(fullcmd[i[0]]) - 1)))
			newline = 0;
		else
		{
			i[1] = 1;
			ft_putstr_fd(fullcmd[i[0]], 1);
			if (fullcmd[i[0] + 1])
				ft_putchar_fd(' ', 1);
		}
	}
	return (write(1, "\n", newline) == 2);
}

int	mini_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (0);
}

int	mini_exit(t_list *cmd, int *isexit)
{
	t_command	*node;
	long		status[2];

	node = cmd->content;
	*isexit = !(cmd->next);
	if (*isexit)
		ft_putstr_fd("\033[1;35mexit⁺₊⋆☽⁺₊⋆\033[0m\n", 2);
	if (!node->full_cmd || !node->full_cmd[1]) // if there is no second argument after the "exit" command
		return (0);
	status[0] = ft_atoi_ext(node->full_cmd[1], &status[1]);
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
