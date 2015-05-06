/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/27 18:50:16 by aleung-c          #+#    #+#             */
/*   Updated: 2015/05/06 18:16:50 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEUR_H
# define SERVEUR_H

# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"
# define RESET "\033[0m"

# define MAX_FILESIZE 524288000

# include <stdio.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <fcntl.h>
# include "./libft/libft.h"
# include <sys/stat.h>
# include <sys/mman.h>
# include <sys/types.h>

char *home;

/*
**	Functions prototypes - Serveur.
*/

void	check_input(int cs, char *buf_client);
void	go_ls(int cs, char **input);
void	go_pwd(int cs, char **input);
void	go_cd(int cs, char **input);
void	change_dir(char *path);
void	go_get(int cs, char **input);
void	write_cs(int cs,  char *text, int visible);
void	file_transfer(int cs, char *input, int fd);

/*
**	Functions prototypes - Client.
*/

void client_get(int cs, char *buf_serv, char *buf);


#endif
