/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_input_parsing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/01 13:46:25 by aleung-c          #+#    #+#             */
/*   Updated: 2015/05/09 15:35:52 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

char	*clean_line(char *line)
{
	int		i;

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
	char	**input;
	int		i;

	i = 0;
	buf_client = clean_line(buf_client);
	input = ft_strsplit(buf_client, ' ');
	if (!input || !input[0])
	{
		ft_putendl_fd("Input recup failed", 2);
		return (NULL);
	}
	return (input);
}

void	check_input(int cs, char *buf_client)
{
	char	**input;

	input = get_input(buf_client);
	if (!(input) || !(input[0]))
		write_cs(cs, "ERROR", 1);
	else if (ft_strcmp(input[0], "ls") == 0)
		go_ls(cs, input);
	else if (ft_strcmp(input[0], "cd") == 0) // bug bloquant, et manque affichage error.
		go_cd(cs, input);
	else if (ft_strcmp(input[0], "get") == 0)
		go_get(cs, input);
	else if (ft_strcmp(input[0], "put") == 0)
		go_put(cs, input);
	else if (ft_strcmp(input[0], "pwd") == 0)
		go_pwd(cs);
	else if (ft_strcmp(input[0], "quit") == 0
		|| ft_strcmp(input[0], "exit") == 0)
	{
		write_cs(cs, "SUCCESS - Quiting server ...", 1);
		close(cs);
		exit(0);
	}
	else
		write_cs(cs, "ERROR - No command found.", 1);
}
