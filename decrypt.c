#include <string.h>
#include <stdio.h>

char str[] = "43(:7&!#3&@>$%^|]:&6;<7*-$}9{;!*!$5{<;-=^8]#:5<@#%#&!5!@40207#9($3&)7<$1";

int b(char *in, char *o, int len)
{
    int i,j,z;
    char a[] = "3:5[9&2^]{7}*<-8@=4(6#!>|)0+;1$%";
    for (i=0; i < len; i++)
    {
        unsigned char k = strchr(a, in[i])-a;
        j = (i / 8) * 5;
        z = i & 7;
        if (!z)
                o[j] |= k << 3;
        if (z==1) {
                o[j] |= k >> 2;
                o[j + z] |= k << 6;
        }
        if (z==2) {
                o[j + 1] |= k << 1;
        }
        if (z==3) {
                o[j + 1] |= k >> 4;
                o[j + 2] |= k << 4;
        }
        if (z==4) {
                o[j + 2] |= k >> 1;
                o[j + 3] |= k << 7;
        }
        if (z==5) {
                o[j + 3] |= k << 2;
        }
        if (z==6) {
                o[j + 3] |= k >> 3;
                o[j + 4] |= k << 5;
        }
        if (z==7) {
                o[j + 4] |= k;
        }
    }
    return i/8 * 5;
}


int k(unsigned char *x, unsigned char *key, int l)
{
    int i;
    unsigned char tmp, a = 0;

    for (i=0; i < 256; i++)
        x[i] = i;

    for (i=0; i < 256; i++)
    {
        a += x[i] + key[i % l];
        tmp = x[i];
        x[i] = x[a];
        x[a] = tmp;
    }
}

int c(unsigned char *x, unsigned char *y, int l)
{
    unsigned char b = 0;
    unsigned char tmp;
    int i;

    for (i=1; i <= l; i++)
    {
        b += x[i];
        tmp = x[i];
        x[i] = x[b];
        x[b] = tmp;
        y[i-1] ^= x[(x[i] + x[b]) & 0xff];
    }
}

int main()
{
    unsigned char x[256];
    unsigned char key[] = "abcd";
    unsigned char crypt_text[sizeof(str)] = {};
    int len;

    len = b(str, crypt_text, strlen(str));
    k(x, key, strlen(key));
    c(x, crypt_text, len);
    printf("%s\n", crypt_text);
}
