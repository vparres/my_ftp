/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** useful
*/

#include "server/server.h"

void help(char *prg, int exit_code)
{
	printf("USAGE:\t%s port path\n\tport\tis the port number on", prg);
	printf("which the server socket listens\n\tpath\tis the path to the ");
	printf("home directory for the Anonymous user\n");
	exit(exit_code);
}

bool is_num(const char *str)
{
	for (size_t i = 0; i < strlen(str); i++) {
		if (!isdigit(str[i]))
			return (false);
	}
	return (true);
}

void strdown(char *str)
{
	for (int i = 0; str[i]; i++) {
		str[i] = tolower(str[i]);
	}
}

static int test_space(char *str)
{
	for (int i = 0; str[i] != '\0'; i++)
		if (str[i] != ' ' && str[i] != '\n' && str[i] != '\r')
			return (0);
	return (1);
}

void epur_tok(char *str, char **arg)
{
	if (test_space(str) == 1) {
		arg[0] = strdup("nope");
		return ;
	}
	if (str[strlen(str) - 2] == '\r')
		str[strlen(str) - 2] = '\0';
	else
		str[strlen(str) - 1] = '\0';
	arg[0] = strtok(str, " ");
	arg[1] = strtok(NULL, " ");
	arg[2] = NULL;
	strdown(arg[0]);
}
