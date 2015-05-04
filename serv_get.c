/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/28 17:18:00 by aleung-c          #+#    #+#             */
/*   Updated: 2015/05/04 17:05:33 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

#include <errno.h> //

void go_get(int cs, char **input)
{
	char *buf_send;
	int fd;
	struct stat file_stat;
	char *file;
	int ret_client;
	char buf_client[1025];

	// buf_send = ft_strdup("SUCCESS - Go get\n");
	// ft_putstr(KGRN);
	// ft_putstr("[Sent]: ");
	// ft_putstr(RESET);
	// printf("%s\n", buf_send);
	// write(cs, buf_send, ft_strlen(buf_send));

	if (!input[1]) // check si manque argument.
	{
		buf_send = ft_strdup("ERROR - Missing argument to get\n");
		ft_putstr(KGRN);
		ft_putstr("[Sent]: ");
		ft_putstr(RESET);
		printf("%s\n", buf_send);
		write(cs, buf_send, ft_strlen(buf_send));
		return ;
	}
	else
	{
		if ((fd = open(input[1], O_RDONLY)) < 0) // 
		{
			buf_send =  ft_strdup("ERROR - File not existing\n");
			ft_putstr(KGRN);
			ft_putstr("[Sent]: ");
			ft_putstr(RESET);
			printf("%s\n", buf_send);
			write(cs, buf_send, ft_strlen(buf_send));
			return;
		}
		else // open est ok, serv peut commencer le mapping.
		{
			stat(input[1], &file_stat);

			printf("File size = %lld\n",  file_stat.st_size);
			if (file_stat.st_size > 524288000) // securité pour taille de fichier trop grande. 500 Mo max set.
			{
				buf_send =  ft_strdup("ERROR - File too big.\n");
				ft_putstr(KGRN);
				ft_putstr("[Sent]: ");
				ft_putstr(RESET);
				printf("%s\n", buf_send);
				write(cs, buf_send, ft_strlen(buf_send));
				return;
			}
			ft_putstr(KMAG);
			ft_putstr("[Serveur]: mapping file.\n");
			ft_putstr(RESET);

			file = (char *)mmap(0, file_stat.st_size + 1, PROT_READ, MAP_FILE | MAP_PRIVATE, fd, 0);
			// file[file_stat.st_size] = '\0';
			//ft_putstr(file);
			if (file == MAP_FAILED)
			{
				ft_putnbr(errno); //
				perror("\nmmap"); //

				buf_send =  ft_strdup("ERROR - Not a valid file\n");
				ft_putstr(KGRN);
				ft_putstr("[Sent]: ");
				ft_putstr(RESET);
				printf("%s\n", buf_send);
				write(cs, buf_send, ft_strlen(buf_send));
				return;
			}
			else
				printf("mmap : SUCCESS\n");
			buf_send =  ft_strjoin("SUCCESS - AWAITING READY SIGNAL get: mapping file. size=", ft_itoa(file_stat.st_size));
			buf_send = ft_strjoin(buf_send, ", name=");
			buf_send = ft_strjoin(buf_send, input[1]);
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
			// send file
			if (ft_strstr(buf_client, "READY"))
			{
				ft_putstr("SUCCESS - READY received\nSending ...\n");
				// ft_putstr(file);
				send(cs, file, (int)file_stat.st_size, MSG_OOB);
			}
			else
			{
				ft_putstr(KMAG);
				ft_putstr("[Serveur]: READY not received. Aborting get.\n");
				ft_putstr(RESET);

				buf_send =  ft_strdup("ERROR - READY not received. Aborting get.\n");
				ft_putstr(KGRN);
				ft_putstr("[Sent]: ");
				ft_putstr(RESET);
				printf("%s\n", buf_send);
				write(cs, buf_send, ft_strlen(buf_send));
			}
			ft_putstr("SERVEUR GET - END\n");
			return;
		}


	}

}