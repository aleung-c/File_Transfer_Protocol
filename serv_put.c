/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_put.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/07 11:49:58 by aleung-c          #+#    #+#             */
/*   Updated: 2015/05/08 17:43:36 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void	go_put(int cs, char **input)
{
	t_msg			msg;
	t_transfer		tr;

	if (!input[1])
		write_cs(cs, "ERROR - Missing argument\nUsage: put <file> serv\n", 1);
	else
	{
		write_cs(cs, "SUCCESS - put ready to receive name and size.", 1);
		msg.ret_client = read(cs, msg.buf_client, MSG_BUFSIZE - 1);
		msg.buf_client[msg.ret_client] = '\0';
		if (!ft_strstr(msg.buf_client, "ERROR"))
		{
			prepare_receive(cs, &msg, &tr);
			check_filesize(tr.fd_newfile, tr.file_name, tr.file_size);
			close(tr.fd_newfile);
			ft_putstr("SERVEUR - PUT - END\n");
		}
		else
			ft_putstr("ERROR - put aborted.\n");
	}
}

void	prepare_receive(int cs, t_msg *msg, t_transfer *tr)
{
	tr->file_name = ft_strsplit(ft_strsplit(msg->buf_client, '=')[1],
								' ')[0];
	tr->file_size = ft_atoi(ft_strsplit(msg->buf_client, '=')[2]);
	printf("File name = %s, size to receive = %d\n", tr->file_name,
			tr->file_size);
	write_cs(cs, "SUCCESS - SERVER READY to receive.\n", 1);
	tr->fd_newfile = open(tr->file_name, O_WRONLY | O_CREAT | O_APPEND,
						S_IRWXU | S_IRGRP | S_IROTH);
	serv_receive(cs, tr->fd_newfile, tr->file_size);
}

void	serv_receive(int cs, int fd_newfile, int file_size)
{
	char			*buf_file;
	int				ret_client;
	t_progression	pr;

	buf_file = ft_strnew(FILE_BUFSIZE);
	pr.somme = 0;
	pr.prec_res = 0;
	printf("--- Transfering file :\n");
	while ((ret_client = recv(cs, buf_file, FILE_BUFSIZE - 1, 0)) > 0)
	{
		buf_file[ret_client] = '\0';
		pr.somme += ret_client;
		write(fd_newfile, buf_file, ret_client);
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
		ft_putstr("ERROR - File size incorrect. File may be corrupted\n");
}
