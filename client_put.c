/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_put.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/07 11:55:19 by aleung-c          #+#    #+#             */
/*   Updated: 2015/05/11 16:12:12 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void	client_put(int sock, char *buf_serv, char *input)
{
	char			**input_split;
	int				fd;
	t_transfer		tr;

	input = clean_line(input);
	input_split = ft_strsplit(input, ' ');
	tr.file_name = input_split[1];
	if (!ft_strstr(buf_serv, "ERROR"))
	{
		if ((fd = open(tr.file_name, O_RDONLY)) < 0)
		{
			write_sock(sock, "ERROR - File not existing\nAborting put.", 1);
			return ;
		}
		if (client_prepare_put(sock, fd, &tr) != 0)
			return ;
		if (tr.file_size == 0)
		{
			write_sock(sock, "ERROR - Not a valid file\nAborting put.", 1);
			return ;
		}
		ready_send(sock, &tr);
	}
}

int		client_prepare_put(int sock, int fd, t_transfer *tr)
{
	char			*send_datas;

	if (client_put_filecheck(sock, fd, tr) != 0)
		return (-1);
	send_datas = ft_strjoin("name=", tr->file_name);
	send_datas = ft_strjoin(send_datas, " ");
	send_datas = ft_strjoin(send_datas, ft_strjoin("size=",
	ft_itoa(tr->file_size)));
	tr->file = (char *)mmap(0, tr->file_size + 1, PROT_READ,
	MAP_FILE | MAP_PRIVATE, fd, 0);
	if (tr->file == MAP_FAILED)
	{
		write_sock(sock, "ERROR - Not a valid file\nAborting put.", 1);
		return (-1);
	}
	write_sock(sock, send_datas, 1);
	free(send_datas);
	return (0);
}

int		client_put_filecheck(int sock, int fd, t_transfer *tr)
{
	struct stat		file_stat;

	fstat(fd, &file_stat);
	tr->file_size = (int)file_stat.st_size;
	if (tr->file_size > MAX_FILESIZE)
	{
		write_sock(sock,
		"ERROR - File too big. Max = 1800Mo\nAborting put.", 1);
		return (-1);
	}
	if (ft_strstr(tr->file_name, "/") || ft_strstr(tr->file_name, "\\"))
	{
		write_sock(sock, "ERROR - File name incorrect.", 1);
		return (-1);
	}
	return (0);
}

void	ready_send(int sock, t_transfer *tr)
{
	int		ret_serv;
	char	*buf_serv;

	buf_serv = ft_strnew(MSG_BUFSIZE);
	ret_serv = read(sock, buf_serv, MSG_BUFSIZE - 1);
	buf_serv[ret_serv] = '\0';
	ft_putstr(KYEL);
	ft_putstr("[Received]: ");
	ft_putstr(RESET);
	printf("%s\n", buf_serv);
	if (ft_strstr(buf_serv, "READY"))
	{
		ft_putstr("SUCCESS - READY received\nSending ...\n");
		send(sock, tr->file, tr->file_size, 0);
		ft_putstr("SUCCESS - File sent.\n");
	}
	else
	{
		write_sock(sock, "ERROR - Ready signal not received.\n", 1);
		return ;
	}
}
