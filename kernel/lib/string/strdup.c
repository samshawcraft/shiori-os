#include "kernel/lib/include/stdlib.h"

char *strdup(const char *src){
	char *str;
	char *p;
	int len = 0;
	while (src[len]) len++;
	str = malloc(len + 1);
	p = str;
	while (*src) *p++ = *src++;
	*p = '\0';
	return str;
}