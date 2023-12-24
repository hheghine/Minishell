/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmnatsak <tmnatsak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 20:26:58 by hbalasan          #+#    #+#             */
/*   Updated: 2023/12/24 19:39:52 by tmnatsak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_from_envp(char *var, char **envp, int i[2])
{
	int	j;

	i[1] = 0;
	j = ft_strlen(var);
	while (envp[i[1]])
	{
		if (!ft_strncmp(envp[i[1]], var, j))
			return (1);
		i[1]++;
	}
	return (0);
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

void	export_declare_x(char **m)
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

static void	equal_found(char **temp, char **splitted, char *str[2], int i)
{
	splitted = ft_split_once(temp[i], '=');
	str[0] = ft_strjoin(splitted[0], "\"");
	str[1] = ft_strjoin(str[0], splitted[1]);
	free(str[0]);
	str[0] = ft_strjoin(str[1], "\"");
	free(str[1]);
	str[1] = temp[i];
	temp[i] = str[0];
	free(str[1]);
	ft_free_matrix(&splitted);
}

void	mini_export_noarg(t_prompt *prompt)
{
	char	**temp;
	char	**splitted;
	char	*str[2];
	int		i[2];

	splitted = NULL;
	temp = ft_alphabetical_matrix(prompt->envp);
	i[0] = -1;
	while (temp[++i[0]])
	{
		i[1] = ft_strchr_idx(temp[i[0]], '=');
		if (i[1] != -1)
			equal_found(temp, splitted, str, i[0]);
	}
	export_declare_x(temp);
	ft_printmatrix_fd(temp, 1);
	ft_free_matrix(&temp);
}
