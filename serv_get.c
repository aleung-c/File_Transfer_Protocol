/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/28 17:18:00 by aleung-c          #+#    #+#             */
/*   Updated: 2015/05/11 15:28:06 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void	go_get(int cs, char **input)
{
	int fd;

	if (!input[1])
		write_cs(cs, "ERROR - Missing argument\nUsage: get <file>", 1);
	else
	{
		if (ft_strstr(input[1], "/") || ft_strstr(input[1], "\\"))
		{
			write_cs(cs, "ERROR - File name incorrect", 1);
			return ;
		}
		if ((fd = open(input[1], O_RDONLY)) < 0)
			write_cs(cs, "ERROR - File not existing", 1);
		else
			file_transfer(cs, fd);
	}
}

void	file_transfer(int cs, int fd)
{
	t_msg		msg;
	t_transfer	tr;

	if (serv_prepare_send(cs, fd, &tr) != 0)
		return ;
	msg.ret_client = read(cs, msg.buf_client, 1025);
	msg.buf_client[msg.ret_client] = '\0';
	ft_putstr(KGRN);
	ft_putstr("[Received]: ");
	ft_putstr(RESET);
	printf("%s\n", msg.buf_client);
	if (ft_strstr(msg.buf_client, "READY"))
	{
		ft_putstr("SUCCESS - READY received\nSending ...\n");
		send(cs, tr.file, tr.file_size, 0);
	}
	else
		write_cs(cs, "ERROR - READY not received. Aborting get.", 1);
	ft_putstr("SERVEUR GET - END\n");
	return ;
}

int		serv_prepare_send(int cs, int fd, t_transfer *tr)
{
	struct stat		file_stat;

	fstat(fd, &file_stat);
	tr->file_size = (int)file_stat.st_size;
	if (file_stat.st_size > MAX_FILESIZE)
	{
		write_cs(cs, "ERROR - File too big. Max = 1800Mo\n", 1);
		return (-1);
	}
	else if (file_stat.st_size == 0)
	{
		write_cs(cs, "ERROR - Empty or corrupted file\n", 1);
		return (-1);
	}
	tr->file = (char *)mmap(0, tr->file_size + 1,
		PROT_READ, MAP_FILE | MAP_PRIVATE, fd, 0);
	if (tr->file == MAP_FAILED)
	{
		write_cs(cs, "ERROR - Not a valid file", 1);
		return (-1);
	}
	else
		printf("mmap : SUCCESS\n");
	serv_send_datas(cs, tr);
	return (0);
}

void	serv_send_datas(int cs, t_transfer *tr)
{
	char			*send_datas;

	send_datas = ft_strjoin("SUCCESS - get - AWAITING READY SIGNAL: size=",
	ft_itoa(tr->file_size));
	ft_putstr(KGRN);
	ft_putstr("[Sent]: ");
	ft_putstr(RESET);
	printf("%s\n", send_datas);
	write(cs, send_datas, ft_strlen(send_datas));
}
