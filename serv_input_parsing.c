/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_input_parsing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/01 13:46:25 by aleung-c          #+#    #+#             */
/*   Updated: 2015/04/29 15:28:37 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

char	*clean_line(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			line[i] = ' ';
		i++;
	}
	return (line);
}

char	**get_input(char *buf_client)
{
	char **input;

	buf_client = clean_line(buf_client);
	input = ft_strsplit(buf_client, ' ');
	if (!input || !input[0])
	{
		ft_putendl_fd("Input recup failed", 2);
		return (NULL);
	}
	return (input);
}

void check_input(int cs, char *buf_client)
{
	char *buf_send;
	char **input;

	input =  get_input(buf_client);
	if (!(input) || !(input[0]))
	{
		buf_send = ft_strdup("ERROR");
		ft_putstr(KGRN);
		ft_putstr("[Sent]: ");
		ft_putstr(RESET);
		printf("%s\n", buf_send);
		write(cs, buf_send, ft_strlen(buf_send)); // send data to client.
		return ;
	}
	else if (ft_strcmp(input[0], "hello") == 0)
	{
		buf_send = ft_strdup("how are you?");
		ft_putstr(KGRN);
		ft_putstr("[Sent]: ");
		ft_putstr(RESET);
		printf("%s\n", buf_send);
		//write(cs, buf_send, ft_strlen(buf_send)); // send data to client.
		send(cs, buf_send, ft_strlen(buf_send), MSG_OOB);
	}
	else if (ft_strcmp(input[0], "ls") == 0)
	{
		go_ls(cs, input);
		// write(cs, buf_send, ft_strlen(buf_send));
		// faire execv et dup2 (avant le execv) pour rediriger la sortie sur le cs.
	}
	else if (ft_strcmp(input[0], "cd") == 0)
	{
		// faire un built-in cd bloqué au dossier courant.
		go_cd(cs, input);
	}
	else if (ft_strcmp(input[0], "get") == 0)  // A FAIRE
	{
		
		go_get(cs, input);
		

		// Pour copier des fichiers, ouvrir le fichier avec OPEN dans un fd,
		// Puis, send la taille a copier. utiliser stat sur le fd.

		// utiliser mmap pour copier le fichier sur la memoire.
		// write sur le cs, avc l'adress de mmap, et la taille recuperée.

		// puis, read le fd sur le client.
		// creer un nouveau fichier sur le client avec OPEN, flag O_CREATE.
		// ecrire dans ce fichier avec le client.
	}
	else if (ft_strcmp(input[0], "put") == 0)  // A FAIRE
	{
		buf_send = ft_strdup("SUCCESS - Go put");
		ft_putstr(KGRN);
		ft_putstr("[Sent]: ");
		ft_putstr(RESET);
		printf("%s\n", buf_send);
		write(cs, buf_send, ft_strlen(buf_send));
	}
	else if (ft_strcmp(input[0], "pwd") == 0)
	{
		go_pwd(cs, input);
	}
	else if (ft_strcmp(input[0], "quit") == 0 || ft_strcmp(input[0], "exit") == 0)
	{
		buf_send = ft_strdup("SUCCESS - Quiting server ...");
		ft_putstr(KGRN);
		ft_putstr("[Sent]: ");
		ft_putstr(RESET);
		printf("%s\n", buf_send);
		write(cs, buf_send, ft_strlen(buf_send));
		close(cs);
		exit(0);
	}
	else
	{
		buf_send = ft_strdup("ERROR - No command found.");
		ft_putstr(KGRN);
		ft_putstr("[Sent]: ");
		ft_putstr(RESET);
		printf("%s\n", buf_send);
		write(cs, buf_send, ft_strlen(buf_send)); // send data to client.
	}
}