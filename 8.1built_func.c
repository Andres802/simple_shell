#include "shell.h"
/**
 * signalhandle - function that handle user signals
 * @n: unused attribute (void)
 */
void signalhandle(int n __attribute__((unused)))
{
	write(STDERR_FILENO, "\n", 1);
	write(STDERR_FILENO, PROMPT, 2);
}
/**
 * ctrl_c - function that handle ctrl c signal from user
 * @line: command by user
 */
void ctrl_c(char *line)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "\n", 1);
	free(line);
	exit(EXIT_SUCCESS);
}
/**
 * fork_error -  function that exit once fork is not done correctly
 * @line: argument
 * @commands: command given by user
 */
void fork_error(char *line, char **commands)
{
	perror("FatalError: ");
	free(line);
	free_arrays(commands);
	exit(EXIT_FAILURE);
}
/**
 * free_arrays - function that free memory already used
 * @array: memory to free
 */
void free_arrays(char **array)
{
	int i;

	if (array == NULL)
		return;
	i = 2;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	if (array[i] == NULL)
		free(array[i]);
	free(array);
}
