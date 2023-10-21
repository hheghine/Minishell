/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_subsplit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:14:18 by hbalasan          #+#    #+#             */
/*   Updated: 2023/10/21 20:47:36 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_words(char *str, char *set, int count)
{
	int	i;
	int	q[2];

	i = 0;
	q[0] = 0;
	q[1] = 0;
	while (str && str[i])
	{
		count ++;
		if (!ft_strchr(set, str[i]))
		{
			while (str[i] && (!ft_strchr(set, str[i]) || q[0] || q[1]))
			{
				q[0] = (q[0] + (!q[1] && str[i] == '\"')) % 2;
				q[1] = (q[1] + (!q[0] && str[i] == '\'')) % 2;
				i++;
			}
			if (q[0] || q[1])
				return (-1);
		}
		else
			i++;
	}
	return (count);
}

static char	**fill_matrix(char **splitted, char *str, char *set, int i[3])
{
	int	q[2];

	q[0] = 0;
	q[1] = 0;
	while (str && str[i[0]])
	{
		i[1] = i[0];
		if (!ft_strchr(set, str[i[0]]))
		{
			while (str[i[0]] && (!ft_strchr(set, str[i[0]]) || q[0] || q[1]))
			{
				q[0] = (q[0] + (!q[1] && str[i[0]] == '\'')) % 2;
				q[1] = (q[1] + (!q[0] && str[i[0]] == '\"')) % 2;
				i[0]++;
			}
		}
		else
			i[0]++;
		splitted[i[2]++] = ft_substr(str, i[1], i[0] - i[1]);
	}
	return (splitted);
}

char	**cmd_subsplit(const char *str, char *set)
{
	char	**splitted;
	int		wcount;
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	if (!str)
		return (NULL);
	wcount = count_words((char *)str, set, 0);
	if (wcount == -1)
		return (NULL);
	splitted = (char **)malloc(sizeof(char *) * (wcount + 1));
	if (!splitted)
		return (NULL);
	splitted = fill_matrix(splitted, (char *)str, set, i);
	splitted[wcount] = NULL;
	return (splitted);
}