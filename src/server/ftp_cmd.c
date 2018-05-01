/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** ftp_cmd
*/

#include "server/server.h"
#include <sys/wait.h>

void	pasv_accept(t_shell *shl, char **arg)
{
	struct	sockaddr_in	s_pasv;
	socklen_t	s_size;

	(void)arg;
	s_size = sizeof(s_pasv);
	shl->pasv_fd = accept(shl->sfd, (struct sockaddr *)&s_pasv, &s_size);
	if (shl->pasv_fd == -1)
		dprintf(shl->cfd, "425 Error occured when opening data\n");
}

void	list(t_shell *shl, char **arg)
{
	int	status;

	if (is_connected(shl) == true) {
		if (shl->pasv_avail == false) {
			dprintf(shl->cfd, "425 Use PORT or PASV first.\n");
			return;
		}
		pasv_accept(shl, arg);
		if (fork() == 0) {
			dprintf(shl->cfd, "150 Here comes the dir listing.\n");
			dup2(shl->pasv_fd, 1);
			close(shl->pasv_fd);
			execl("/bin/ls", "ls", "-la", (char *)0);
		} else {
			wait(&status);
			pasv_close(shl);
			dprintf(shl->cfd, "226 Directory send OK.\n");
		}
	}
}

void	noop(t_shell *shl, char **arg)
{
	(void)arg;
	if (is_connected(shl) == true)
		dprintf(shl->cfd, "200 NOOP ok.\n");
}

void	quit(t_shell *shl, char **arg)
{
	(void)arg;
	if (shl->user)
		free(shl->user);
	if (shl->ip)
		free(shl->ip);
	shl->exit_f = true;
	dprintf(shl->cfd, "221 Goodbye\n");
}

void	f_help(t_shell *s, char **arg)
{
	(void)arg;
	if (is_connected(s) == true){
		dprintf(s->cfd, "214-The following commands are recognized.\n");
		dprintf(s->cfd, " USER PASS LIST PWD  NOOP QUIT HELP\n");
		dprintf(s->cfd, " CWD  PASV CDUP TYPE RETR STOR DELE\n");
		dprintf(s->cfd, "214 Help OK.\n");
	}
}
