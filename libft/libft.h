/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:40:28 by dchernik          #+#    #+#             */
/*   Updated: 2026/02/26 00:58:17 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdbool.h>

/* ==================== get_next_line() DEFINITIONS  ==================== */
# ifndef GNL_BUFFER_SIZE
#  define GNL_BUFFER_SIZE 42
# endif

# define GNL_EXIT		0
# define GNL_READ		1
# define GNL_ALLOC		2
# define GNL_END		3
# define GNL_AGAIN		4

/* GNL_FD		  - a file descriptor;
 * GNL_RLEN		  - bytes read from `fd` (FD);
 * GNL_I		  - an auxiliary coutner variable;
 * GNL_RES		  - result of a function execution;
 * GNL_PRIV_MEM_S - previously allocated memory size. */
# define GNL_FD				0
# define GNL_BUF_POS		1
# define GNL_LINE_POS		2
# define GNL_RLEN			3
# define GNL_LINE_LEN		4
# define GNL_I				5
# define GNL_RES			6
# define GNL_PRIV_MEM_S		7
# define GNL_ERR			8

/* GNL_NORM  - normal execution. Means to do nothing;
 * GNL_RET   - indicate that the `line` must be returned;
 * GNL_BREAK - break from the main loop must be performed;
 * GNL_CONT  - continue must be applied on the main loop. */
# define GNL_NORM			0
# define GNL_RET			1
# define GNL_BREAK			2
# define GNL_CONT			3

/* get_next_line.c */
char	*get_next_line(int fd, int *err);
int		gnl_loop_alg(char *buf, char **line, long long *v, int *flags);
int		gnl_get_chunk(char *buf, char **line, long long *v, int *flags);
void	gnl_process_new_line(char *buf, char **line, long long *v, int *flags);
int		gnl_process_end_chunk(char **line, long long *v, int *flags);

/* get_next_line_utils.c */
int		gnl_init(char *buf, char **line, long long *v, int *flags);
int		gnl_alloc_mem(char **line, long long *v, int *flags);
void	gnl_check_reaching_end(long long *v, int *flags);
void	gnl_clear_func_state(char **line, long long *v, int *flags);
void	gnl_finish(int fd);

/* ==================== SYSTEM CALLS COPYCAT DEFINITIONS ================ */

/* UNKNOWN_STR - A value that may be assigned to any `char *`
 *				 field of the s_passwd structure or to any
 *				 other entity if we did not manage to find
 *				 its real value, or any other data we were
 *				 looking for */
# define COMMON_HOME_DIR		"/home"
# define PASSWD_PATH			"/etc/passwd"
# define PROC_INFO_SOURCE	"/proc/self/status"
# define PROC_PID_TOKEN		"Pid"
# define PROC_PPID_TOKEN		"PPid"
# define UNKNOWN_USER_NAME	"unknown" 

/* The analogue of system
 * `passwd` structure.
 *     pw_name   - username;
 *     pw_passwd - user password;
 *     pw_uid    - user ID;
 *     pw_gid    - group ID;
 *     pw_gecos  - user information;
 *     pw_dir    - home directory;
 *     pw_shell  - shell program. */
typedef struct s_passwd
{
	char	*pw_name;
	char	*pw_passwd;
	uid_t	pw_uid;
	gid_t	pw_gid;
	char	*pw_gecos;
	char	*pw_dir;
	char	*pw_shell;
}	t_passwd;

int		ft_getpid(pid_t *pid);
int		ft_getppid(pid_t *ppid);
int		ft_getuid(uid_t *uid);
int		ft_getgid(gid_t *gid);
int		ft_getpwuid(t_passwd *pwd, uid_t uid);

/* ft_getpwuid_aux.c */
int		home_attempt(t_passwd *pwd, uid_t uid);
int		home_loop_body(t_passwd *pwd, struct dirent *entry,
			struct stat *st, uid_t uid);
int		fill_pwd_struct(t_passwd *pwd, char **ptokens, uid_t uid);
int		fill_pwd_struct2(t_passwd *pwd, struct dirent *entry,
			char *user_dir, uid_t uid);
void	free_pwd(t_passwd *pwd);

/* ==================== Libft DEFINITIONS =============================== */

# define SPLIT_ERR_MSG	"Error: ft_split()\n"
# define GNL_ERR_MSG	"Error: get_next_line()\n"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
char	*ft_strdup(const char *s);

int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_substr(char const *s, unsigned int start, size_t len);

/* ft_aux.c */
void	split_free(char ***res);
size_t	split_size(char **res);

/* Singly-linked list */
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* Math */
size_t	ft_abs(long long num);
bool	ft_isnum(const char *s);

#endif
