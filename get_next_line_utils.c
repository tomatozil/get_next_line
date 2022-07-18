/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyun <jiyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 21:00:24 by jiyun             #+#    #+#             */
/*   Updated: 2022/05/20 17:04:57 by jiyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
    size_t	s_len;
    size_t  i;
    char	*sub;

    if (!s)
        return (NULL);
    s_len = ft_strlen(s);
    if (s_len <= start)
        return (ft_strdup(""));
    if (s_len - start < len)
        len = s_len - start;
    sub = malloc(sizeof(char) * (len + 1));
    if (!sub)
        return (NULL);
    i = 0;
    while (s[start + i] != '\0' && i < len)
    {
        sub[i] = s[start + i];
        i++;
    }
    sub[i] = '\0';
    return (sub);
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
