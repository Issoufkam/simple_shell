#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 10
#define BUFFER_SIZE 1024

int main(void)
{
	char input_buffer[BUFFER_SIZE];
	char *args[MAX_ARGS];
	int status;

	while (1)
	{
		printf("$ ");
		fgets(input_buffer, BUFFER_SIZE, stdin);

		// Supprimer le caractère de nouvelle ligne à la fin de l'entrée
		input_buffer[strcspn(input_buffer, "\n")] = '\0';

		// Séparer l'entrée en arguments
		char *token = strtok(input_buffer, " ");
		int i = 0;
		while (token != NULL && i < MAX_ARGS - 1)
		{
			args[i] = token;
			token = strtok(NULL, " ");
			i++;
		}
		args[i] = NULL;

		// Exécuter la commande
		pid_t pid = fork();
		if (pid == 0)
		{
			execvp(args[0], args);
			perror("execvp");
			exit(EXIT_FAILURE);
		}
		else if (pid < 0)
		{
			perror("fork");
		}
		else
		{
			waitpid(pid, &status, 0);
		}
	}

	return (0);
}
