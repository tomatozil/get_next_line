//
// Created by jiyun on 2022/07/16.
//
//
// Created by jiyun on 2022/07/15.
//

#include "get_next_line_bonus.h"
//#include <stdio.h>
//#include <fcntl.h>
//#define BUFFER_SIZE 1

static char    *backup_line(char *keep, char **ret_from_outside)
{
    char    *ptr_newline;
    char    *ret;

    ptr_newline = ft_strchr(keep, '\n');
    // 2. 백업 필요하지 않는 경우(eof였던 경우, keep 속 \n 뒤에 뭐가 남아있지 않은 경우)
    if (!ptr_newline || *(ptr_newline + 1) == '\0')
    {
        free(keep);
        keep = NULL;
        return (NULL);
    }
    // 1. 백업이 필요한 경우
    ret = ft_strdup(ptr_newline + 1);
    if (!ret) // 3. 백업을 하지 못한 경우(할당 실패)
    {
        free(*ret_from_outside);
        *ret_from_outside = NULL;
    }
    free(keep);
    return (ret);
}
/* 1. 할당 실패, read 실패(keep == NULL)
 * 2. keep에 무엇인가 저장됨(keep != NULL)
 * 2-1. \n이 포함된 문장이 keep에 저장된 상태(eof 일 수도 아닐 수도)
 * 2-2. \n이 포함되지 않은 문장이 keep에 저장된 상태(eof)
*/

static char    *get_line(char *keep)
{
    char    *ptr_newline;
    char    *ret;
    ssize_t i;

    // 2-2. \n이 포함되지 않은 문장이 keep에 저장된 상태(eof)
    if (*keep == '\0')
        return (NULL);
    ptr_newline = ft_strchr(keep, '\n');
    if (!ptr_newline)
        return (ft_strdup(keep));
    // 2-1. \n이 포함된 문장이 keep에 저장된 상태(eof 일 수도 아닐 수도)
//    ret = ft_substr(*keep, 0, ptr_newline - *keep + 1);
    ret = malloc(sizeof(char) * (ptr_newline - keep + 2));
    if (!ret)
        return (NULL);
    i = 0;
    while (i < ptr_newline - keep + 1)
    {
        ret[i] = keep[i];
        i++;
    }
    ret[i] = '\0';
    return (ret);
}

static char    *read_and_put(int fd, char *keep)
{
    ssize_t read_byte;
    char    *buf;

    buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
    if (!buf)
        return (NULL);
    read_byte = read(fd, buf, BUFFER_SIZE);
    while (read_byte > 0)
    {
        buf[read_byte] = '\0';
        keep = ft_strjoin(keep, buf);
        if (ft_strchr(keep, '\n') || !keep) /* !keep: join 실패 시 진즉에 빠져나가기 위해서 */
            break ;
        read_byte = read(fd, buf, BUFFER_SIZE);
    }
    free(buf);
    buf = NULL;
    if (read_byte < 0 || !keep) /* !keep이 여기 꼭 들어갈 필요 없지만 NULL로 빠져나감을 명시하기 위해서 */
        return (NULL);
    return (keep);
}

static t_fd_lst    *find_fd(int fd, t_fd_lst *head)
{
    t_fd_lst    *target;

    target = head->next;
    while(target)
    {
        if (target->fd == fd)
            return (target);
        target = target->next;
    }
    target = malloc(sizeof(t_fd_lst));
    if (!target)
        return (NULL);
    target->fd = fd;
    target->keep = NULL;
    target->prev = head;
    target->next = head->next;
    if (head->next)
        head->next->prev = target;
    head->next = target;
    return (target);
}

char    *get_next_line(int fd)
{
    static t_fd_lst head;
    t_fd_lst        *node;
    char            *ret;

    if (fd < 0 || BUFFER_SIZE < 1)
        return (NULL);
    // 해당하는 {fd와 그 버퍼} 찾기
    node = find_fd(fd, &head);
    // 못찾으면 끝
    if (!node)
        return (NULL);
    // 찾았으면 버퍼 불러오기
    node->keep = read_and_put(fd, node->keep);
    // 1. 할당 실패, read 실패(keep == NULL)
    if(!(node->keep))
    {
        free_clean(node);
        return (NULL);
    }
    // 2. keep에 무엇인가 저장됨(keep != NULL)
    ret = get_line(node->keep);
    if (!ret) // line 만드는 데에 필요한 메모리 할당 실패
    {
        free(node->keep);
        free_clean(node);
        return (NULL);
    }
    /*
     * 1. 백업이 필요한 경우(keep 속 \n 뒤에 뭐가 남아있는 경우)
     * 2. 백업 필요하지 않는 경우(eof였던 경우, keep 속 \n 뒤에 뭐가 남아있지 않은 경우)
     * 3. 백업을 하지 못한 경우(할당 실패)
    */
    node->keep = backup_line(node->keep, &ret);
    return (ret);
}

/* ?
 size_t
 static 메모리 할당 위치
 lseek 함수 금지 이유
 메모리 누수 system 명령어
*/

//int main() {
//    int fd[4];
//
//    fd[0] = open("../gnlTester/files/41_with_nl", O_RDWR);
//    printf("my: %s", get_next_line(fd[0]));
//    printf("ans: 0123456789012345678901234567890123456789with\n");

//    fd[1] = open("../gnlTester/files/42_with_nl", O_RDWR);
//    printf("my: %s", get_next_line(fd[1]));
//    printf("ans: 01234567890123456789012345678901234567890with\n");

//    fd[2] = open("../gnlTester/files/43_with_nl", O_RDWR);
//    printf("my: %s", get_next_line(fd[2]));
//    printf("ans: 012345678901234567890123456789012345678901with\n");
//
//    printf("my: %s\n", get_next_line(fd[0]));
//    printf("ans: 0\n");
//
//    printf("my: %s\n", get_next_line(fd[1]));
//    printf("ans: 1\n");
//
//    printf("my: %s\n", get_next_line(fd[2]));
//    printf("ans: 2\n");
//
//    printf("my: %s", get_next_line(fd[0]));
//    printf("my: %s", get_next_line(fd[1]));
//    printf("my: %s\n", get_next_line(fd[2]));
//    printf("ans: (NULL)(NULL)(NULL)\n");
//
//    fd[3] = open("../gnlTester/files/nl", O_RDWR);
//    printf("my: %s", get_next_line(fd[3]));
//    printf("ans: with\n");
//    printf("my: %s\n", get_next_line(fd[3]));
//    printf("ans: (NULL)\n");
//}
