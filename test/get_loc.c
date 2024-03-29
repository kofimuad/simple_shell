#include "main.h"

char *get_loc(char *command)
{
	char *path, *path_cp, *file_path, *path_token;
	int cmd_len, dir_len;
	struct stat buffer;

	path = getenv("PATH");

	if (path)
	{
		path_cp = strdup(path);

		cmd_len = strlen(command);

		path_token = strtok(path_cp, ":");

		while (path_token != NULL)
		{
			dir_len = strlen(path_token);

			file_path = malloc(dir_len + cmd_len + 2);

			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, command);
			strcat(file_path, "\0");

			if (stat(file_path, &buffer) == 0)
			{
				free(path_cp);

				return (file_path);
			}
			else
			{
				free(file_path);

				path_token = strtok(NULL, ":");
			}
		}

		free(path_cp);

		if (stat(command, &buffer) == 0)
			return (command);

		return (NULL);
	}

	return (NULL);
}
