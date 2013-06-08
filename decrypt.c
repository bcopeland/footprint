#include <string.h>
#include <stdio.h>

typedef unsigned char q;
q s[] = "43(:7&!#3&@>$%^|]:&6;<7*-$}9{;!*!$5{<;-=^8]#:5<@#%#&!5!@40207#9($3&)7<$1";

b(q *n, int l, q *y)
{
    int i,e=256,m=4;
    q a[] = "3:5[9&2^]{7}*<-8@=4(6#!>|)0+;1$%", d[8],
      c=0, t, x[e], *o=y, k[]="abcd";
    for (i=0; i < l; i++)
    {
        d[i%8] = (q*)strchr(a,*n++)-a;
        if (!((i+1)%8)) {
            *o++ = d[0] * 8 | d[1] / 4;
            *o++ = d[1] << 6 | d[2] * 2 | d[3] >> 4;
            *o++ = d[3] << 4 | d[4] / 2;
            *o++ = d[4] << 7 | d[5] * 4 | d[6] / 8;
            *o++ = d[6] << 5 | d[7];
        }
    }

    for (i=0; i < e; i++)
        i[x] = i;

    for (i=0; i < e; i++)
    {
        c += x[i] + k[i % m];
        t = x[i];
        x[i] = x[c];
        x[c] = t;
    }

    for (i=1,c=0; i <= o-y; i++)
    {
        c += x[i];
        t = x[i];
        x[i] = x[c];
        x[c] = t;
        y[i-1] ^= x[(q)(x[i] + x[c])];
    }
}

main()
{
    q t[421] = {};

    b(s, strlen(s), t);
    puts(t);
}
