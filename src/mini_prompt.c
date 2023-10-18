/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:31:27 by hbalasan          #+#    #+#             */
/*   Updated: 2023/10/18 03:43:25 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	ministat;

char	*get_user(t_prompt prompt)
{
	char	*user;
	char	*temp;

	user = get_env("USER", prompt.envp);
	if (!user)
		user = ft_strdup("guest");
	if(!strncmp(user, "root", 4))
		temp = ft_strjoin(YELLOW, user);
	else
		temp = ft_strjoin(BLACK_BOLD, user);
	free(user);
	return (temp);
}

char	*get_home(t_prompt prompt)
{
	char	*home;
	char	*pwd;
	char	*temp;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("⚠ ");
	home = get_env("HOME", prompt.envp);
	if (home && home[0] && ft_strnstr(pwd, home, ft_strlen(pwd)))
	{
		temp = pwd;
		pwd = ft_strjoin("~", &pwd[ft_strlen(home)]);
		free(temp);
	}
	free(home);
	home = ft_strjoin(BLACK_BOLD, pwd);
	free(pwd);
	pwd = ft_strjoin(" ", home);
	free(pwd);
	return (home);
}

char	*get_prompt(t_prompt prompt)
{
	char	*temp;
	char	*temp1;
	char	*temp2;

	temp = get_user(prompt);
	temp1 = ft_strjoin(temp, READLINE_MSG);
	free(temp);
	temp2 = get_home(prompt);
	temp = ft_strjoin(temp1, temp2);
	free(temp1);
	free(temp2);
	temp1 = ft_strjoin(temp, "> ");
	free(temp);
	temp2 = ft_strjoin(temp1, DEFAULT);
	free(temp1);
	return (temp2);
}