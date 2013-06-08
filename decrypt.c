#include <string.h>
#include <stdio.h>

typedef unsigned char q;
q s[] = "43(:7&!#3&@>$%^|]:&6;<7*-$}9{;!*!$5{<;-=^8]#:5<@#%#&!5!@40207#9($3&)7<$1";

int b(q *n, int l, q *k, int m, q *y)
{
    int i,j,w,t,e=256;
    q a[] = "3:5[9&2^]{7}*<-8@=4(6#!>|)0+;1$%", d[8], c=0, x[e], *o=y;
    for (i=0; i < l; i+=8)
    {
        for (j=0; j < 8; j++)
            d[j] = (q*)strchr(a,*n++)-a;
        *o++ = d[0] << 3 | d[1] >> 2;
        *o++ = d[1] << 6 | d[2] << 1 | d[3] >> 4;
        *o++ = d[3] << 4 | d[4] >> 1;
        *o++ = d[4] << 7 | d[5] << 2 | d[6] >> 3;
        *o++ = d[6] << 5 | d[7];
    }
    w = o-y;

    for (i=0; i < e; i++)
        i[x] = i;

    for (i=0; i < e; i++)
    {
        c += x[i] + k[i % m];
        t = x[i];
        x[i] = x[c];
        x[c] = t;
    }

    for (i=1,c=0; i <= w; i++)
    {
        c += x[i];
        t = x[i];
        x[i] = x[c];
        x[c] = t;
        y[i-1] ^= x[(q)(x[i] + x[c])];
    }
}

int main()
{
    q k[] = "abcd", t[421] = {};

    b(s, strlen(s), k, 4, t);
    puts(t);
}
