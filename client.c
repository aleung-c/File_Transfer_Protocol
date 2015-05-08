/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/27 18:49:52 by aleung-c          #+#    #+#             */
/*   Updated: 2015/05/08 17:45:15 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void	client_prompt(int sock)
{
	int		ret;
	int		ret_serv;
	char	buf[MSG_BUFSIZE];
	char	buf_serv[MSG_BUFSIZE];

	prompt();
	while ((ret = read(0, buf, MSG_BUFSIZE)))
	{
		buf[ret - 1] = '\0';
		display_input(buf);
		if (!buf[0])
			write(sock, " ", 2);
		else
			write(sock, buf, ft_strlen(buf));
		ret_serv = read(sock, buf_serv, MSG_BUFSIZE);
		buf_serv[ret_serv] = '\0';
		ft_putstr(KYEL);
		ft_putstr("Received: ");
		ft_putstr(RESET);
		printf("\n%s\n", buf_serv);
		client_parse(sock, buf, buf_serv);
		prompt();
	}
}

void	client_parse(int sock, char *buf, char *buf_serv)
{
	int ret_serv;

	if (ft_strcmp(buf, "quit") == 0 || ft_strcmp(buf, "exit") == 0)
		exit(0);
	if (ft_strstr(buf_serv, "SUCCESS"))
	{
		if (ft_strstr(buf_serv, "get"))
			client_get(sock, buf_serv, buf);
		else if (ft_strstr(buf_serv, "put"))
			client_put(sock, buf_serv, buf);
		else
		{
			ret_serv = read(sock, buf_serv, MSG_BUFSIZE);
			buf_serv[ret_serv] = '\0';
			ft_putstr(buf_serv);
		}
	}
}

int		main(int argc, char **argv) // A FAIRE : gestion erreur des args plus solide ?
{
	int sock;
	int port;

	port = ft_atoi(argv[2]);
	if (argc != 3)
		usage(argv[0]);
	else
	{
		// gestion d'erreur argv1 a faire ?
		sock = create_client(argv[1], port);
		client_prompt(sock);
		close(sock);
	}
	return (0);
}
