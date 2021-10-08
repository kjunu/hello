#include <stdio.h>
#include <string.h>
#include<deque>
using namespace std;
int n, m;
char frined[50][11];
int ans;
int dish[50];
bool cooked[50];
deque<int> d[50], caneat[50];
void worker(int chosen)
{
    if (chosen >= ans) return;
    int tar_f = -1;
    for (int i = 0; i<n; i++)
    {
        if (dish[i] == 0 && (tar_f == -1 || caneat[i].size()<caneat[tar_f].size()))
            tar_f = i;
    }
    if (tar_f == -1)
    {
        if (ans>chosen) ans = chosen;
        return;
    }
    for (int i = 0; i<caneat[tar_f].size(); i++)
    {
        if (!cooked[caneat[tar_f][i]])
        {
            cooked[caneat[tar_f][i]] = true;
            for (int j = 0; j<d[caneat[tar_f][i]].size(); j++)
                dish[d[caneat[tar_f][i]][j]]++;
            worker(chosen + 1);
            for (int j = 0; j<d[caneat[tar_f][i]].size(); j++)
                dish[d[caneat[tar_f][i]][j]]--;
            cooked[caneat[tar_f][i]] = false;
        }
    }
}
int main()
{
    int r;
    scanf("%d", &r);
    while (r--)
    {
        scanf("%d%d", &n, &m);
        ans = 51;
        for (int i = 0; i<50; i++)
        {
            d[i].clear();
            caneat[i].clear();
        }
        for (int i = 0; i<n; i++)
        {
            scanf("%s", frined[i]);
        }
        for (int i = 0; i<m; i++)
        {
            int t;
            scanf("%d", &t);
            for (int j = 0; j<t; j++)
            {
                char str[11];
                scanf("%s", str);
                for (int fc = 0; fc<n; fc++)
                {
                    if (!strcmp(str, frined[fc]))
                    {
                        d[i].push_back(fc);
                        caneat[fc].push_back(i);
                        break;
                    }
                }
            }
        }
        worker(0);
        printf("%d\n", ans);
    }
    return 0;
}
