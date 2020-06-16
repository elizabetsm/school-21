#ifndef MINISHELL_H
# define MINISHELL_H

// #include "libft/libft.a"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct s_struct {
	char *inp;
	char **env;
}				t_struct;		

// void print(char *name);

#endif