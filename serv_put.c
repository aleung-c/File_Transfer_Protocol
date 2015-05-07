/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_put.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/07 11:49:58 by aleung-c          #+#    #+#             */
/*   Updated: 2015/05/07 17:30:44 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void go_put(int cs, char **input)
{
	int ret_client;
	char buf_client[1025];
	int file_size;
	char *file_name;
	int somme;
	char *buf_file;
	int fd_newfile;

	if (!input[1])
		write_cs(cs, "ERROR - Missing argument\nUsage: put <file> serv\n", 1);
	else
	{
		write_cs(cs, "SUCCESS - put ready to receive name and size.", 1);
		ret_client = read(cs, buf_client, 1024);
		buf_client[ret_client] = '\0';
		if (!ft_strstr(buf_client, "ERROR"))
		{
			file_name = ft_strsplit(ft_strsplit(buf_client, '=')[1], ' ')[0];
			file_size = ft_atoi(ft_strsplit(buf_client, '=')[2]);
			// ft_putstr(buf_client);
			printf("name = %s, size = %d\n", file_name, file_size);
			write_cs(cs, "SUCCESS - READY to receive.", 1); // send READY signal.

			// receive FILE.
			buf_file = ft_strnew(1025);
			somme = 0;
			fd_newfile = open(file_name, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU | S_IRGRP | S_IROTH );
			while ((ret_client = recv(cs, buf_file, 1024, 0)) > 0)
			{
				buf_file[ret_client] = '\0';
				somme += ret_client;
				write(fd_newfile, buf_file, ret_client); // write in file.
				ft_putnbr(somme);
				// ft_putstr(buf_file);
				ft_putchar('\n');
				if (somme >= file_size)
					break;
			}
			free(buf_file);
			ft_putstr("SUCCESS - File received\n");
			return ;
		}
		else
		{
			ft_putstr("ERROR - put aborted.\n");
			return ;
		}
	}
}