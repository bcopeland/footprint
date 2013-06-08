#include <string.h>
#include <stdio.h>

char str[] = "43(:7&!#3&@>$%^|]:&6;<7*-$}9{;!*!$5{<;-=^8]#:5<@#%#&!5!@40207#9($3&)7<$1";

int b32dec(char *in, char *out, int len)
{
    int i;
    char alpha[] = "3:5[9&2^]{7}*<-8@=4(6#!>|)0+;1$%";
    for (i=0; i < len; i++)
    {
        unsigned char bits = strchr(alpha, in[i])-alpha;
        int j = (i / 8) * 5;
        switch (i % 8) {
            case 0:
                out[j + 0] |= bits << 3;
                break;
            case 1:
                out[j + 0] |= bits >> 2;
                out[j + 1] |= bits << 6;
                break;
            case 2:
                out[j + 1] |= bits << 1;
                break;
            case 3:
                out[j + 1] |= bits >> 4;
                out[j + 2] |= bits << 4;
                break;
            case 4:
                out[j + 2] |= bits >> 1;
                out[j + 3] |= bits << 7;
                break;
            case 5:
                out[j + 3] |= bits << 2;
                break;
            case 6:
                out[j + 3] |= bits >> 3;
                out[j + 4] |= bits << 5;
                break;
            case 7:
                out[j + 4] |= bits;
                break;
        }
    }
    return i/8 * 5;
}


int keysched(unsigned char *x, unsigned char *key, int keylen)
{
    int i;
    unsigned char tmp, a = 0;

    for (i=0; i < 256; i++)
        x[i] = i;

    for (i=0; i < 256; i++)
    {
        a += x[i] + key[i % keylen];
        tmp = x[i];
        x[i] = x[a];
        x[a] = tmp;
    }
}

int crypt(unsigned char *x, unsigned char *y, int len)
{
    unsigned char a;
    unsigned char b = 0;
    unsigned char tmp;
    int i;

    for (i=0; i < len; i++)
    {
        a = i+1;
        b += x[a];
        tmp = x[a];
        x[a] = x[b];
        x[b] = tmp;
        y[i] ^= x[(x[a] + x[b]) & 0xff];
    }
}

int main()
{
    unsigned char x[256];
    unsigned char key[] = "abcd";
    unsigned char crypt_text[sizeof(str)] = {};
    int len;

    len = b32dec(str, crypt_text, strlen(str));
    keysched(x, key, strlen(key));
    crypt(x, crypt_text, len);
    printf("%s\n", crypt_text);
}
