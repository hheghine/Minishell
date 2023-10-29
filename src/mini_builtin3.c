/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_builtin3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 23:27:54 by hbalasan          #+#    #+#             */
/*   Updated: 2023/10/30 00:03:00 by hbalasan         ###   ########.fr       */
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
		if (!strncmp(envp[i[1]], var, j))
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

/* "export" is used to define and modify environment variables,
making them accessible to child processes */
int	mini_export(t_prompt *prompt)
{
	char	**arg;
	bool	flag;
	int		i[2];

	arg = ((t_command *)prompt->cmds)->full_cmd;
	if (ft_matrixlen(arg) >= 2)
	{
		i[0] = 1;
		while (arg[i[0]])
		{
			flag = find_from_envp(arg[i[0]], prompt->envp, i);
			if (flag)
			{
				free(prompt->envp[i[1]]);
				prompt->envp[i[1]] = ft_strdup(arg[i[0]]);
			}
			else
				prompt->envp = ft_extend_matrix(prompt->envp, arg[i[0]]);
			i[0]++;
		}
	}
	return (0);
}
