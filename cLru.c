#include<stdio.h>
#include<stdlib.h>
#define N 320
int num[N];  //存放随机数 
int page[N]; //存放页地址流 
int mc[33]; //memory capacity内存容量 ，并初始化为0 
 
void randomnumber()//random number随机数 程序第一步，产生320个指令序列 
{   
	int pc;
	int flag=0;     
	scanf("%d",&pc);     
	printf("\n在0-319之间产生的320个随机数如下:\n");     
	for(int i=0;i<320;i++)  
	{        
        num[i]=pc;   
        if(flag%2==0) pc=++pc%320;  //flag=0||2 50%的指令是顺序执行的       
        if(flag==1) pc=rand()% (pc-1);   //flag=1 25%的指令是均匀分布在前地址部分   
        if(flag==3) pc=pc+1+(rand()%(320-(pc+1)));  //flag=3 25%的指令是均匀分布在后地址部分       
        flag=++flag%4;   
        printf("%3d   ",num[i]);         
        if((i+1)%10==0) printf("\n");  //每行输出10个数 
	} 
} 
 
void pageaddress()    //pageaddress页地址 程序第二步，将指令序列变换为页地址流 
{     
	for(int i=0;i<320;i++)  
	{     
        printf("%3d   ",page[i]=num[i]/10);        
        if((i+1)%10==0) printf("\n");  //每行输出10个数 
	} 
}
 
int LRU(int capacity)
{
	int j,x,y,m;
	int sum=0; //mc中分配的个数 
	int exist=0; //命中次数 
	int flag; //标志是否命中 flag=0没命中 flag=1命中 
	int ep;
	mc[1]=page[0];
	printf(" %2d加入  \t",page[0]);
	for(m=1;m<=capacity;m++)   //输出当前内存块的存储情况 
		printf("%2d  ",mc[m]);
	printf("\n");
	sum+=1; 
	for(j=1;j<320;j++)
	{ 
        flag=0; 
        for(y=1;y<=sum;y++)   //判断这个页地址流是否命中 
        {
            if(mc[y]==page[j]) 
            {
                exist++;
                flag=1;
                printf(" %2d命中  \t",page[j]);
                for(m=1;m<=capacity;m++)   //输出当前内存块的存储情况
                {
                    printf("%2d  ",mc[m]);
                } 
                printf("\n");
                break;
            } 
        }
        
        //没命中 
        if(flag==0)    
        {
            if(sum<capacity)  //还有空块 
            {
                for(x=1;x<=capacity;x++) //查找内存块中第一个空块 
                {
                    if(mc[x]==-1) 
                    {
                        mc[x]=page[j];
                        sum++;
                        printf(" %2d加入  \t",page[j]);
                        for(m=1;m<=capacity;m++)    //输出当前内存块的存储情况 
                            printf("%2d  ",mc[m]);
                        printf("\n");
                        break;
                    }
                }
            }
            else if(sum>=capacity)
            {
                int t; 
                int a,b;
                int min=320;
                for(b=capacity;b>=1;b--)   //找最近最少使用的页地址流 
                for(a=j-1;a>=0;a--)
                {
                    if(mc[b]==page[a]) 
                    { 
                    if(a>min) break;
                    if(a<min){min=a;break;}
                    }
                }
                for(a=1;a<=capacity;a++)  //找最少使用的页地址流对应的页号所在数组的下标 
                {
                    if(mc[a]==page[min]) {ep=a;break;}
                }
                t=mc[ep];
                mc[ep]=page[j];
                printf(" %2d置换%2d\t",page[j],t);
                for(m=1;m<=capacity;m++)   //输出当前内存块的存储情况 
                    printf("%2d  ",mc[m]);
                printf("\n");
            } 
        }
	} 
	printf("\nexist=%d\n命中率=%lf",exist,exist/320.0);
} 
int main()
{
	int capacity; 
	printf("请输入第一条指令号(0~319):");
	randomnumber();
	printf("\n指令序列对应的页地址流:\n");   
	pageaddress();     
	printf("\n\n\n\t\t最近最少使用算法(LRU):\n\n");
	printf("请输入内存块数（4-32）：");
	scanf("%d",&capacity);
	for(int i=1;i<=32;i++)  //给数组赋初值 
	    mc[i]=-1;
	LRU(capacity);   
	return 0;
}
