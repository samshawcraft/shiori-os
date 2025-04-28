#include <stddef.h>

char *strrchr(const char *s, int c) {
    const char *p = NULL;
    while(1) {
        if (*s == (char)c)
            p = s;
        if (*s++ == '\0')
            return (char *)p;
    }
}