
#include "get_next_line_bonus.h"

size_t  ft_strlen(const char *s)
{
    size_t len;

    len = 0;
    while (*s != '\0')
    {
        s++;
        len++;
    }
    return (len);
}


char	*ft_strchr(const char *s, char c)
{
    if (!s)
        return (NULL);
    while (*s != '\0')
    {
        if (*s == c)
            return ((char *)s);
        s++;
    }
    return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
    size_t	s1_len;
    size_t	s2_len;
    size_t  i;
    char	*new;

    if (!s1)
        return (ft_strdup(s2));
    s1_len = ft_strlen(s1);
    s2_len = ft_strlen(s2);
    new = malloc(sizeof(char) * (s1_len + s2_len + 1));
    if (!new)
        return (NULL);
    i = -1;
    while (++i < s1_len)
        new[i] = s1[i];
    i = -1;
    while (++i < s2_len)
        new[s1_len + i] = s2[i];
    new[s1_len + i] = '\0';
    free((void *)s1);
    return (new);
}

char	*ft_strdup(const char *s)
{
    char	*ret;
    size_t  size;
    size_t  i;

    if (!s)
        return (NULL);
    size = ft_strlen(s);
    if (size == 0)
        return (NULL);
    ret = malloc(sizeof(char) * (size + 1));
    if (!ret)
        return (NULL);
    i = 0;
    while (s[i] != '\0')
    {
        ret[i] = s[i];
        i++;
    }
    ret[i] = '\0';
    return (ret);
}

void    free_clean(t_fd_lst *node)
{
    if (node->prev)
        node->prev->next = node->next;
    if (node->next)
        node->next->prev = node->prev;
    free(node);
    node = NULL;
}
