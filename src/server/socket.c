/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** socket
*/

#include "server/server.h"

void socket_init(t_params *params)
{
	struct protoent *pe;

	pe = getprotobyname("TCP");
	if (!pe) {
		fprintf(stderr, "Error occured while getting protocol !\n");
		exit(84);
	}
	params->sock_fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (!params->sock_fd) {
		fprintf(stderr, "Failed to create socket ! Abort ...\n");
		exit(84);
	}
}

void socket_bind(t_params *params)
{
	struct sockaddr_in s_in;

	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(params->port);
	s_in.sin_addr.s_addr = INADDR_ANY;
	if (bind(params->sock_fd, (const struct sockaddr *)&s_in, \
	sizeof(s_in)) == -1) {
		fprintf(stderr, "Bind failed !\n");
		socket_close(params);
		exit(84);
	}
	if (listen(params->sock_fd, 42) == -1) {
		fprintf(stderr, "Server is not listening, closing ...\n");
		socket_close(params);
		exit(84);
	}
	printf("Server is ready ! Waiting for connections ...\n");
}

int socket_accept(t_params *params)
{
	int cfd;
	struct sockaddr_in s_clt;
	socklen_t size = sizeof(s_clt);

	cfd = accept(params->sock_fd, (struct sockaddr *)&s_clt, &size);
	params->client_ip = strdup(inet_ntoa(s_clt.sin_addr));
	if (cfd == -1) {
		printf("Connection to %s refused.\n", params->client_ip);
		return (-1);
	}
	printf("New client : %s\n", params->client_ip);
	return (cfd);
}

void socket_close(t_params *params)
{
	if (close(params->sock_fd) == -1) {
		fprintf(stderr, "Failed to close socket !\n");
		exit(84);
	}
}
