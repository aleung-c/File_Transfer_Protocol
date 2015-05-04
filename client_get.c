/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/29 15:35:48 by aleung-c          #+#    #+#             */
/*   Updated: 2015/05/04 17:12:18 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void client_get(int sock, char *buf_serv) // BUG avc fichiers non textes...
{
	int ret_serv;
	int size_to_get;
	char *buf;
	char *file_name;
	int fd_newfile;
	char *buf_file;
	struct stat file_stat;

	if (!ft_strstr(buf_serv, "ERROR")) // check READ 1 si error argunment. sinon receive size OK
	{
		// receive size.
		file_name = ft_strsplit(buf_serv, '=')[2];
		size_to_get = ft_atoi(ft_strsplit(buf_serv, '=')[1]);
		printf("size to get = %d\n", size_to_get);
		printf("name = %s\n", file_name);
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
		buf_file = ft_strnew(size_to_get);
		ret_serv = read(sock, buf_file, size_to_get);
		// read content.
		buf_file[ret_serv] = '\0';
		// mettre le buf dans un fichier => OPEN O_CREAT.
		fd_newfile = open(file_name, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU | S_IRGRP | S_IROTH );
		write(fd_newfile, buf_file, size_to_get);
		close(fd_newfile);
		//ft_putstr(buf_file);
		ft_putstr("SUCCESS - File received\n");
		

		stat(file_name, &file_stat);
		printf("name = %s, size = %d\n", file_name, (int)file_stat.st_size);
		if (file_stat.st_size == size_to_get)
		{
			ft_putstr("SUCCESS - File reception OK\n");
		}
		else
			ft_putstr("ERROR - File size incorrect. File may be corrupted");
		ft_putstr(" --- READ 2\n");

		// puis, check si taille recue est la bonne. si oui, return.
		// si non, erase file et error msg.
	}
	else
		return ;
}