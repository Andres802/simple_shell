#include "shell.h"
/**
 * interactive - shell in interactive mode (user interaction)
 * @env: enviroment of the system
 * Return: 0 on success or -1 if it fails
 */
int prompt(char **env)
{
	char *line = NULL; 
	char **commands = NULL;
	size_t n;
	ssize_t read;
	pid_t child_pid;
	int status;
	bool execute = false;
	/* ========== S H E L L  P R O M P T ==========*/
signal(SIGINT, signalhandle);
while ((read = getline(&line, &n, stdin)))
	{		/*=== CHECK  FOR END OF FILE ====*/
		if (read == EOF)
			ctrl_c(line);
	commands = parse_input(line);
	child_pid = fork();
		if (child_pid == -1)
			fork_error(line, commands);
		if (child_pid == 0)
		{
			execute = execute_cmd(commands, line, env);
				if (execute == false)
					{
						perror("COMMAND NOT FOUND");
						free(line), free_arrays(commands), exit(EXIT_FAILURE);
					}
		}
		else
		{
			wait(&status);
			if (commands == NULL)
			free(line), free_arrays(commands);
			else if ((_strcmp("exit", commands[0])) == 0)
			exit_shell(line, commands);
			else
				free_arrays(commands), free(line);
		}
		n = 0, line = NULL;
		if (isatty(STDIN_FILENO) == 1)
		write(STDOUT_FILENO, "$hell ", 6);
	} /* === E N D  O F  T H E  W H I L E  LOOP === */
	return (0);
}