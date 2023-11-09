/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_builtin2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmnatsak <tmnatsak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 02:28:45 by hbalasan          #+#    #+#             */
/*   Updated: 2023/11/09 19:15:37 by tmnatsak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_gstatus;

int	mini_cd(t_prompt *prompt)
{
	char	**full_cmd;
	char	**str;
	char	*temp;

	g_gstatus = 0;
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
	if (!g_gstatus)
		prompt->envp = set_env("OLDPWD", str[1], prompt->envp);
	temp = getcwd(NULL, 0);
	if (!temp)
		temp = ft_strdup("");
	str = ft_extend_matrix(str, temp);
	free(temp);
	prompt->envp = set_env("PWD", str[2], prompt->envp);
	ft_free_matrix(&str);
	return (g_gstatus);
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

static void	is_exit(int *isexit)
{
	if (*isexit)
		ft_putstr_fd("\033[0;35mexit\033[1;36m⁺₊⋆☽⁺₊⋆\033[0m\n", 2);
}

int	mini_exit(t_list *cmd, int *isexit)
{
	t_command	*node;
	long		status[2];

	node = cmd->content;
	*isexit = !(cmd->next);
	is_exit(isexit);
	if (!node->full_cmd || !node->full_cmd[1])
		return (0);
	status[0] = ft_atoi_ext(node->full_cmd[1], &status[1]);
	if (status[0] == -1)
	{
		print_error_msg_fd("exit: ", 0);
		ft_putstr_fd("\033[1;33m", 2);
		ft_putstr_fd(node->full_cmd[1], 2);
		ft_putstr_fd("\033[0;33m: numeric argument required\033[0m\n", 2);
		return (255);
	}
	else if (node->full_cmd[2])
	{
		*isexit = 0;
		print_error_msg_fd("exit: too many arguments\n", 1);
		return (1);
	}
	status[1] = (status[1] % 256) + 256 * (status[1] < 0);
	return (status[1]);
}
