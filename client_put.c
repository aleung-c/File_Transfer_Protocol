/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_put.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/07 11:55:19 by aleung-c          #+#    #+#             */
/*   Updated: 2015/05/07 17:28:17 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void client_put(int sock, char *buf_serv, char *input)
{
	char **input_split;
	int ret_serv;
	char *file_name;
	int file_size;
	int fd;
	char *send_datas;
	struct stat file_stat;
	char *file;

	ft_putstr(input);
	ft_putchar('\n');
	// get input in tb;
	input = clean_line(input);
	input_split = ft_strsplit(input, ' ');
	file_name = input_split[1];
	if (!ft_strstr(buf_serv, "ERROR")) // check READ 1 si error argument. sinon send name + size
	{
		if ((fd = open(file_name, O_RDONLY)) < 0)
		{
			write_sock(sock, "ERROR - File not existing", 1);
			return ;
		}
		ft_putstr("FILE OK\n");
		fstat(fd, &file_stat);
		file_size = (int)file_stat.st_size;
		ft_putstr("PUT OK\n");
		// send name + size;
		send_datas = ft_strjoin("name=", file_name);
		send_datas = ft_strjoin(send_datas, " ");
		send_datas = ft_strjoin(send_datas, ft_strjoin("size=", ft_itoa(file_size)));
		write_sock(sock, send_datas, 1); // send file data.

		printf("Client : Mapping file...\n");
		file = (char *)mmap(0, file_stat.st_size + 1, PROT_READ, MAP_FILE | MAP_PRIVATE, fd, 0);
		if (file == MAP_FAILED)
		{
			write_sock(sock, "ERROR - Not a valid file", 1);
			return;
		}
		else
			printf("mmap : SUCCESS\n");

		// read READY signal.
		ret_serv = read(sock, buf_serv, 1025);
		buf_serv[ret_serv] = '\0';
		ft_putstr(KYEL);
		ft_putstr("[Received]: ");
		ft_putstr(RESET);
		printf("%s\n", buf_serv);
		if (ft_strstr(buf_serv, "READY"))
		{
			// send file
			ft_putstr("SUCCESS - READY received\nSending ...\n");
			send(sock, file, file_stat.st_size, 0); // send mapped file
		}
		else
			write_sock(sock, "ERROR - Ready signal not received. Aborting put.", 1);
	}
}