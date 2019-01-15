#include <stdlib.h>
#include <string.h>
/* Autor: Bartosz Lukasiewicz
 * Rozwiazanie wzorcowe.
 * Implementacja algorytmu Dinicka na podstawie kodu autorstwa Marka Cygana
 * http://was.zaa.mimuw.edu.pl/sites/default/files/file/s2008-w03/flow.cpp.
 * Zlozonosc: O(n^4).
 */

#include <algorithm>
#include <cstdio>
#include <vector>

#define scanf(arg...) (scanf(arg)?:0)

namespace Dinic
{
    const int INF = 1000000001;
    const int N = 1000;
    std::vector<int> edge[N];
    std::vector<int>::iterator ptr[N];
    int capacity[N][N], distance[N], q[N];

    void insert(int a, int b, int c)
    {
        capacity[a][b] += c;
        edge[a].push_back(b);
        edge[b].push_back(a);
    }

    bool bfs(int s, int t, int n)
    {
        for(int i=0; i<n; i++) distance[i] = -1;
        distance[s] = 0;
        int beg = 0, end = 0;
        q[end++] = s;
        while(beg < end)
        {
            int v = q[beg++];
            for(std::vector<int>::iterator it=edge[v].begin(); it!=edge[v].end(); it++)
                if(capacity[v][*it] > 0 && distance[*it] == -1)
                {
                    distance[*it] = distance[v] + 1;
                    q[end++] = *it;
                }
        }
        return (distance[t] != -1);
    }

    int dfs(int v, int t, int minimum)
    {
        int res = 0;
        if(v == t || minimum == 0) return minimum;
        for(std::vector<int>::iterator &it=ptr[v]; it!=edge[v].end(); it++)
            if(distance[v] + 1 == distance[*it] && capacity[v][*it] > 0)
            {
                int y = dfs(*it, t, std::min(minimum, capacity[v][*it]));
                capacity[v][*it] -= y; 
                capacity[*it][v] += y;
                minimum -= y, res += y;
                if(minimum == 0) break;
            }
        return res;
    }

    int flow(int s, int t, int n)
    {
        int res=0;
        while(bfs(s, t, n))
        {
            for(int i=0; i<n; i++) ptr[i] = edge[i].begin();
            res += dfs(s, t, INF);
        }
        return res;
    }
}

struct Job
{
    int x, y, c;
};

const int MAXN = 105;

std::vector<std::pair<int,int> > intervals;
std::vector<int> times;
Job jobs[MAXN];
int n, m, sumC;

bool intervalInJob(std::pair<int,int> interval, Job job)
{
    return interval.first >= job.x && interval.second <= job.y;
}

int main()
{
    scanf("%d %d", &n, &m);
    
    for(int i=0; i<n; i++)
    {
        scanf("%d %d %d", &jobs[i].x, &jobs[i].y, &jobs[i].c);
        times.push_back(jobs[i].x);
        times.push_back(jobs[i].y);
        sumC += jobs[i].c;
    }
    
    std::sort(times.begin(), times.end());
    std::vector<int>::iterator it = std::unique(times.begin(), times.end());
    times.resize(std::distance(times.begin(), it));

    int intervalsSize = int(times.size()) - 1;
    int S = 0;
    int T = 1 + intervalsSize + n; 
    
    for(int i=0; i<intervalsSize; i++)
    {
        intervals.push_back(std::make_pair(times[i], times[i+1]));
        Dinic::insert(S, 1 + i, m * (times[i+1] - times[i]));
    }
    
    for(int i=0; i<intervalsSize; i++)
        for(int j=0; j<n; j++)
            if(intervalInJob(intervals[i], jobs[j]))
                Dinic::insert(1 + i, 1 + intervalsSize + j, intervals[i].second - intervals[i].first);
    
    for(int i=0; i<n; i++)
        Dinic::insert(1 + intervalsSize + i, T, jobs[i].c);
    
    int f = Dinic::flow(S, T, T + 1);
    
    printf("%s\n", (f == sumC) ? "YES" : "NO");
    return 0;
}
