/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/27 18:49:52 by aleung-c          #+#    #+#             */
/*   Updated: 2015/03/31 18:56:19 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"



void read_client(int cs)
{
	int ret;
	char *buf_client;
	char *buf_send;

	if (cs >= 0)
		printf("Connexion receveid.\n");
	if (!(buf_client = (char *)malloc(sizeof(char) * 1024 + 1)))
		exit(-1);
	while ((ret = read(cs, buf_client, 1024))) // read client request.
	{
		buf_client[ret] = '\0';
		ft_putstr(KGRN);
		ft_putstr("[Received]: ");
		ft_putstr(RESET);
		printf("%d bytes: [%s]\n", ret, buf_client);

		if (ft_strcmp(buf_client, "hello") == 0)
		{
			if (!(buf_send = (char *)malloc(sizeof(char) * 1024 + 1)))
			exit(-1);
			buf_send = ft_strdup("how are you?");
			ft_putstr(KGRN);
			ft_putstr("[Sent]: ");
			ft_putstr(RESET);
			printf("how are you?\n");
			write(cs, buf_send, ft_strlen(buf_send)); // send data to client.
		}
		else
		{
			buf_send = ft_strdup("No command found.");
			ft_putstr(KGRN);
			ft_putstr("[Sent]: ");
			ft_putstr(RESET);
			printf("%s\n", buf_send);
			write(cs, buf_send, ft_strlen(buf_send)); // send data to client.
		}
	}
}

void ft_sock_reception(int socket)
{
	pid_t child_pid;	

	child_pid = fork();

	if (child_pid >= 0)
	{
		if (child_pid == 0)
			read_client(socket);
		else
			waitpid(child_pid, NULL, 0);
	}
	else
	{
		ft_putendl_fd("Fork failed", 2);
		exit(-1);
	}
}

int create_server(int port)
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
	sin.sin_addr.s_addr = htonl(INADDR_ANY);  // transform to long
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		ft_putendl_fd("Bind error.", 2);
		exit (-1);
	}
	
	ft_putstr(KGRN);
	printf("- SUCCESS - Server Created.\n");
	ft_putstr(RESET);
	printf("Port: %d\n", port);
	printf("Server socket: %d\n", sock);

	listen(sock, 42); // recevoir 42 connexions simultanées.
	printf("- Awaiting connections... -\n");
	return (sock);
}

void usage(char *str)
{
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" [port]\n", 2);
	exit(-1);
}

int main(int argc, char **argv)
{
	int sock; // socket mere.
	int client_sock; // socket clients
	unsigned int cslen;
	struct sockaddr_in *csin;

	if (argc != 2)
		usage(argv[0]);
	else
	{
		// gestion d'erreur argv1 a faire ? 
		sock = create_server(ft_atoi(argv[1])); // socket mere.
		client_sock = accept(sock, (struct sockaddr *)&csin, &cslen);
		ft_sock_reception(client_sock);
		//read_client(client_sock); // a mettre dans reception apres fork.
		close(client_sock);
		close(sock);
	}
	return (0);
}