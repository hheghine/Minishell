/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_builtin3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 23:27:54 by hbalasan          #+#    #+#             */
/*   Updated: 2023/11/01 22:10:46 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	find_from_envp(char *var, char **envp, int i[2])
{
	int	j;

	i[1] = 0;
	j = ft_strlen(var);
	while (envp[i[1]])
	{
		if (!ft_strncmp(envp[i[1]], var, j))
			return (true);
		i[1]++;
	}
	return (false);
}

int	mini_unset(t_prompt *prompt)
{
	char	**arg;
	char	*temp;
	int		i[2];

	i[0] = 0;
	arg = ((t_command *)prompt->cmds->content)->full_cmd;
	if (ft_matrixlen(arg) >= 2)
	{
		while (arg[++i[0]])
		{
			temp = ft_strjoin(arg[i[0]], "=");
			free(arg[i[0]]);
			arg[i[0]] = temp;
			if (find_from_envp(arg[i[0]], prompt->envp, i))
				ft_matrix_replace(&prompt->envp, NULL, i[1]);
		}
	}
	return (0);
}

static void	export_declare_x(char **m)
{
	char	*temp;
	int		i;

	i = -1;
	while (m && m[++i])
	{
		temp = ft_strjoin("declare -x ", m[i]);
		free(m[i]);
		m[i] = ft_strdup(temp);
		free(temp);
	}
}

void	mini_export_noarg(t_prompt *prompt)
{
	char	**temp;

	temp = ft_alphabetical_matrix(prompt->envp);
	export_declare_x(temp);
	ft_printmatrix_fd(temp, 1);
	ft_free_matrix(&temp);
}

/* "export" is used to define and modify environment variables,
making them accessible to child processes */
int	mini_export(t_prompt *prompt, t_list *cmd)
{
	t_command	*arg;
	bool		flag;
	int			i[2];

	arg = cmd->content;
	if (ft_matrixlen(arg->full_cmd) == 1)
		mini_export_noarg(prompt);
	else if (ft_matrixlen(arg->full_cmd) >= 2)
	{
		i[0] = 1;
		while (arg->full_cmd[i[0]])
		{
			flag = find_from_envp(arg->full_cmd[i[0]], prompt->envp, i);
			if (flag)
			{
				free(prompt->envp[i[1]]);
				prompt->envp[i[1]] = ft_strdup(arg->full_cmd[i[0]]);
			}
			else
				prompt->envp = ft_extend_matrix(prompt->envp, arg->full_cmd[i[0]]);
			i[0]++;
		}
	}
	return (0);
}
