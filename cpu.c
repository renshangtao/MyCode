#include <stdio.h>
#include <stdlib.h>

int cmp(const void *p1, const void *p2)
{
    int ip1 = *(int *)p1;
    int ip2 = *(int *)p2;

    return ip1 - ip2;
}

int main()
{
    int cpunum = 0;
    int jobnum = 0;
    int tm[100] = {0};
    int i = 0;
    int sumtime = 0 ;
    int num = 0;

    scanf("%d", &cpunum);
    scanf("%d", &jobnum);

    for (i = 0; i < jobnum; i++)
    {
        scanf("%d", &tm[i]);
    }

    qsort(tm, jobnum, sizeof(int), cmp);

    num = jobnum % cpunum;
    if (num == 0)
    {
        num = cpunum;
    }

    for (i = num - 1; i < jobnum; i += cpunum)
    {
        sumtime += tm[i];

        //printf("i = %d, sum = %d, tm[i] = %d\r\n", i, sumtime, tm[i]);
    }

    //printf("tm[jobmum-1] = %d, sum = %d\r\n", tm[jobnum-1], sumtime);
    printf("%d", sumtime);


    return 0;
}