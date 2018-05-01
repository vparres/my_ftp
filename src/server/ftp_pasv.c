/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** ftp_pasv
*/

#include "server/server.h"

static int	pasv_sock(t_shell *shl)
{
	struct	protoent	*pe;

	pe = getprotobyname("TCP");
	if (!pe) {
		dprintf(shl->cfd, "425 Can't open data connection.\n");
		return (1);
	}
	shl->sfd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (shl->sfd == -1) {
		dprintf(shl->cfd, "425 Can't open data connection.\n");
		return (1);
	}
	return (0);
}

static int	pasv_bind(t_shell *shl)
{
	struct sockaddr_in s_in;
	int ck;

	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(0);
	s_in.sin_addr.s_addr = INADDR_ANY;
	ck = bind(shl->sfd, (const struct sockaddr *)&s_in, sizeof(s_in));
	ck = listen(shl->sfd, 42);
	if (ck != 0) {
		dprintf(shl->cfd, "425 Can't open data connection.\n");
		close(shl->sfd);
		return (1);
	}
	return (0);
}

static int	pasv_infoget(t_shell *shl, char *sip)
{
	struct sockaddr_in s_s, s_p;
	socklen_t s_p_size;

	s_p_size = sizeof(s_p);
	if (getsockname(shl->cfd, (struct sockaddr *)&s_s, &s_p_size) == -1 ||
	getsockname(shl->sfd, (struct sockaddr *)&s_p, &s_p_size) == -1) {
		dprintf(shl->cfd, "425 Can't open data connection.\n");
		return (-1);
	}
	strcpy(sip, inet_ntoa(s_s.sin_addr));
	for (int i = 0; sip[i] != '\0'; i++)
		if (sip[i] == '.')
			sip[i] = ',';
	return (ntohs(s_p.sin_port));
}

void	pasv(t_shell *shl, char **arg)
{
	char	sip[15];
	int	port;

	(void)arg;
	if (is_connected(shl) == true){
		if (shl->sfd != -1)
			pasv_close(shl);
		if (pasv_sock(shl) == 1)
			return;
		if (pasv_bind(shl) == 1)
			return;
		if ((port = pasv_infoget(shl, sip)) == -1)
			return;
		shl->pasv_avail = true;
		dprintf(shl->cfd, "227 Entering Passive Mode (%s,%d,%d)\n", \
		sip, port >> 8 , port & 255);
	}
}

void	pasv_close(t_shell *shl)
{
	shutdown(shl->pasv_fd, 2);
	close(shl->sfd);
	shl->sfd = -1;
	shl->pasv_fd = -1;
	shl->pasv_avail = false;
}
