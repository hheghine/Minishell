/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmnatsak <tmnatsak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 01:53:08 by hbalasan          #+#    #+#             */
/*   Updated: 2023/12/24 18:18:51 by tmnatsak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

void	error_msg(char *msg);
void	*mini_error(int errmsg, char *param, int errcode);
void	print_error_msg_fd(char *msg, int nl);
void	mini_cd_error(char **full_cmd, char **str);

typedef enum s_error
{
	EPERM = 1,
	EMEM,
	NOTDIR,
	ISDIR,
	NDIR,
	ECMD,
	EFORK,
	EPIPE,
	EPIPEND,
	DUPERR,
	EQUOTE
}	t_error;

#endif