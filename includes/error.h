/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 01:53:08 by hbalasan          #+#    #+#             */
/*   Updated: 2023/10/28 00:22:11 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

typedef enum e_error
{
	EPERM = 1, // permission denied: 126
	EMEM, // no memory left on device 
	NOTDIR, // Not a directory: 
	ISDIR, // Is a directory: 
	NDIR, // No such file or directory: 
	ECMD, // command not found: 127
	EFORK, // fork failed
	EPIPE, // error creating pipe
	EPIPEND, // syntax error near unexpected token `|'
	DUPERR, // dup2 failed
	EQUOTE // error while looking for matching quote
} e_error;

/************************mini_error.c************************/
void	error_msg(char *msg);
void	*mini_error(int errmsg, char *param, int errcode);
void	print_error_msg_fd(char *msg);
void	mini_cd_error(char **full_cmd, char **str);
/************************************************************/

#endif