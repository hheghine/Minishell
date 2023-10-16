/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visuals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:23:37 by hbalasan          #+#    #+#             */
/*   Updated: 2023/10/17 03:55:18 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALS_H
# define VISUALS_H

/*********ANSI BASIC COLORS*********/
# define BLACK_BOLD		"\033[1;30m"
# define RED_BOLD		"\033[1;31m"
# define GREEN_BOLD		"\033[1;32m"
# define YELLOW_BOLD	"\033[1;33m"
# define BLUE_BOLD		"\033[1;34m"
# define MAGENTA_BOLD	"\033[1;35m"
# define CYAN_BOLD		"\033[1;36m"
# define WHITE_BOLD		"\033[1;37m"
# define RESET_COLOR	"\033[0m"
/************ANSI COLORS************/
# define BLACK			"\033[30m"
# define RED			"\033[31m"
# define LIGHT_RED		"\033[91m"
# define GREEN			"\033[32m"
# define LIGHT_GREEN	"\033[92m"
# define YELLOW			"\033[33m"
# define LIGHT_YELLOW	"\033[93m"
# define BLUE			"\033[34m"
# define LIGHT_BLUE		"\033[94m"
# define MAGENTA		"\033[35m"
# define LIGHT_MAGENTA	"\033[95m"
# define CYAN			"\033[36m"
# define LIGHT_CYAN		"\033[96m"
# define WHITE			"\033[37m"
# define GREY			"\033[90m"
# define LIGHT_GREY		"\033[37m"
/**********************************/
# define PURPLE			"\033[0;34m"
# define PINK			"\033[0;35m"
# define SKY			"\033[0;36m"
/**********************************/

/*
#######################################################
# !/bin/bash                                          #
#                                                     #
#    This file echoes a bunch of color codes to the   #
#    terminal to demonstrate what's available.  Each  #
#    line is the color code of one forground color,   #
#    out of 17 (default + 16 escapes), followed by a  #
#    test use of that color on all nine background    #
#    colors (default + 8 escapes).                    #
#                                                     #
#######################################################

T='gYw'   # The test text

echo -e "\n                 40m     41m     42m     43m\
     44m     45m     46m     47m";

for FGs in '    m' '   1m' '  30m' '1;30m' '  31m' '1;31m' '  32m' \
           '1;32m' '  33m' '1;33m' '  34m' '1;34m' '  35m' '1;35m' \
           '  36m' '1;36m' '  37m' '1;37m';
  do FG=${FGs// /}
  echo -en " $FGs \033[$FG  $T  "
  for BG in 40m 41m 42m 43m 44m 45m 46m 47m;
    do echo -en "$EINS \033[$FG\033[$BG  $T  \033[0m";
  done
  echo;
done
echo
*/


# define MINISHELL0	"\033[96m╔═══════════════════════════════════════════════════════════════════════════════╗\n\
║                                                                               ║\n\
║      \033[35m ███╗░░░███╗██╗███╗░░██╗██╗░██████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░      \033[96m║\n\
║      \033[35m ████╗░████║██║████╗░██║██║██╔════╝██║░░██║██╔════╝██║░░░░░██║░░░░░      \033[96m║\n\
║     \033[35m  ██╔████╔██║██║██╔██╗██║██║╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░      \033[96m║\n\
║     \033[35m  ██║╚██╔╝██║██║██║╚████║██║░╚═══██╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░      \033[96m║\n\
║     \033[35m  ██║░╚═╝░██║██║██║░╚███║██║██████╔╝██║░░██║███████╗███████╗███████╗      \033[96m║\n\
║                                                                               ║\n\
╚═══════════════════════════════════════════════════════════════════════════════╝\n"

# define MINISHELL1	"\033[96m╔═══════════════════════════════════════════════════════════════════════════════╗\n\
║ ✧      ✧   ✧           ✧  ✧      ✧         ✧    ✧        ✧✧       ✧     ✧   ✧ ║\n\
║\033[0;35m    ✧  ███╗░░░███╗██╗███╗░░██╗██╗░██████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░  ✧   \033[96m║\n\
║\033[0;35m  ✧    ████╗░████║██║████╗░██║██║██╔════╝██║░░██║██╔════╝██║░░░░░██║░░░░░    ✧ \033[96m║\n\
║\033[0;35m       ██╔████╔██║██║██╔██╗██║██║╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░ ✧    \033[96m║\n\
║\033[0;34m    ✧  ██║╚██╔╝██║██║██║╚████║██║░╚═══██╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░    ✧ \033[96m║\n\
║\033[0;36m ✧     ██║░╚═╝░██║██║██║░╚███║██║██████╔╝██║░░██║███████╗███████╗███████╗  ✧   \033[96m║\n\
║  ✧   ✧      ✧   ✧      ✧  ✧       ✧           ✧ ✧         ✧   ✧     ✧     ✧   ║\n\
╚═══════════════════════════════════════════════════════════════════════════════╝\n"

# define MINISHELL2	"\033[95m╔═══════════════════════════════════════════════════════════════════╗\n\
║                                                                   ║\n\
║      \033[32m ░▒█▀▄▀█░▀█▀░▒█▄░▒█░▀█▀░▒█▀▀▀█░▒█░▒█░▒█▀▀▀░▒█░░░░▒█░░░       \033[95m║\n\
║      \033[32m ░▒█▒█▒█░▒█░░▒█▒█▒█░▒█░░░▀▀▀▄▄░▒█▀▀█░▒█▀▀▀░▒█░░░░▒█░░░       \033[95m║\n\
║      \033[32m ░▒█░░▒█░▄█▄░▒█░░▀█░▄█▄░▒█▄▄▄█░▒█░▒█░▒█▄▄▄░▒█▄▄█░▒█▄▄█       \033[95m║\n\
║                                                                   ║\n\
╚═══════════════════════════════════════════════════════════════════╝\n"

# define READLINE_MSG	"\033[1;30muser\033[1;35m✧ mini\033[1;36mshell\033[35m$\033[1;30m~/Desktop> \033[0m"

#endif
