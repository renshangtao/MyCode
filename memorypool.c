/* 设计内存池 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//C语言实现的内存池：
// 数据结构实现：
// G-PP ---> |MEM_POOL_S|MEM_POOL_S|MEM_POOL_S|MEM_POOL_S|MEM_POOL_S|...|
            //     |           |           |       |           |
            //   BLOCK->    BLOCK->     BLOCK->   BLOCK->    BLOCK->
            //   BLOCK->    BLOCK->     BLOCK->   BLOCK->    BLOCK->
            //   BLOCK->    BLOCK->     BLOCK->   BLOCK->    BLOCK->
            //   BLOCK->    BLOCK->     BLOCK->   BLOCK->    BLOCK->
            //   BLOCK->    BLOCK->     BLOCK->   BLOCK->    BLOCK->
            //   NULL       NULL        NULL      NULL       NULL






typedef struct MemBlock
{
    void *pData;
    int column;
    struct MemBlock *pNext;
}MEM_BLOCK_S;

typedef struct MemPool
{
    int total;
    int free;
    int memsize;
    MEM_BLOCK_S FreeHead;
}MEM_POOL_S;

typedef struct MemManger
{
    int typeNums;
    MEM_POOL_S *pstMemPools;
}MEM_MANGER_S;

MEM_MANGER_S g_stMemManger;


void mem_add2Pool(MEM_BLOCK_S *pstBlock)
{
    MEM_BLOCK_S *pstHead = NULL;

    if (NULL != pstBlock)
    {
        pstHead = &g_stMemManger.pstMemPools[pstBlock->column].FreeHead;
        pstBlock->pNext = pstHead->pNext;
        pstHead->pNext = pstBlock;
        
        g_stMemManger.pstMemPools[pstBlock->column].free++;
    }    
}

/* 内存申请 */
void *mem_malloc(int size)
{
    int column = ~0;
    MEM_POOL_S *pstMemPool = NULL;
    MEM_BLOCK_S *pstMemBlock = NULL;

    for (int i = 0; i < g_stMemManger.typeNums; i++)
    {
        if (g_stMemManger.pstMemPools[i].memsize >= size)
        {
            column = i;
            break;
        }
    }

    if (column != ~0)
    {
        pstMemPool = &g_stMemManger.pstMemPools[column];
        if (pstMemPool->free > 0)
        {
            pstMemBlock = pstMemPool->FreeHead.pNext;
            pstMemPool->FreeHead.pNext = pstMemBlock->pNext; 
            pstMemBlock->pNext = NULL;
            pstMemPool->free--;
        }
    }

    printf("malloc size = %d, calloc size = %d.\n", size, pstMemPool->memsize);

    return (void *)pstMemBlock;
}

/* 内存释放 */
void mem_free(void* pstBlock)
{
    mem_add2Pool((MEM_BLOCK_S *)pstBlock);
}

/* 内存池初始化 */
int mem_InitMemPool(int num, int sizes[], int nums[])
{
    MEM_BLOCK_S *pTmp = NULL;
    int tmpSize = 0;

    if (num == 0) return -1; 

    g_stMemManger.typeNums = num;

    /* 系统刚启动，不可能内存不够 */
    g_stMemManger.pstMemPools = (MEM_POOL_S *)malloc(sizeof(MEM_POOL_S) * num);
    if (NULL == g_stMemManger.pstMemPools)
    {
        return -1;
    }

    memset(g_stMemManger.pstMemPools, 0, sizeof(MEM_POOL_S) * num);

    for (int i = 0; i < num; i++)
    {
        g_stMemManger.pstMemPools[i].total = nums[i];
        g_stMemManger.pstMemPools[i].free = nums[i];
        g_stMemManger.pstMemPools[i].memsize = sizes[i];

        for (int j = 0; j < nums[i]; j++)
        {
            tmpSize = sizeof(MEM_BLOCK_S) + sizes[i];
            pTmp = (MEM_BLOCK_S *)malloc(tmpSize);
            memset(pTmp, 0, tmpSize);
            pTmp->pNext = NULL;
            pTmp->column = i;
            mem_add2Pool(pTmp);            
        }
    }

    printf("memPoolInit\r\n");

    return 0;
}

/* 内存池销毁 */
void mem_DestoryMemPool()
{
    MEM_POOL_S *pstMemPools = NULL;
    MEM_BLOCK_S *pstMemBlock = NULL;
    MEM_BLOCK_S *pstTmp = NULL;

    for (int i = 0; i < g_stMemManger.typeNums; i++)
    {
        pstMemPools = &g_stMemManger.pstMemPools[i];

        pstMemBlock = pstMemPools->FreeHead.pNext;
        while (pstMemBlock != NULL)
        {
            pstTmp = pstMemBlock->pNext;
            free(pstMemBlock);
            pstMemBlock = pstTmp;
        }
    }

    printf("memPoolDestory\r\n");
}

int main(void)
{
    char *pTmp = NULL;
    int a[] = {4, 8, 16, 32, 64, 128, 256, 512, 1024};
    int b[] = {90, 80, 70, 60, 50, 40, 30, 20, 10};

    mem_InitMemPool(sizeof(a)/sizeof(int), a, b);

    for (int i = 4; i < 1000; i+=20)
    {
        pTmp = (char*)mem_malloc(i);
        mem_free(pTmp);
    }
    
    mem_DestoryMemPool();

}