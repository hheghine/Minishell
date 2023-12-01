/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cmdtrim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmnatsak <tmnatsak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 22:06:14 by hbalasan          #+#    #+#             */
/*   Updated: 2023/12/01 11:54:38 by tmnatsak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_words(const char *str, char *set, int i[2], t_prompt *prompt)
{
	int	q[2];

	q[0] = 0;
	q[1] = 0;
	while (str[i[0]])
	{
		if (!ft_strchr(set, str[i[0]]))
		{
			i[1]++;
			while (str[i[0]] && (!ft_strchr(set, str[i[0]]) || q[0]))
			{
				if (!q[1] && (str[i[0]] == '\"' || str[i[0]] == '\''))
				{
					q[1] = str[i[0]];
					prompt->has_comma = 1;
				}
				q[0] = (q[0] + (q[1] == str[i[0]])) % 2;
				q[1] *= (q[0] != 0);
				i[0]++;
			}
			if (q[0])
				return (-1);
		}
		else
			i[0]++;
	}
	return (i[1]);
}

static char	**fill_matrix(char **trimmed, const char *str, char *set, int i[3])
{
	int	len;
	int	q[2];

	q[0] = 0;
	q[1] = 0;
	len = ft_strlen(str);
	while (str[i[0]])
	{
		while (str[i[0]] && ft_strchr(set, str[i[0]]))
			i[0]++;
		i[1] = i[0];
		while (str[i[0]] && (!ft_strchr(set, str[i[0]]) || q[0] || q[1]))
		{
			q[0] = (q[0] + (!q[1] && str[i[0]] == '\'')) % 2;
			q[1] = (q[1] + (!q[0] && str[i[0]] == '\"')) % 2;
			i[0]++;
		}
		if (i[1] >= len)
			trimmed[i[2]++] = NULL;
		else
			trimmed[i[2]++] = ft_substr(str, i[1], i[0] - i[1]);
	}
	return (trimmed);
}

char	**cmd_trim(const char *str, char *set, t_prompt *prompt)
{
	char	**trimmed;
	int		wcount;
	int		idx[2];
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	idx[0] = 0;
	idx[1] = 0;
	if (!str)
		return (NULL);
	wcount = count_words(str, set, idx, prompt);
	if (wcount == -1)
		return (mini_error(EQUOTE, NULL, 1));
	trimmed = (char **)malloc(sizeof(char *) * (wcount + 1));
	if (!trimmed)
		return (NULL);
	trimmed = fill_matrix(trimmed, str, set, i);
	trimmed[wcount] = NULL;
	return (trimmed);
}
