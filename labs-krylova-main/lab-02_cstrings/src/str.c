#include "str.h"

char *my_strcpy(char *restrict destination , const char *restrict source)
{
    char *temp = destination;
    while(*destination++ = *source++);
    return temp;
}


char *my_strcat(char *restrict destination, const char *restrict source)
{
    my_strcpy(destination + my_strlen(destination), source);
    return destination;
}


int my_strcmp(const char *str1, const char *str2)
{
    while(*str1 && (*str1 == *str2))
    {
        str1++;
        str2++;
    }
    return *(const unsigned char*)str1 - *(const unsigned char *)str2;
}

int my_strlen(const char *str) {
    for (const char* i = str;;++i)
    {
        if (!*i)
            return i - str;
    }
}

