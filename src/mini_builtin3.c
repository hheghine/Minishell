/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_builtin3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 23:27:54 by hbalasan          #+#    #+#             */
/*   Updated: 2023/12/22 20:15:09 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* when there are two or more arguments */
static int	mini_export_helper(t_prompt *p, t_list *c, char **sp, int i[3])
{
	t_command	*cmd;

	cmd = (t_command *)c->content;
	i[0] = 1;
	if (!ft_isalpha(*(cmd)->full_cmd[i[0]]) && *(cmd)->full_cmd[i[0]] != '_')
	{
		print_error_msg_fd("export: not a valid identifier", 1);
		return (1);
	}
	while ((cmd)->full_cmd[i[0]])
	{
		sp = ft_split_once(cmd->full_cmd[i[0]], '=');
		i[2] = find_from_envp(sp[0], p->envp, i);
		if (i[2])
		{
			free(p->envp[i[1]]);
			p->envp[i[1]] = ft_strdup((cmd)->full_cmd[i[0]]);
		}
		else
			p->envp = ft_extend_matrix(p->envp, \
				cmd->full_cmd[i[0]]);
		i[0]++;
		ft_free_matrix(&sp);
	}
	return (0);
}

/* "export" is used to define and modify environment variables,
making them accessible to child processes */
int	mini_export(t_prompt *p, t_list *c)
{
	char		**splitted;
	int			i[3];

	splitted = NULL;
	if (ft_matrixlen(((t_command *)c->content)->full_cmd) == 1)
		mini_export_noarg(p);
	if (ft_matrixlen(((t_command *)c->content)->full_cmd) >= 2)
	{
		if (mini_export_helper(p, c, splitted, i))
			return (1);
	}
	return (0);
}
