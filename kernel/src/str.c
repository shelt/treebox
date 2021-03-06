#include "str.h"

/**
 * @file str.c
 * @brief Basic string/memory manipuation
 */

unsigned char hexc_to_nibble(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    else return 255;
}
char nibble_to_hexc(unsigned char n)
{
    if (n <= 9)
        return n + '0';
    else
        return n + 'a' - 10;
}

// bytearr must have size bytes/2 and (bytes mod 2) of 0
void hstrtob(unsigned char *bytearr, char *string, size_t bytes)
{
    size_t byte_pos;
    int str_pos;
    for(byte_pos=0, str_pos=0; byte_pos<bytes; byte_pos++, str_pos+=2)
        bytearr[byte_pos] = (hexc_to_nibble(string[str_pos]) << 4) | (hexc_to_nibble(string[str_pos+1]));
}
// string must have size 2*bytes+1
void btohstr(char *string, unsigned char *bytearr, size_t bytes)
{
    size_t byte_pos;
    int str_pos;
    for(byte_pos=0, str_pos=0; byte_pos<bytes; byte_pos++, str_pos+=2)
    {
        string[str_pos  ] = nibble_to_hexc(bytearr[byte_pos] >> 4);
        string[str_pos+1] = nibble_to_hexc(bytearr[byte_pos]);
    }
}

size_t strlen(const char* str)
{
    size_t ret = 0;
    while ( str[ret] != 0 )
        ret++;
    return ret;
}


///////////////////////////////////
// primitive memory manipulation //
///////////////////////////////////

// Very basic implementation; TODO improve
void *memcpy(void *_dst, void *_src, size_t len)
{
    register char *dst = _dst;
    register char *src = _src;
    for (size_t i=0; i<len; i++)
        dst[i] = src[i];
    
    return dst;
}

void *memset(void *_dst, unsigned char data, size_t len)
{
    register char *dst = _dst;
    for (size_t i=0; i<len; i++)
        dst[i] = data;
    
    return dst;
}
