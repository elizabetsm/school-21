#include "ft_ls.h"

void	l_param(t_struct *st)
{
	struct stat buf;
	int i = 0;
	struct passwd *pwd;
	struct group *group;
	time_t vrem;
	while (st->buf[i] != NULL)
	{
		char *path = get_path(st, i);
		// printf("%s %d\n", path, i);
		char *modeval = (char *)malloc(sizeof(char) * 9 + 1);
    	if(stat(path, &buf) == 0)
		{
			mode_t perm = buf.st_mode;
			modeval = permissions(perm);
			pwd = getpwuid(buf.st_uid);
			if(pwd == NULL)
				perror("getpwuid");
			group = getgrgid(buf.st_gid);
			if(group == NULL)
				perror("getgrgid");
			char * a;
			a = get_time(buf);
			printf("%s %ld %s %s %*ld %s %s \n",  
			modeval, buf.st_nlink, pwd->pw_name, group->gr_name,  5,
			buf.st_size, a, st->buf[i]);     
   		}
		i++;
	}
}

char	*permissions(mode_t perm)
{
	char *modeval = (char *)malloc(sizeof(char) * 9 + 2);
	modeval[0] = (perm &__S_IFDIR) ? 'd' : '-';
	modeval[1] = (perm & S_IRUSR) ? 'r' : '-';
	modeval[2] = (perm & S_IWUSR) ? 'w' : '-';
	modeval[3] = (perm & S_IXUSR) ? 'x' : '-';
	modeval[4] = (perm & S_IRGRP) ? 'r' : '-';
	modeval[5] = (perm & S_IWGRP) ? 'w' : '-';
	modeval[6] = (perm & S_IXGRP) ? 'x' : '-';
	modeval[7] = (perm & S_IROTH) ? 'r' : '-';
	modeval[8] = (perm & S_IWOTH) ? 'w' : '-';
	modeval[9] = (perm & S_IXOTH) ? 'x' : '-';
	modeval[10] = '\0';
	return (modeval);
}

char	*get_time(struct stat buf)
{
	char *time;
	char *vrem;
	int i;
	int j;
	int sem;

	time = ft_memalloc(20);
	i = 4;
	j = 0;
	sem = 0;
	vrem = ctime(&buf.st_mtime);
	while (vrem[i] != '\0')
	{
		if (vrem[i] == ':')
			sem++;
		if (sem == 2)
			break;
		time[j] = vrem[i];
		j++;
		i++;
	}
	return (time);
}

char *get_path(t_struct *st, int i)
{
	char *path;
	char *tmp;
	if (ft_strcmp(st->dir_name, ".") == 0)
		return (st->buf[i]);
	else
	{
		tmp = ft_strjoin(st->dir_name, "/");
		path = ft_strjoin(tmp, st->buf[i]);
	}
	return(path);
}