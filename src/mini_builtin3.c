/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_builtin3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 23:27:54 by hbalasan          #+#    #+#             */
/*   Updated: 2023/11/11 20:08:12 by hbalasan         ###   ########.fr       */
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
	char	**splitted;
	char	*str[2];
	int		i;

	temp = ft_alphabetical_matrix(prompt->envp);
	i = -1;
	while (temp[++i])
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
	export_declare_x(temp);
	ft_printmatrix_fd(temp, 1);
	ft_free_matrix(&temp);
}

/* "export" is used to define and modify environment variables,
making them accessible to child processes */
int	mini_export(t_prompt *p, t_list *c)
{
	char		**splitted;
	int			i[3];

	if (ft_matrixlen(((t_command *)c->content)->full_cmd) == 1)
		mini_export_noarg(p);
	if (ft_matrixlen(((t_command *)c->content)->full_cmd) >= 2)
	{
		i[0] = 1;
		if (!ft_isalpha(*((t_command *)c->content)->full_cmd[i[0]]) && *((t_command *)c->content)->full_cmd[i[0]] != '_')
		{
			print_error_msg_fd("export: not a valid identifier", 1);
			return (1);
		}
		while (((t_command *)c->content)->full_cmd[i[0]])
		{
			splitted = ft_split_once(((t_command *)c->content)->full_cmd[i[0]], '=');
			i[2] = find_from_envp(splitted[0], p->envp, i);
			if (i[2])
			{
				free(p->envp[i[1]]);
				p->envp[i[1]] = ft_strdup(((t_command *)c->content)->full_cmd[i[0]]);
			}
			else
				p->envp = ft_extend_matrix(p->envp, \
					((t_command *)c->content)->full_cmd[i[0]]);
			i[0]++;
			ft_free_matrix(&splitted);
		}
	}
	return (0);
}
