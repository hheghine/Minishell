/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:21:22 by hbalasan          #+#    #+#             */
/*   Updated: 2023/10/18 04:12:33 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	ministat;

void	init_varp(t_prompt *prompt, char **argv, char **env)
{
	char	*str;
	char	*num;

	str  = getcwd(NULL, 0);
	prompt->envp = set_env("PWD", str, prompt->envp);
	free(str);
	str = get_env("SHLVL", prompt->envp);
	if (!str || ft_atoi(str) <= 0)
		num = ft_strdup("1");
	else
		num = ft_itoa(ft_atoi(str) + 1);
	free(str);
	prompt->envp = set_env("SHLVL", num, prompt->envp);
	free(num);
	str = get_env("PATH", prompt->envp);
	if (!str)
		prompt->envp = set_env("PATH", \
		"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", prompt->envp);
	free(str);
	str = get_env("_", prompt->envp);
	if (!str)
		prompt->envp = set_env("_", argv[0], prompt->envp); // "_" (underscore) is used to store the last argument to the last executed command
	free(str);						   						// "!!" the last command that you executed
}

void	init_prompt(t_prompt *prompt, char **argv, char **env)
{
	prompt->cmds = NULL;
	prompt->envp = ft_dup_matrix(env);
	prompt->pid = getpid();
	ministat = 0;
	init_varp(prompt, argv, env);
}

int	main(int argc, char **argv, char **env)
{
	t_prompt	prompt;
	char		*str;
	char		*cmd = "";
	
	if (argc > 1)
		error_msg("Minishell doesn't take any arguments!\033[0m");
	printf("\n%s\n\n", MINISHELL1);
	init_prompt(&prompt, argv, env);
	while (1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		str = get_prompt(prompt);
		if(str)
		{
			cmd = readline(str);
			free(str);
		}
		else
			cmd = readline(READLINE_MSG1);
		if (!cmd || !ft_strncmp(cmd, "exit", 4))
		{
			printf("exit\n");
			free(cmd);
			break ;
		}
		if (ft_strlen(cmd) > 0)
    		add_history(cmd);
		free(cmd);
	}
	free_prompt(&prompt);
	return (ministat);
}