//miller_rabin�������+Pollard P�����ӷֽ�
//���� a<2^63
//�Ӵ�MAX ���Ա�֤�ֽ�ĳɹ���
#include <stdlib.h>
#include <stdio.h>

typedef unsigned __int64 u64;

#define MAX 100
#define MAXN 30

u64 len, dig, limit;
u64 mod(u64 a, u64 b, u64 n)
{
    if(!a) return 0;
    else return (((a & dig) * b) % n + (mod(a >> len, b, n) << len) % n) % n;
}

u64 by(u64 a, u64 b, u64 n)
{
    u64 p;
    p = 8, len = 61;
    while(p < n)
    {
        p <<= 4;
        len -= 4;
    }
    dig = ((limit / p) << 1) - 1; //��̬���ֶ�
    return mod(a, b, n);
}

u64 random(void)
{
    u64 a;
    a = rand();
    a *= rand();
    a *= rand();
    a *= rand();
    return a;
}

//Miller_Rabin
u64 square_multiply(u64 x, u64 c, u64 n)
{
    u64 z = 1;
    while(c)
    {
        if(c % 2 == 1) z = by(z, x, n);
        x = by(x,x,n);
        c = (c >> 1);
    }
    return z;
}

bool Miller_Rabin(u64 n)
{
    if(n < 2) return false;
    if(n == 2) return true;
    if(!(n & 1)) return false;
    u64 k = 0, i, j, m, a;
    m = n - 1;
    while(m % 2 == 0) m = (m >> 1), k++;
    for(i = 0; i < MAX; i++)
    {
        a = square_multiply(random() % (n - 1) + 1, m, n);//ƽ����
        if(a == 1) continue;
        for(j = 0; j < k; j++)
        {
            if(a == n - 1) break;
            a = by(a, a, n);
        }
        if(j < k) continue;
        return false ;
    }
    return true;
}

//Pollard p,ֻ�ҳ�һ�����ӡ�
u64 gcd(u64 a, u64 b)
{
    return b == 0 ? a : gcd(b, a % b);
}

//�ù�ʽf(x) = x^2 + 1������ײ��
u64 f(u64 x, u64 n)
{
    return (by(x, x, n) + 1) % n;
}

//�ֽⲻ����return 0
u64 Pollard(u64 n)
{
    if(n <= 2) return 0;
    if(!(n & 1)) return 2; //�ز�����
    u64 i, p, x, xx;
    for(i = 1; i < MAX; i++)
    {
        x = random() % n; //����ֱ���� x = i
        xx = f(x, n);
        p = gcd((xx + n - x) % n , n);
        while(p == 1)
        {
            x = f(x, n);
            xx = f(f(xx, n), n);
            p = gcd((xx + n - x) % n, n) % n;
        }
        if(p)return p;
    }
    return 0;
}

/////////////////////////////////////////////////////////
u64 factor[MAXN], m;
/////////////////////////////////////////////////////
//�ֽ���������
u64 prime(u64 a)
{   
    if(Miller_Rabin(a) || a == 0) return 0;
    u64 t = Pollard(a), p;
    if(p = prime(t)) return p;
    else return t;
}


//622057148 155514287 ���
int main(void)
{
    u64 l, a, t;
    limit = 1;
    limit = limit << 63; //��̬���ֶ�ʹ��
    while(scanf("%I64u", &a) != EOF)
    {
        m = 0;
        while(a > 1)
        {
            if(Miller_Rabin(a)) break;
            t = prime(a);
            if (t == 0) break;
            factor[m++] = t;
            a /= t;
        }
        if(a > 0) factor[m++] = a;
        for(l = 0; l < m; l++)
            printf("%I64u\n", factor[l]);
    }
    return 0;
}
