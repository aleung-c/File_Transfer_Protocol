/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/27 18:49:52 by aleung-c          #+#    #+#             */
/*   Updated: 2015/03/31 18:31:46 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void	prompt()
{
	ft_putstr(KYEL);
	ft_putstr("~ Client $> ");
	ft_putstr(RESET);
}

void client_prompt(int sock)
{
	int ret;
	int ret_serv;
	char *buf;
	char *buf_serv;

	prompt();
	if (!(buf = (char *)malloc(sizeof(char) * 1024 + 1)))
		exit(-1);
	while ((ret = read(0, buf, 1024))) // read user input
	{
		buf[ret - 1] = '\0';
		printf("Input: [%s]\n", buf);
		write(sock, buf, ft_strlen(buf));
		if (!(buf_serv = (char *)malloc(sizeof(char) * 1024 + 1)))
			exit(-1);
		ret_serv = read(sock, buf_serv, 1024);  // read server response
		buf_serv[ret_serv] = '\0';
		printf("received: %s\n", buf_serv);
		prompt();
	}
}

int create_client(char *addr, int port)
{
	int sock;
	struct protoent *proto;
	struct sockaddr_in sin;

	proto = getprotobyname("tcp");
	if (!proto)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port); // transform to short
	sin.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		ft_putendl_fd("Connect error.", 2);
		exit (-1);
	}
	printf("- Connected to server.\n");
	printf("Port: %d\n", port);
	printf("Client socket: %d\n", sock);
	return (sock);
}

void usage(char *str)
{
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" <addr> <port>\n", 2);
	exit(-1);
}

int main(int argc, char **argv)
{
	int sock; // socket du client.
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