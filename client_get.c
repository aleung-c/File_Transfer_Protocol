/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/29 15:35:48 by aleung-c          #+#    #+#             */
/*   Updated: 2015/04/30 16:30:11 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void client_get(int sock, char *buf_serv) // a peu pres OK.
{
	int ret_serv;
	int size_to_get;
	char *buf;

	ft_putstr("hey\n");
	if (!ft_strstr(buf_serv, "ERROR")) // check READ 1 si error argunment. sinon receive size OK
	{
		// receive size.
		size_to_get = ft_atoi(ft_strsplit(buf_serv, '=')[1]);
		printf("size to get = %d\n", size_to_get);
		// ft_putchar('\n');
		//free(buf_serv);

		// send "ready" signal.
		buf = ft_strdup("READY to receive file.");
		ft_putstr(KGRN);
		ft_putstr("[Sent]: ");
		ft_putstr(RESET);
		printf("%s\n", buf);
		write(sock, buf, ft_strlen(buf));

		// receive FILE.
		ret_serv = read(sock, buf_serv, size_to_get);
		// read content.
		buf_serv[ret_serv] = '\0';
		// mettre le buf dans un fichier => OPEN O_CREATE.
		ft_putstr(buf_serv);
		ft_putstr(" --- READ 2\n");

		// puis, check si taille recue est la bonne. si oui, return.
		// si non, erase file et error msg.
	}
	else
		return ;
}