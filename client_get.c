/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/29 15:35:48 by aleung-c          #+#    #+#             */
/*   Updated: 2015/05/12 12:04:34 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void	client_get(int sock, char *buf_serv, char *buf)
{
	t_transfer		tr;

	if (!ft_strstr(buf_serv, "ERROR"))
	{
		tr.file_name = ft_strsplit(buf, ' ')[1];
		tr.file_size = ft_atoi(ft_strsplit(buf_serv, '=')[1]);
		printf("File name = %s, size to receive = %d\n", tr.file_name,
					tr.file_size);
		printf("name = %s\n", tr.file_name);
		write_sock(sock, "READY to receive file.", 1);
		tr.fd_newfile = open(tr.file_name, O_WRONLY | O_CREAT | O_APPEND,
										S_IRWXU | S_IRGRP | S_IROTH);
		client_receive(sock, tr.fd_newfile, tr.file_size);
		check_filesize(tr.fd_newfile, tr.file_name, tr.file_size);
		close(tr.fd_newfile);
	}
	else
		return ;
}

void	client_receive(int sock, int fd_newfile, int file_size)
{
	char			*buf_file;
	int				ret_serv;
	t_progression	pr;

	buf_file = ft_strnew(FILE_BUFSIZE);
	pr.somme = 0;
	pr.prec_res = 0;
	printf("--- Transfering file :\n");
	while ((ret_serv = recv(sock, buf_file, FILE_BUFSIZE - 1, 0)) > 0)
	{
		buf_file[ret_serv] = '\0';
		pr.somme += ret_serv;
		write(fd_newfile, buf_file, ret_serv);
		pr.percent = (double)pr.somme * 100.00 / file_size;
		if (pr.percent > 100)
			pr.percent = 100;
		if (pr.percent != pr.prec_res)
			printf("\tFile transfer at %d %%\n", pr.percent);
		pr.prec_res = pr.percent;
		if (pr.somme >= file_size)
			break ;
	}
	free(buf_file);
	ft_putstr("SUCCESS - File received\n");
}

void	check_filesize(int fd_newfile, char *file_name, int file_size)
{
	struct stat file_stat;

	fstat(fd_newfile, &file_stat);
	printf("File name = %s, received size = %d\n", file_name,
			(int)file_stat.st_size);
	if (file_stat.st_size == file_size)
		ft_putstr("SUCCESS - File reception - OK\n");
	else
		ft_putstr("ERROR - File size incorrect. File may be corrupted.\n");
}
