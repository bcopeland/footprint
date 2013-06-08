#include <string.h>
#include <stdio.h>

char str[] = "43(:7&!#3&@>$%^|]:&6;<7*-$}9{;!*!$5{<;-=^8]#:5<@#%#&!5!@40207#9($3&)7<$1";

int b(char *in, char *o, int len)
{
    int i,j,z;
    char a[] = "3:5[9&2^]{7}*<-8@=4(6#!>|)0+;1$%", d[8];
    for (i=0; i < len; i+=8)
    {
        for (j=0; j < 8; j++)
            d[j] = strchr(a,in[i+j])-a;
        j = (i / 8) * 5;
        o[j] = d[0] << 3 | d[1] >> 2;
        o[j + 1] = d[1] << 6 | d[2] << 1 | d[3] >> 4;
        o[j + 2] = d[3] << 4 | d[4] >> 1;
        o[j + 3] = d[4] << 7 | d[5] << 2 | d[6] >> 3;
        o[j + 4] = d[6] << 5 | d[7];
    }
    return i/8 * 5;
}


int c(unsigned char *y, int w, unsigned char *k, int l)
{
    int i;
    unsigned char tmp, a=0, x[256], b=0;

    for (i=0; i < 256; i++)
        x[i] = i;

    for (i=0; i < 256; i++)
    {
        a += x[i] + k[i % l];
        tmp = x[i];
        x[i] = x[a];
        x[a] = tmp;
    }

    for (i=1; i <= w; i++)
    {
        b += x[i];
        tmp = x[i];
        x[i] = x[b]; // here
        x[b] = tmp;
        y[i-1] ^= x[(x[i] + x[b]) & 0xff];
    }
}

int main()
{
    unsigned char k[] = "abcd";
    unsigned char crypt_text[sizeof(str)] = {};
    int len;

    len = b(str, crypt_text, strlen(str));
    c(crypt_text, len, k, strlen(k));
    printf("%s\n", crypt_text);
}
