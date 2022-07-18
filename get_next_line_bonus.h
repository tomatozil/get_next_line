#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct  s_fd_lst
{
    int     fd;
    char    *keep;
    struct s_fd_lst *prev;
    struct s_fd_lst *next;
}   t_fd_lst;

char    *get_next_line(int fd);

size_t  ft_strlen(const char *s);
char	*ft_strchr(const char *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
void    free_clean(t_fd_lst *node);

#endif