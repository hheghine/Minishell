/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 00:40:21 by hbalasan          #+#    #+#             */
/*   Updated: 2023/11/11 17:39:24 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_gstatus;

char	*expand_path(char *s, int q[2], char *getpath, int i)
{
	char	*path;
	char	*temp;

	q[0] = 0;
	q[1] = 0;
	while (s && s[++i])
	{
		q[0] = (q[0] + (!q[1] && s[i] == '\'')) % 2;
		q[1] = (q[1] + (!q[0] && s[i] == '\"')) % 2;
		if (!q[0] && !q[1] && s[i] == '~' && (i == 0 || s[i - 1] != '$'))
		{
			temp = ft_substr(s, 0, i);
			path = ft_strjoin(temp, getpath);
			free(temp);
			temp = ft_substr(s, i + 1, ft_strlen(s));
			free(s);
			s = ft_strjoin(path, temp);
			free(path);
			free(temp);
			return (expand_path(s, q, getpath, i + ft_strlen(getpath) - 1));
		}
	}
	free(getpath);
	return (s);
}

char	*get_exp_var(char *s, t_prompt *prompt, int i)
{
	char	*expanded;
	char	*path;
	char	*var;
	int		pos;

	pos = ft_strchr_set(&s[i], "=|/\"\'$?>< \n") + (ft_strchr("$?", s[i]) != 0);
	if (pos == -1)
		pos = ft_strlen(s) - 1;
	expanded = ft_substr(s, 0, i - 1);
	var = get_env(&s[i], prompt->envp, ft_strchr_set(&s[i], " =|/\"\'$?>< \n"));
	if (!var && s[i] == '$')
		var = ft_itoa(prompt->pid);
	else if (!var && s[i] == '?')
		var = ft_itoa(g_gstatus);
	path = ft_strjoin(expanded, var);
	free(expanded);
	expanded = ft_strjoin(path, &s[i + pos]);
	free(path);
	free(var);
	free(s);
	return (expanded);
}

char	*expand_vars(char *s, t_prompt *prompt, int q[2], int i)
{
	q[0] = 0;
	q[1] = 0;
	while (s && s[++i])
	{
		q[0] = (q[0] + (!q[1] && s[i] == '\'')) % 2;
		q[1] = (q[1] + (!q[0] && s[i] == '\"')) % 2;
		if (!q[0] && s[i] == '$' && s[i + 1] && \
			((ft_strchr_set(&s[i + 1], "=/~%^{}+-:;,. ") && !q[1]) || \
			(ft_strchr_set(&s[i + 1], "=/~%^{}:;+-,.\"") && q[1])))
			return (expand_vars(get_exp_var(s, prompt, ++i), prompt, q, -1));
	}
	return (s);
}
