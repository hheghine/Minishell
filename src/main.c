/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:21:22 by hbalasan          #+#    #+#             */
/*   Updated: 2023/12/24 22:16:50 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_status;

void	init_varp(t_prompt *prompt, char **argv)
{
	char	*str;
	char	*num;

	str = getcwd(NULL, 0);
	prompt->envp = set_env("PWD", str, prompt->envp);
	free(str);
	str = get_env("SHLVL", prompt->envp, -1);
	if (!str || ft_atoi(str) <= 0)
		num = ft_strdup("1");
	else
		num = ft_itoa(ft_atoi(str) + 1);
	free(str);
	prompt->envp = set_env("SHLVL", num, prompt->envp);
	free(num);
	str = get_env("PATH", prompt->envp, -1);
	if (!str)
		prompt->envp = set_env("PATH", \
		"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", prompt->envp);
	free(str);
	str = get_env("_", prompt->envp, -1);
	if (!str)
		prompt->envp = set_env("_", argv[0], prompt->envp);
	free(str);
}

void	init_prompt(t_prompt *prompt, char **argv, char **env)
{
	prompt->cmds = NULL;
	prompt->envp = ft_dup_matrix(env);
	prompt->pid = getpid();
	prompt->has_comma = 0;
	g_status = 0;
	init_varp(prompt, argv);
}

int	main(int argc, char **argv, char **env)
{
	t_prompt	prompt;
	char		*str;
	char		*cmd ;

	if (argc > 1)
		error_msg("Minishell doesn't take any arguments!\033[0m");
	printf("\n%s\n\n", MINISHELL1);
	init_prompt(&prompt, argv, env);
	while (1)
	{
		sigaction_handler1();
		str = get_prompt(prompt);
		if (str)
		{
			cmd = readline(str);
			free(str);
		}
		else
			cmd = readline(READLINE_MSG1);
		if (!check_args(cmd, &prompt))
			break ;
		prompt.has_comma = 0;
	}
	free_prompt(&prompt);
	return (g_status);
}
