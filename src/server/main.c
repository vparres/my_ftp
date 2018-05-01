/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** main
*/

#include "server/server.h"

void check_parse(t_params *params, int ac, char **av)
{
	(void)ac;
	if (!is_num(av[1])) {
		fprintf(stderr, "Port number is invalid, exiting ...\n");
		exit(84);
	}
	params->port = atoi(av[1]);
	DIR *dir = opendir(av[2]);
	if (dir) {
		chdir(av[2]);
		closedir(dir);
	} else {
		fprintf(stderr, "Home directory %s not found nor accessible\n",
		av[2]);
		exit(84);
	}
	printf("Starting %s on port %d with home set to %s ...\n", av[0],
	params->port, av[2]);
}

static char	*get_home(void)
{
	char	tmp[4096];
	char 	*cwd;
	if (getcwd(tmp, sizeof(tmp)) != NULL) {
		if (!(cwd = malloc(sizeof(char) * strlen(tmp) + 2)))
			return (NULL);
		strcpy(cwd, tmp);
		strcat(cwd, "/");
		printf("Home is set to : %s\n", cwd);
		return (cwd);
	} else
		return (NULL);
}

static void	client_routine(t_params *p, int cfd)
{
	pid_t	pid;
	pid = fork();
	if (pid == -1){
		fprintf(stderr, "Forking failed\n");
		return;
	}
	else if (pid == 0) {
		handle_client(cfd, p->client_ip, get_home());
		shutdown(cfd, 2);
		printf("Connection with %s closed\n", p->client_ip);
		free(p->client_ip);
		return;
	}
}

int main(int ac, char **av)
{
	t_params	params;
	int		cfd;

	if (ac != 3)
		help(av[0], 84);
	check_parse(&params, ac, av);
	socket_init(&params);
	socket_bind(&params);
	while (42){
		if ((cfd = socket_accept(&params)) == -1)
			continue;
		client_routine(&params, cfd);
	}
	socket_close(&params);
	return (0);
}
