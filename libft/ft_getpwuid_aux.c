/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpwuid_aux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 20:46:30 by dchernik          #+#    #+#             */
/*   Updated: 2026/02/26 01:02:47 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/* Returns -1 on a malloc() error, 0 if no match is
 * found, and 1 on success. The loop exits if
 * home_loop_body() returns -1 (indicating a malloc()
 * or system error) or if it returns 1, which means
 * the UID of the files represented by `st` matches
 * the provided `uid` */
int	home_attempt(t_passwd *pwd, uid_t uid)
{
	DIR				*dir;
	struct dirent	*entry;
	struct stat		st;
	int				ret;

	dir = opendir(COMMON_HOME_DIR);
	if (!dir)
	{
		perror("opendir");
		return (-1);
	}
	errno = 0;
	entry = readdir(dir);
	while (entry != NULL)
	{
		ret = home_loop_body(pwd, entry, &st, uid);
		if (ret)
			break ;
		entry = readdir(dir);
	}
	if (errno && !entry)
		perror("readdir");
	closedir(dir);
	return (ret);
}

/* Returns -1 on a malloc() error. If the UID of the file owner
 * represented by `st` matches `uid`, it returns 0. On success,
 * it returns 1 */
int	home_loop_body(t_passwd *pwd, struct dirent *entry,
		struct stat *st, uid_t uid)
{
	char	user_dir[PATH_MAX];

	ft_strlcpy(user_dir, COMMON_HOME_DIR, PATH_MAX);
	ft_strlcat(user_dir, "/", PATH_MAX);
	ft_strlcat(user_dir, entry->d_name, PATH_MAX);
	if (!stat(user_dir, st))
	{
		if (st->st_uid == uid)
		{
			if (!fill_pwd_struct2(pwd, entry, user_dir, uid))
				return (-1);
			return (1);
		}
	}
	return (0);
}

int	fill_pwd_struct(t_passwd *pwd, char **ptokens, uid_t uid)
{
	if (split_size(ptokens) < 7)
		return (0);
	pwd->pw_name = ft_strdup(ptokens[0]);
	pwd->pw_passwd = ft_strdup(ptokens[1]);
	pwd->pw_uid = uid;
	pwd->pw_gid = ft_atoi(ptokens[3]);
	pwd->pw_gecos = ft_strdup(ptokens[4]);
	pwd->pw_dir = ft_strdup(ptokens[5]);
	pwd->pw_shell = ft_strdup(ptokens[6]);
	if (!pwd->pw_name || !pwd->pw_passwd
		|| !pwd->pw_gecos || !pwd->pw_dir
		|| !pwd->pw_shell)
	{
		perror("malloc");
		return (0);
	}
	return (1);
}

int	fill_pwd_struct2(t_passwd *pwd, struct dirent *entry,
		char *user_dir, uid_t uid)
{
	int	ret;

	pwd->pw_name = ft_strdup(entry->d_name);
	pwd->pw_passwd = ft_strdup("");
	pwd->pw_uid = uid;
	ret = ft_getgid(&pwd->pw_gid);
	if (ret)
		return (0);
	pwd->pw_gecos = ft_strdup("");
	pwd->pw_dir = ft_strdup(user_dir);
	pwd->pw_shell = ft_strdup("");
	if (!pwd->pw_name || !pwd->pw_passwd
		|| !pwd->pw_gecos || !pwd->pw_dir
		|| !pwd->pw_shell)
	{
		perror("malloc");
		return (0);
	}
	return (1);
}

void	free_pwd(t_passwd *pwd)
{
	if (pwd->pw_name)
		free(pwd->pw_name);
	if (pwd->pw_passwd)
		free (pwd->pw_passwd);
	if (pwd->pw_gecos)
		free (pwd->pw_gecos);
	if (pwd->pw_dir)
		free (pwd->pw_dir);
	if (pwd->pw_shell)
		free (pwd->pw_shell);
}
