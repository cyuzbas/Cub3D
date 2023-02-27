#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

char		*get_next_line(int fd);
char		*ft_strchr(const char *s, int c);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *str);
char		*ft_substr(char const *s, int start, int len);
char		*ft_strdup(const char *src);

#endif
