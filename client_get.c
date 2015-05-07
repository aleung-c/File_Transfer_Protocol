/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/29 15:35:48 by aleung-c          #+#    #+#             */
/*   Updated: 2015/05/07 17:00:45 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void client_get(int sock, char *buf_serv, char *buf) // A FAIRE envoyer nom du fichier dedans, pour securite.
{
	int ret_serv;
	int size_to_get;
	char *file_name;
	int fd_newfile;
	char *buf_file;
	struct stat file_stat;
	int somme;

	if (buf)
	{
		ft_putendl(buf);
	}
	if (!ft_strstr(buf_serv, "ERROR")) // check READ 1 si error argunment. sinon receive size OK
	{
		// receive size.
		file_name = ft_strsplit(buf, ' ')[1];
		size_to_get = ft_atoi(ft_strsplit(buf_serv, '=')[1]);
		printf("size to get = %d\n", size_to_get);
		printf("name = %s\n", file_name);

		// send "ready" signal.
		write_sock(sock, "READY to receive file.", 1);

		// receive FILE.
		buf_file = ft_strnew(1025);
		somme = 0;
		fd_newfile = open(file_name, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU | S_IRGRP | S_IROTH );
		while ((ret_serv = recv(sock, buf_file, 1024, 0)) > 0)
		{
			buf_file[ret_serv] = '\0';
			somme += ret_serv;
			write(fd_newfile, buf_file, ret_serv); // write in file.
			//ft_putnbr(somme);
			// ft_putstr(buf_file);
			// ft_putchar('\n');
			if (somme >= size_to_get)
				break;
		}
		free(buf_file);
		ft_putstr("SUCCESS - File received\n");

		// Check file size.
		fstat(fd_newfile, &file_stat);
		printf("name = %s, size = %d\n", file_name, (int)file_stat.st_size);
		if (file_stat.st_size == size_to_get)
			ft_putstr("SUCCESS - File reception OK\n");
		else
			ft_putstr("ERROR - File size incorrect. File may be corrupted");
		ft_putstr(" --- READ 2\n");
		// puis, check si taille recue est la bonne. si oui, return.
		// si non, erase file et error msg.
		close(fd_newfile);
	}
	else
		return ;
}