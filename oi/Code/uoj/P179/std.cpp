#include <cstdio>
#include <cstdlib>
#include <algorithm>

int n,m;
double eq[21][21];
int idx[20],idy[20];
double ans[20];

inline int read(void)
{
    char c;
    int answer = 0;
    int sign = 1;
    while((c = getchar()),(c < '0' || c > '9' ))
        if(c == '-')
            sign = -1;
    do ((answer *= 10) += c - '0'),(c = getchar());
    while(c >= '0' && c <= '9');
    return answer * sign;
}

inline int sign(double x)
{
    if(x > 1e-8)
        return 1;
    if(x < -1e-8)
        return -1;
    return 0;
}

int pviot(int x,int y)
{
    int i,j;
    std::swap(idy[x],idx[y]);
    for(i = 0;i <= n;++i)
        if(i != y)
            eq[x][i] /= -eq[x][y];
    eq[x][y] = 1.0 / eq[x][y];
    for(i = 0;i <= m;++i)
    {
        if(i == x || !sign(eq[i][y]))
            continue;
        for(j = 0;j <= n;++j)
            if(j != y)
                eq[i][j] += eq[i][y] * eq[x][j];
        eq[i][y] *= eq[x][y];
    }
}

int initialize(void)
{
    int i;
    int x,y;
    for(;;)
    {
        x = y = -1;
        for(i = 0;i < m;++i)
            if(sign(eq[i][n]) < 0 && (x == -1 || (rand() & 1)))
                x = i;
        if(x == -1)
            return 0;
        for(i = 0;i < n;++i)
            if(sign(eq[x][i]) > 0 && (y == -1 || (rand() & 1)))
                y = i;
        if(y == -1)
            return -1;
        pviot(x,y);
    }
}

int simplex(void)
{
    int i;
    double w;
    int x,y;
    if(initialize())
        return -1;
    for(;;)
    {
        x = y = -1;
        for(i = 0;i < n;++i)
            if(sign(eq[m][i]) > 0 && (y == -1 || (rand() & 1)))
                y = i;
        if(y == -1)
            return 0;
        for(i = 0;i < m;++i)
            if(sign(eq[i][y]) < 0 && (x == -1 || -eq[i][n] / eq[i][y] < w))
                x = i,w = -eq[i][n] / eq[i][y];
        if(x == -1)
            return 1;
        pviot(x,y);
    }
}

int main(void)
{
    int i,j,k;

//    freopen("uoj179.in","r",stdin);
//    freopen("uoj179.out","w",stdout);

    n = read();
    m = read();
    k = read();

    for(i = 0;i < n;++i)
    {
        idx[i] = i;
        eq[m][i] = read();
    }
    for(i = 0;i < m;++i)
    {
        for(j = 0;j < n;++j)
            eq[i][j] = -read();
        eq[i][n] = read();
        idy[i] = n + i;
    }

    switch(simplex())
    {
    case 1:
        puts("Unbounded");
        break;
    case -1:
        puts("Infeasible");
        break;
    case 0:
        printf("%.8lf\n",eq[m][n]);
        if(!k)
            break;
        for(i = 0;i < m;++i)
			if(idy[i] < n)
            	ans[idy[i]] = eq[i][n];
        for(i = 0;i < n;++i)
            printf("%.8lf ",ans[i]);
        printf("\n");
        break;
    }

    return 0;
}
