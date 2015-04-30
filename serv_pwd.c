/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 17:01:39 by aleung-c          #+#    #+#             */
/*   Updated: 2015/04/30 16:15:47 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void	go_pwd(int cs, char **input)
{
	char *buf_send;
	// int child;
	char *pwd;
	char *buf_cwd;
	int p_len;

	if (input)
	{}
	buf_send = ft_strdup("SUCCESS - Go pwd");
	ft_putstr(KGRN);
	ft_putstr("[Sent]: ");
	ft_putstr(RESET);
	printf("%s\n", buf_send);
	write(cs, buf_send, ft_strlen(buf_send));

	buf_cwd = NULL;
	pwd = getcwd(buf_cwd, 4096);
	p_len = ft_strlen(pwd) - ft_strlen(home);
	if (p_len > 0)
		write(cs, &pwd[ft_strlen(home)], p_len);
	else
		write(cs, "/\n", 2);
	// child = fork();
	// if (child == 0)
	// {
	// 	dup2(cs, 1);
	// 	execv("/bin/pwd", input);
	// }
	// else
	// 	wait(NULL);
}