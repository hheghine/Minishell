/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_bultins1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 02:28:45 by hbalasan          #+#    #+#             */
/*   Updated: 2023/10/27 03:33:57 by hbalasan         ###   ########.fr       */
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