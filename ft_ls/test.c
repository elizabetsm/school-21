
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "libft/libft.h"

int main(void)
{
	struct dirent *entry;
	int i = 0;
	int j = 0;
	char **buf;
	DIR *dir = opendir(".");
	while ((entry = readdir(dir)) != NULL)
	{
		printf("%s\n", entry->d_name);
		i++;
	}
	closedir(dir);
	return 0;
}