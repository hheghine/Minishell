/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cmdtrim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 22:06:14 by hbalasan          #+#    #+#             */
/*   Updated: 2023/10/21 00:00:06 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_words(const char *s, char *set, int i[2])
{
	int	q[2];

	q[0] = 0;
	q[1] = 0;
	while (s[i[0]])
	{
		if (!ft_strchr(set, s[i[0]]))
		{
			i[1]++;
			while (s[i[0]] && (!ft_strchr(set, s[i[0]]) || q[0]))
			{
				if (!q[1] && (s[i[0]] == '\"' || s[i[0]] == '\''))
					q[1] = s[i[0]];
				q[0] = (q[0] + (q[1] == s[i[0]])) % 2;
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

static char	**fill_array(char **trimmed, const char *s, char *set, int i[3])
{
	int	len;
	int	q[2];

	q[0] = 0;
	q[1] = 0;
	len = ft_strlen(s);
	while (s[i[0]])
	{
		while (s[i[0]] && ft_strchr(set, s[i[0]]))
			i[0]++;
		i[1] = i[0];
		while (s[i[0]] && (!ft_strchr(set, s[i[0]]) || q[0] || q[1]))
		{
			q[0] = (q[0] + (!q[1] && s[i[0]] == '\'')) % 2;
			q[1] = (q[1] + (!q[0] && s[i[0]] == '\"')) % 2;
			i[0]++;
		}
		if (i[1] >= len)
			trimmed[i[2]++] = NULL;
		else
			trimmed[i[2]++] = ft_substr(s, i[1], i[0] - i[1]);
	}
	return (trimmed);
}

char	**cmd_trim(const char *s, char *set)
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
	if (!s)
		return (NULL);
	wcount = count_words(s, set, idx);
	if (wcount == -1)
		return (mini_error(EQUOTE, NULL, 1)); // return (NULL)
	trimmed = (char **)malloc(sizeof(char *) * (wcount + 1));
	if (!trimmed)
		return (NULL);
	trimmed = fill_array(trimmed, s, set, i);
	trimmed[wcount] = NULL;
	// for (int i = 0; trimmed[i]; i++)
	// {
	// 	for (int j = 0; trimmed[i][j]; j++)
	// 		printf("%c", trimmed[i][j]);
	// 	printf("\n");
	// }
	return (trimmed);
}
