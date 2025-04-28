#include "kernel/lib/include/stdlib.h"

char *strtok(char *s,const char *delm){
    static int currIndex = 0;
    static char *backup_string; 
    if (s)
        backup_string = s; 
    else 
        s = backup_string;
    if(!s || !delm || s[currIndex] == '\0') return 0;
    char *W = (char *)malloc(sizeof(char)*4096);
    int i = currIndex, k = 0, j = 0;
    while (s[i] != '\0'){
        j = 0;
        while (delm[j] != '\0'){
            if (s[i] != delm[j])
                W[k] = s[i];
            else goto It;
            j++;
        }
        i++;
        k++;
    }
It:
    W[i] = 0;
    currIndex = i+1;
    return W;
}