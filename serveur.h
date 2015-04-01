/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/27 18:50:16 by aleung-c          #+#    #+#             */
/*   Updated: 2015/04/01 13:54:19 by aleung-c         ###   ########.fr       */
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

# include <stdio.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <fcntl.h>
# include "./libft/libft.h"

/*
**	Functions prototypes.
*/

void check_input(int cs, char *buf_client);

#endif