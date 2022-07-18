//
// Created by jiyun on 2022/07/15.
//

#include "get_next_line.h"

static void    free_clean(char **s)
{
    free(*s);
    *s = NULL;
}

static char    *get_line(char **keep)
{
    char    *ptr_newline;
    char    *backup_line;
    char    *ret;

    ptr_newline = ft_strchr(*keep, '\n');
    backup_line = ft_strdup(ptr_newline + 1);
    ret = ft_substr(*keep, 0, ptr_newline - *keep + 1);
    free(*keep);
    *keep = backup_line;
    return (ret);
}

char    *last_line(char **keep)
{
    char    *ret;

    if (ft_strchr(*keep, '\n'))
        return (get_line(keep));
    if (*keep[0] != '\0')
        ret = ft_strdup(*keep);
    else
        ret = NULL;
    free(*keep);
    *keep = NULL;
    return (ret);
}

char    *get_next_line(int fd)
{
    static char *keep;
    ssize_t     read_byte; /* over 1 -> read success, 0 -> reach eof, -1 -> read fail */
    char        *buf;

    if (fd < 0 || BUFFER_SIZE < 1)
        return (NULL);
    buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
    if (!buf)
        return (NULL);
    read_byte = read(fd, buf, BUFFER_SIZE);
    while (read_byte > 0)
    {
        buf[read_byte] = '\0';
        keep = ft_strjoin(keep, buf);
        if (ft_strchr(keep, '\n'))
        {
            free_clean(&buf);
            return (get_line(&keep));
        }
        read_byte = read(fd, buf, BUFFER_SIZE);
    }
    free_clean(&buf);
    if (read_byte == 0 && keep)
        return (last_line(&keep));
    return (NULL);
}


// int main() // 파일로부터
// {
// 	int		fd, line;
// 	char	*ret;
//
// 	fd = open("../gnlTester/files/multiple_nlx5", O_RDONLY);
// 	line = 0;
//
// 	// close(fd); // unvalid fd 일 때,
//
// 	while((ret = get_next_line(fd)) > 0)
// 	{
// 		printf(">%d : %s", line, ret);
// 		free(ret);
// 		line++;
// 	}
// 	printf("\n->%d : %s", line, ret); // 마지막 (NULL) 출력
//
// 	free(ret);
// 	close(fd);
//
// 	return 0;
// }