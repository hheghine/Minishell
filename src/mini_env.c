/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:51:22 by hbalasan          #+#    #+#             */
/*   Updated: 2023/10/16 03:35:32 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env(char *varname, char **envp)
{
	int	i;
	int	n1;
	int	n2;

	i = 0;
	n1 = ft_strlen(varname);
	while (!ft_strchr(varname, '=') && envp && envp[i])
	{
		n2 = n1;
		if (n2 < ft_strchr_idx(envp[i], '='))
			n2 = ft_strchr_idx(envp[i], '=');
		if (!ft_strncmp(envp[i], varname, n2))
			return (ft_substr(envp[i], n2 + 1, ft_strlen(envp[i])));
		i++;
	}
	return (NULL);
}

char	**set_env(char *var, char *value, char **envp)
{
	int		n;
	int		i[2];
	char	*s[2];

	n = ft_strlen(var);
	i[0] = -1;
	s[0] = ft_strjoin(var, "=");
	s[1] = ft_strjoin(s[0], value);
	free(s[0]);
	while (!ft_strchr(var, '=') && envp && envp[++i[0]])
	{
		i[1] = n;
		if (i[1] < ft_strchr_idx(envp[i[0]], '='))
			i[1] = ft_strchr_idx(envp[i[0]], '=');
		if (!ft_strncmp(envp[i[0]], var, i[1]))
		{
			s[0] = envp[i[0]];
			envp[i[0]] = s[1]; // updates the environment variable with the new value
			free(s[0]);
			return (envp);
		}
	}
	envp = ft_extend_matrix(envp, s[1]); // adds the new environment variable to the existing envp
	free(s[1]);
	return (envp);
}
