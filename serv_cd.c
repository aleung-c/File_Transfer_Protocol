/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/03 14:14:46 by aleung-c          #+#    #+#             */
/*   Updated: 2015/05/08 17:44:38 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void	go_cd(int cs, char **input)
{
	char	*buf_send;
	char	*buf;
	char	*cwd;

	cwd = NULL;
	buf = NULL;
	printf("%s\n", getcwd(buf, 4096));
	buf_send = ft_strdup("SUCCESS - Go cd");
	ft_putstr(KGRN);
	ft_putstr("[Sent]: ");
	ft_putstr(RESET);
	printf("%s\n", buf_send);
	write(cs, buf_send, ft_strlen(buf_send));
	if (input[1] && input[1][0])
		change_dir(input[1]);
	else
		chdir(home);
	write(cs, " ", 1);
}

void	change_dir(char *path)
{
	char	*new_cwd;
	char	*buf_cwd;
	int		p_len;

	chdir(path);
	buf_cwd = NULL;
	new_cwd = getcwd(buf_cwd, 4096);
	p_len = ft_strlen(new_cwd) - ft_strlen(home);
	if (p_len > 0)
		return ;
	else
		chdir(home);
}
