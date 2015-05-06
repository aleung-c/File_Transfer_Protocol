/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/28 17:18:00 by aleung-c          #+#    #+#             */
/*   Updated: 2015/05/06 18:16:28 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

#include <errno.h> //

void go_get(int cs, char **input)
{
	int fd;

	if (!input[1]) // check si manque argument.
		write_cs(cs, "ERROR - Missing argument", 1);
	else
	{
		if ((fd = open(input[1], O_RDONLY)) < 0) //
			write_cs(cs, "ERROR - File not existing", 1);
		else // open est ok, serv peut commencer le mapping.
			file_transfer(cs, input[1], fd);
	}
}


void file_transfer(int cs, char *input, int fd)
{
	char buf_client[1025];
	struct stat file_stat;
	char *file;
	int ret_client;
	char *buf_send;

	
	buf_send = NULL;
	// GET FILE INFO.
	stat(input, &file_stat);

	printf("File size = %lld\n",  file_stat.st_size);
	if (file_stat.st_size > MAX_FILESIZE) // securité pour taille de fichier trop grande. 500 Mo max set. voir .h
	{
		write_cs(cs, "ERROR - File too big. Max = 500Mo", 1);
		return;
	}
	ft_putstr(KMAG);
	ft_putstr("[Serveur]: mapping file.\n");
	ft_putstr(RESET);

	// MAP FILE
	file = (char *)mmap(0, file_stat.st_size + 1, PROT_READ, MAP_FILE | MAP_PRIVATE, fd, 0);
	// file[file_stat.st_size] = '\0';
	//ft_putstr(file);
	if (file == MAP_FAILED)
	{
		ft_putnbr(errno); //
		perror("\nmmap"); //

		write_cs(cs, "ERROR - Not a valid file", 1);
		return;
	}
	else
		printf("mmap : SUCCESS\n");

	// AWAITING READY SIGNAL
	buf_send =  ft_strjoin("SUCCESS - AWAITING READY SIGNAL get: mapping file. size=", ft_itoa(file_stat.st_size));
	buf_send = ft_strjoin(buf_send, ", name=");
	buf_send = ft_strjoin(buf_send, input);
	ft_putstr(KGRN);
	ft_putstr("[Sent]: ");
	ft_putstr(RESET);
	printf("%s\n", buf_send);
	write(cs, buf_send, ft_strlen(buf_send));

	// receive the "ready" from the client.
	ret_client = read(cs, buf_client, 1025);
	buf_client[ret_client] = '\0';
	ft_putstr(KGRN);
	ft_putstr("[Received]: ");
	ft_putstr(RESET);
	printf("%s\n", buf_client);

	// SEND FILE
	if (ft_strstr(buf_client, "READY"))
	{
		ft_putstr("SUCCESS - READY received\nSending ...\n");
		send(cs, file, file_stat.st_size, 0); // send mapped file
	}
	else
		write_cs(cs, "ERROR - READY not received. Aborting get.", 1);
	ft_putstr("SERVEUR GET - END\n");
	return;
}
